//	SSD1289 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in SSD1289.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_SSD1289 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
#include <TFT.h>

inline uint16_t swapcolor(uint16_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void SSD1289::initializeDevice() {
    _comm->initializeDevice();
    _width  = SSD1289::Width;
    _height = SSD1289::Height;

    _comm->streamStart();

    delay(15);
    _comm->streamCommand16(0x0000); _comm->streamData16(0x0001);
    _comm->streamCommand16(0x0003); _comm->streamData16(0xA8A4);
    _comm->streamCommand16(0x000C); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x000D); _comm->streamData16(0x800C);
    _comm->streamCommand16(0x000E); _comm->streamData16(0x2B00);
    _comm->streamCommand16(0x001E); _comm->streamData16(0x00B7);
    _comm->streamCommand16(0x0001); _comm->streamData16(0x2B3F);
    _comm->streamCommand16(0x0002); _comm->streamData16(0x0600);
    _comm->streamCommand16(0x0010); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0011); _comm->streamData16(0x6070);
    _comm->streamCommand16(0x0005); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0006); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0016); _comm->streamData16(0xEF1C);
    _comm->streamCommand16(0x0017); _comm->streamData16(0x0003);
    _comm->streamCommand16(0x0007); _comm->streamData16(0x0233);
    _comm->streamCommand16(0x000B); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x000F); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0041); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0042); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0048); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0049); _comm->streamData16(0x013F);
    _comm->streamCommand16(0x004A); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x004B); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0044); _comm->streamData16(0xEF95);
    _comm->streamCommand16(0x0045); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0046); _comm->streamData16(0x013F);
    _comm->streamCommand16(0x0030); _comm->streamData16(0x0707);
    _comm->streamCommand16(0x0031); _comm->streamData16(0x0204);
    _comm->streamCommand16(0x0032); _comm->streamData16(0x0204);
    _comm->streamCommand16(0x0033); _comm->streamData16(0x0502);
    _comm->streamCommand16(0x0034); _comm->streamData16(0x0507);
    _comm->streamCommand16(0x0035); _comm->streamData16(0x0204);
    _comm->streamCommand16(0x0036); _comm->streamData16(0x0204);
    _comm->streamCommand16(0x0037); _comm->streamData16(0x0502);
    _comm->streamCommand16(0x003A); _comm->streamData16(0x0302);
    _comm->streamCommand16(0x003B); _comm->streamData16(0x0302);
    _comm->streamCommand16(0x0023); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0024); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0025); _comm->streamData16(0x8000);
    _comm->streamCommand16(0x004f); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x004e); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0022);

    _comm->streamEnd();
}

void SSD1289::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

    uint16_t x0a, x1a, y0a, y1a;

    switch(rotation) {
        case 1:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
  
            x0 = y0a;
            x1 = y1a;
            y0 = _width - x1a;
            y1 = _width - x0a;
            break;
        case 2:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;
        
            x0 = _width - x1a;
            x1 = _width - x0a;
            y0 = _height - y1a;
            y1 = _height - y0a;
            break;
  

        case 3:
            x0a = x0;
            x1a = x1;
            y0a = y0;
            y1a = y1;

            x0 = _height - y1a;
            x1 = _height - y0a;
            y0 = x0a;
            y1 = x1a;
            break;
    }

    _comm->streamCommand16(68); _comm->streamData16((x1 << 8) | x0);
    _comm->streamCommand16(69); _comm->streamData16(y0);
    _comm->streamCommand16(70); _comm->streamData16(y1);
    _comm->streamCommand16(78); _comm->streamData16(x0);
    _comm->streamCommand16(79); _comm->streamData16(y0);
    _comm->streamCommand16(34);
}

void SSD1289::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    _comm->streamStart();
	setAddrWindow(x,y,x,y);
	_comm->streamData16(color);
    _comm->streamEnd();
}

void SSD1289::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void SSD1289::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;

    _comm->streamStart();
	setAddrWindow(x, y, x+w-1, y+h-1);
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            _comm->streamData16(color);
		}
	}
    _comm->streamEnd();
}

void SSD1289::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;

    _comm->streamStart();
	setAddrWindow(x, y, x+w-1, y);
	while (w--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void SSD1289::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;

    _comm->streamStart();
	setAddrWindow(x, y, x, y+h-1);
	while (h--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

#define SSD1289_EMODE 0x0003

#define SSD1289_TRI 0x8000
#define SSD1289_DFM 0x4000
#define SSD1289_BGR 0x1000
#define SSD1289_HWM 0x0200
#define SSD1289_ORG 0x0080
#define SSD1289_ID0 0x0000
#define SSD1289_ID1 0x0010
#define SSD1289_ID2 0x0020
#define SSD1289_ID3 0x0030
#define SSD1289_AM  0x0008

void SSD1289::setRotation(uint8_t m) {
	rotation = m % 4; // can't be higher than 3
}

void SSD1289::invertDisplay(boolean i) {
//	_comm->writeCommand(i ? SSD1289_INVON : SSD1289_INVOFF);
}

void SSD1289::update(Framebuffer *fb) {
    uint32_t pixpair = 0;
    uint16_t color = 0;

    uint16_t scanline[_width];

    _comm->streamStart();
    setAddrWindow(0, 0, _width-1, _height-1);
    _comm->streamEnd();
    for (int y = 0; y < _height; y++) {
        fb->getScanLine(y, scanline);
        _comm->streamStart();
        _comm->blockData(scanline, _width);
        _comm->streamEnd();
    }
}

