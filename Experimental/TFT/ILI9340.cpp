//	ILI9340 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ILI9340.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ILI9340 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
#include <TFT.h>

#define ILI9340_NOP     0x00
#define ILI9340_SWRESET 0x01
#define ILI9340_RDDID   0x04
#define ILI9340_RDDST   0x09

#define ILI9340_SLPIN   0x10
#define ILI9340_SLPOUT  0x11
#define ILI9340_PTLON   0x12
#define ILI9340_NORON   0x13

#define ILI9340_RDMODE 0x0A
#define ILI9340_RDMADCTL 0x0B
#define ILI9340_RDPIXFMT 0x0C
#define ILI9340_RDIMGFMT 0x0A
#define ILI9340_RDSELFDIAG 0x0F

#define ILI9340_INVOFF 0x20
#define ILI9340_INVON 0x21
#define ILI9340_GAMMASET 0x26
#define ILI9340_DISPOFF 0x28
#define ILI9340_DISPON 0x29

#define ILI9340_CASET 0x2A
#define ILI9340_PASET 0x2B
#define ILI9340_RAMWR 0x2C
#define ILI9340_RAMRD 0x2E

#define ILI9340_PTLAR 0x30
#define ILI9340_MADCTL 0x36


#define ILI9340_MADCTL_MY 0x80
#define ILI9340_MADCTL_MX 0x40
#define ILI9340_MADCTL_MV 0x20
#define ILI9340_MADCTL_ML 0x10
#define ILI9340_MADCTL_RGB 0x00
#define ILI9340_MADCTL_BGR 0x08
#define ILI9340_MADCTL_MH 0x04

#define ILI9340_PIXFMT 0x3A

#define ILI9340_FRMCTR1 0xB1
#define ILI9340_FRMCTR2 0xB2
#define ILI9340_FRMCTR3 0xB3
#define ILI9340_INVCTR 0xB4
#define ILI9340_DFUNCTR 0xB6

#define ILI9340_PWCTR1 0xC0
#define ILI9340_PWCTR2 0xC1
#define ILI9340_PWCTR3 0xC2
#define ILI9340_PWCTR4 0xC3
#define ILI9340_PWCTR5 0xC4
#define ILI9340_VMCTR1 0xC5
#define ILI9340_VMCTR2 0xC7

#define ILI9340_RDID1 0xDA
#define ILI9340_RDID2 0xDB
#define ILI9340_RDID3 0xDC
#define ILI9340_RDID4 0xDD

#define ILI9340_GMCTRP1 0xE0
#define ILI9340_GMCTRN1 0xE1

inline uint16_t swapcolor(uint16_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void ILI9340::initializeDevice() {
    _comm->initializeDevice();
    _width  = ILI9340::Width;
    _height = ILI9340::Height;
    _comm->writeCommand8(0xEF);
    _comm->writeData8(0x03);
    _comm->writeData8(0x80);
    _comm->writeData8(0x02);

    _comm->writeCommand8(0xCF);
    _comm->writeData8(0x00);
    _comm->writeData8(0XC1);
    _comm->writeData8(0X30);

    _comm->writeCommand8(0xED);
    _comm->writeData8(0x64);
    _comm->writeData8(0x03);
    _comm->writeData8(0X12);
    _comm->writeData8(0X81);

    _comm->writeCommand8(0xE8);
    _comm->writeData8(0x85);
    _comm->writeData8(0x00);
    _comm->writeData8(0x78);

    _comm->writeCommand8(0xCB);
    _comm->writeData8(0x39);
    _comm->writeData8(0x2C);
    _comm->writeData8(0x00);
    _comm->writeData8(0x34);
    _comm->writeData8(0x02);

    _comm->writeCommand8(0xF7);
    _comm->writeData8(0x20);

    _comm->writeCommand8(0xEA);
    _comm->writeData8(0x00);
    _comm->writeData8(0x00);

    _comm->writeCommand8(ILI9340_PWCTR1); //Power control
    _comm->writeData8(0x23); //VRH[5:0]

    _comm->writeCommand8(ILI9340_PWCTR2); //Power control
    _comm->writeData8(0x10); //SAP[2:0];BT[3:0]

    _comm->writeCommand8(ILI9340_VMCTR1); //VCM control
    _comm->writeData8(0x3e); //¶Ô±È¶Èµ÷½Ú
    _comm->writeData8(0x28);

    _comm->writeCommand8(ILI9340_VMCTR2); //VCM control2
    _comm->writeData8(0x86); //--

    _comm->writeCommand8(ILI9340_MADCTL); // Memory Access Control
    _comm->writeData8(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);

    _comm->writeCommand8(ILI9340_PIXFMT);
    _comm->writeData8(0x55);

    _comm->writeCommand8(ILI9340_FRMCTR1);
    _comm->writeData8(0x00);
    _comm->writeData8(0x18);

    _comm->writeCommand8(ILI9340_DFUNCTR); // Display Function Control
    _comm->writeData8(0x08);
    _comm->writeData8(0x82);
    _comm->writeData8(0x27);

    _comm->writeCommand8(0xF2); // 3Gamma Function Disable
    _comm->writeData8(0x00);

    _comm->writeCommand8(ILI9340_GAMMASET); //Gamma curve selected
    _comm->writeData8(0x01);

    _comm->writeCommand8(ILI9340_GMCTRP1); //Set Gamma
    _comm->writeData8(0x0F);
    _comm->writeData8(0x31);
    _comm->writeData8(0x2B);
    _comm->writeData8(0x0C);
    _comm->writeData8(0x0E);
    _comm->writeData8(0x08);
    _comm->writeData8(0x4E);
    _comm->writeData8(0xF1);
    _comm->writeData8(0x37);
    _comm->writeData8(0x07);
    _comm->writeData8(0x10);
    _comm->writeData8(0x03);
    _comm->writeData8(0x0E);
    _comm->writeData8(0x09);
    _comm->writeData8(0x00);

    _comm->writeCommand8(ILI9340_GMCTRN1); //Set Gamma
    _comm->writeData8(0x00);
    _comm->writeData8(0x0E);
    _comm->writeData8(0x14);
    _comm->writeData8(0x03);
    _comm->writeData8(0x11);
    _comm->writeData8(0x07);
    _comm->writeData8(0x31);
    _comm->writeData8(0xC1);
    _comm->writeData8(0x48);
    _comm->writeData8(0x08);
    _comm->writeData8(0x0F);
    _comm->writeData8(0x0C);
    _comm->writeData8(0x31);
    _comm->writeData8(0x36);
    _comm->writeData8(0x0F);

    _comm->writeCommand8(ILI9340_SLPOUT); //Exit Sleep
    delay(120);
    _comm->writeCommand8(ILI9340_DISPON); //Display on 
}

void ILI9340::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	_comm->writeCommand8(ILI9340_CASET); // Column addr set
    _comm->writeData16(x0);
    _comm->writeData16(x1);
//	_comm->writeData8(x0 >> 8);
//	_comm->writeData8(x0 & 0xFF);     // XSTART 
//	_comm->writeData8(x1 >> 8);
//	_comm->writeData8(x1 & 0xFF);     // XEND

	_comm->writeCommand8(ILI9340_PASET); // Row addr set
    _comm->writeData16(y0);
    _comm->writeData16(y1);
//	_comm->writeData8(y0 >> 8);
//	_comm->writeData8(y0 & 0xFF);     // YSTART
//	_comm->writeData8(y1 >> 8);
//	_comm->writeData8(y1 & 0xFF);     // YEND

	_comm->writeCommand8(ILI9340_RAMWR); // write to RAM
}

void ILI9340::setPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);
	_comm->writeData16(color);
}

void ILI9340::fillScreen(uint16_t color) {
	fillRectangle(0, 0,  _width, _height, color);
}

void ILI9340::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	setAddrWindow(x, y, x+w-1, y+h-1);

    _comm->streamStart();
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
            _comm->streamData16(color);
		}
	}
    _comm->streamEnd();
}

void ILI9340::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

    _comm->streamStart();
	while (w--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void ILI9340::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

    _comm->streamStart();
	while (h--) {
		_comm->streamData16(color);
	}
    _comm->streamEnd();
}

void ILI9340::setRotation(uint8_t m) {
	_comm->writeCommand8(ILI9340_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			_comm->writeData8(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Width;
			_height = ILI9340::Height;
			break;
		case 1:
		    _comm->writeData8(ILI9340_MADCTL_MV | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Height;
			_height = ILI9340::Width;
			break;
		case 2:
			_comm->writeData8(ILI9340_MADCTL_MY | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Width;
			_height = ILI9340::Height;
			break;
		case 3:
			_comm->writeData8(ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
			_width  = ILI9340::Height;
			_height = ILI9340::Width;
			break;
	}
}

void ILI9340::invertDisplay(boolean i) {
	_comm->writeCommand8(i ? ILI9340_INVON : ILI9340_INVOFF);
}

void ILI9340::update(Framebuffer *fb) {
    setAddrWindow(0, 0, _width, _height);
    uint16_t linebuffer[_width];

    for (int y = 0; y < _height; y++) {
	fb->getScanLine(y, linebuffer);
	_comm->blockData(linebuffer, _width);
    }
}

