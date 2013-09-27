//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
#include <TFT.h>

#define GLCD_CMD_OFF         0b00111110
#define GLCD_CMD_ON          0b00111111
#define GLCD_CMD_SET_Y       0b01000000
#define GLCD_CMD_SET_PAGE    0b10111000
#define GLCD_CMD_START       0b11000000

#define GLCD_STAT_BUSY   0b10000000
#define GLCD_STAT_ONOFF  0b00100000
#define GLCD_STAT_RESET  0b00010000

void KS0108::initChip(TFTCommunicator *chip) {
    chip->writeCommand8(GLCD_CMD_ON);
    chip->writeCommand8(GLCD_CMD_START);
}

void KS0108::initializeDevice() {
    _width  = 64;
    _height = 64;
    initChip(_chip1);
    if (_chip2) {
        _width = 128;
        initChip(_chip2);
    }
    if (_chip3) {
        _width = 192;
        initChip(_chip3);
    }
    buffer = (uint8_t *)malloc(_width * _height / 8);
}

void KS0108::setPage(TFTCommunicator *chip, uint8_t page)
{
    chip->writeCommand8(GLCD_CMD_SET_PAGE | (page & 0x07));
}

void KS0108::setY(TFTCommunicator *chip, uint8_t y)
{
    chip->writeCommand8(GLCD_CMD_SET_Y | (y & 63));
}

void KS0108::setPixel(int16_t x, int16_t y, uint16_t color) {
    uint8_t row;
    uint8_t pixel;
    uint8_t mask;

	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    row = y>>3;
    pixel = y & 0x07;
    mask = 1<<pixel;
    if (color) {
        this->buffer[row * _width + x] |= mask;
    } else {
        this->buffer[row * _width + x] &= ~mask;
    }
}

void KS0108::fillScreen(uint16_t color) {
    for (int16_t y = 0; y < _height/8; y++) {
        for (int16_t x = 0; x < _width; x++) {
            this->buffer[y * _width + x] = color ? 0xFF : 0x00;
        }
    }
}

void KS0108::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;

    for (int16_t dy = y; dy < y + h; dy++) {
        for (int16_t dx = x; dx < x + w; dx++) {
            setPixel(dx, dy, color);
        }
    }
}

void KS0108::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    drawLine(x, y, x + w, y, color);
}

void KS0108::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    drawLine(x, y, x, y + h, color);
}

void KS0108::invertDisplay(boolean i) {
    for (int16_t y = 0; y < _height/8; y++) {
        for (int16_t x = 0; x < _width; x++) {
            this->buffer[y * _width + x] = ~this->buffer[y * _width + x];
        }
    }
}

void KS0108::update() {
    uint8_t x,y;
    for(y=0; y<8; y++)
    {
        this->setPage(_chip1, y);
        this->setY(_chip1, 0);
        if (_chip2) {
            this->setPage(_chip2, y);
            this->setY(_chip2, 0);
        }
        if (_chip3) {
            this->setPage(_chip3, y);
            this->setY(_chip3, 0);
        }
        for(x=0; x<64; x++)
        {
            _chip1->writeData8(this->buffer[y * _width + x]);
            if (_chip2) {
                _chip2->writeData8(this->buffer[y * _width + x + 64]);
            }
            if (_chip3) {
                _chip3->writeData8(this->buffer[y * _width + x + 128]);
            }
        }
    }
}
