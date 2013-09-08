//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
/////////////////////////////////////////////////////////////////////////
#include <TFT.h>

static inline uint16_t swapcolor(uint16_t x) {
    return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void ST7735FB::update() {
    setAddrWindow(0, 0, _width, _height);
    uint32_t pixpair = 0;
    uint16_t color = 0;

    _comm->dataStreamStart();
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x+=2) {
            color = this->palette[colorAt(x, y)];
            if (_variant == ST7735FB::BlackTab) color = swapcolor(color);
            pixpair = color << 16;
            color = this->palette[colorAt(x+1, y)];
            if (_variant == ST7735FB::BlackTab) color = swapcolor(color);
            pixpair |= color;
            _comm->dataStream32(pixpair);
        }
    }
    _comm->dataStreamEnd();
}

uint8_t ST7735FB::getBuffer(uint32_t addr) {
    return buffer[addr];
}

void ST7735FB::setBuffer(uint32_t addr, uint8_t data) {
    buffer[addr] = data;
}

void ST7735FB::fillBuffer(uint8_t data) {
    memset(buffer, data, ST7735FB::Width * ST7735FB::Height);
}

uint8_t ST7735FB::getWidth() {
    return _width;
}

uint8_t ST7735FB::getHeight() {
    return _height;
}

