//	BD663474 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in BD663474.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_BD663474 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
#include <TFT.h>

inline uint16_t swapcolor(uint16_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void BD663474::initializeDevice() {
    _comm->initializeDevice();
    _width  = BD663474::Width;
    _height = BD663474::Height;

    _comm->streamStart();

    delay(15);

    // Power
    _comm->streamCommand16(0x0000); _comm->streamData16(0x0001);
    delay(10);
    _comm->streamCommand16(0x0100); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0101); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0102); _comm->streamData16(0x3110);
    _comm->streamCommand16(0x0103); _comm->streamData16(0xE200);
    _comm->streamCommand16(0x0110); _comm->streamData16(0x009D);
    _comm->streamCommand16(0x0111); _comm->streamData16(0x0022);
    _comm->streamCommand16(0x0100); _comm->streamData16(0x0120);
    delay(20);
    _comm->streamCommand16(0x0100); _comm->streamData16(0x3120);
    delay(80);
    // Display
    _comm->streamCommand16(0x0001); _comm->streamData16(0x0100);
    _comm->streamCommand16(0x0002); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0003); _comm->streamData16(0x1230);
    _comm->streamCommand16(0x0006); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0007); _comm->streamData16(0x0101);
    _comm->streamCommand16(0x0008); _comm->streamData16(0x0808);
    _comm->streamCommand16(0x0009); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x000B); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x000C); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x000D); _comm->streamData16(0x0018);
    // LTPS
    _comm->streamCommand16(0x0012); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0013); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0018); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0019); _comm->streamData16(0x0000);

    _comm->streamCommand16(0x0203); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0204); _comm->streamData16(0x0000);

    _comm->streamCommand16(0x0210); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0211); _comm->streamData16(0x00EF);
    _comm->streamCommand16(0x0212); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0213); _comm->streamData16(0x013F);
    _comm->streamCommand16(0x0214); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0215); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0216); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0217); _comm->streamData16(0x0000);

    // Grey scale
    _comm->streamCommand16(0x0300); _comm->streamData16(0x5343);
    _comm->streamCommand16(0x0301); _comm->streamData16(0x1021);
    _comm->streamCommand16(0x0302); _comm->streamData16(0x0003);
    _comm->streamCommand16(0x0303); _comm->streamData16(0x0011);
    _comm->streamCommand16(0x0304); _comm->streamData16(0x050A);
    _comm->streamCommand16(0x0305); _comm->streamData16(0x4342);
    _comm->streamCommand16(0x0306); _comm->streamData16(0x1100);
    _comm->streamCommand16(0x0307); _comm->streamData16(0x0003);
    _comm->streamCommand16(0x0308); _comm->streamData16(0x1201);
    _comm->streamCommand16(0x0309); _comm->streamData16(0x050A);

    // RAM access
    _comm->streamCommand16(0x0400); _comm->streamData16(0x4027);
    _comm->streamCommand16(0x0401); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0402); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0403); _comm->streamData16(0x013F);
    _comm->streamCommand16(0x0404); _comm->streamData16(0x0000);

    _comm->streamCommand16(0x0200); _comm->streamData16(0x0000);
    _comm->streamCommand16(0x0201); _comm->streamData16(0x0000);

    _comm->streamCommand16(0x0100); _comm->streamData16(0x7120);
    _comm->streamCommand16(0x0007); _comm->streamData16(0x0103);
    delay(10);
    _comm->streamCommand16(0x0007); _comm->streamData16(0x0113);
    _comm->streamEnd();
}

void BD663474::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

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

    x1 -= 1;
//    y1 += 3;
    _comm->streamCommand16(0x0210); _comm->streamData16(x0);
    _comm->streamCommand16(0x0211); _comm->streamData16(x1);
    _comm->streamCommand16(0x0212); _comm->streamData16(y0);
    _comm->streamCommand16(0x0213); _comm->streamData16(y1);
    _comm->streamCommand16(0x0200); _comm->streamData16(x0);
    _comm->streamCommand16(0x0201); _comm->streamData16(y0);
    _comm->streamCommand16(0x0202);
}

void BD663474::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;

    fillRectangle(x, y, 1, 1, color);

//    _comm->streamStart();
//	setAddrWindow(x,y,x+1,y+1);
//    _comm->streamCommand16(0x0202);
//	_comm->streamData16(color);
//    _comm->streamEnd();
}

void BD663474::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void BD663474::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
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

void BD663474::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
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

void BD663474::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
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

#define BD663474_EMODE 0x0003

#define BD663474_TRI 0x8000
#define BD663474_DFM 0x4000
#define BD663474_BGR 0x1000
#define BD663474_HWM 0x0200
#define BD663474_ORG 0x0080
#define BD663474_ID0 0x0000
#define BD663474_ID1 0x0010
#define BD663474_ID2 0x0020
#define BD663474_ID3 0x0030
#define BD663474_AM  0x0008

void BD663474::setRotation(uint8_t m) {
    _comm->streamStart();
	rotation = m % 4; // can't be higher than 3
    _comm->streamCommand16(BD663474_EMODE);
	switch (rotation) {
		case 0:
            _comm->streamData16(BD663474_BGR | BD663474_ORG | BD663474_ID3);
			_width  = BD663474::Width;
			_height = BD663474::Height;
			break;
		case 1:
            _comm->streamData16(BD663474_BGR | BD663474_ORG | BD663474_ID1 | BD663474_AM); 
			_width  = BD663474::Height;
			_height = BD663474::Width;
			break;
		case 2:
            _comm->streamData16(BD663474_BGR | BD663474_ORG | BD663474_ID0);
			_width  = BD663474::Width;
			_height = BD663474::Height;
			break;
		case 3:
            _comm->streamData16(BD663474_BGR | BD663474_ORG | BD663474_ID2 | BD663474_AM);
			_width  = BD663474::Height;
			_height = BD663474::Width;
			break;
	}
    _comm->streamEnd();
//			_width  = BD663474::Width;
//			_height = BD663474::Height;

}

void BD663474::invertDisplay(boolean i) {
//	_comm->writeCommand(i ? BD663474_INVON : BD663474_INVOFF);
}

void BD663474::update(Framebuffer *fb) {
    uint32_t pixpair = 0;
    uint16_t color = 0;

    _comm->streamStart();
    setAddrWindow(0, 0, _width, _height);
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x+=2) {
            color = fb->colorAt(x, y);
            pixpair = color << 16;
            color = fb->colorAt(x+1, y);
            pixpair |= color;
            _comm->streamData32(pixpair);
        }
    }
    _comm->streamEnd();
}

