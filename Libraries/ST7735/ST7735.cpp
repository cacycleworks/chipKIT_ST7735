//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT Uno32, uC32
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
/////////////////////////////////////////////////////////////////////////
#include "ST7735.h"

inline uint16_t swapcolor(uint16_t x) { 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

//	Constructor for using hardware SPI.  Faster, but must use SPI pins
//	specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
//  RST pin ignored altogether
ST7735::ST7735( uint8_t cs, uint8_t rs ) {
	_cs   = cs;
	_rs   = rs;
	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	digitalWrite(_cs, HIGH);
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV2);
}

// Initialization code common to both 'B' and 'R' type displays
void ST7735::commonInit(uint8_t *cmdList) {
	// instead of using c++ way of calling the parent's constructor, a function was created
	constructor(ST7735_TFTWIDTH, ST7735_TFTHEIGHT);
	colstart  = rowstart = 0; // May be overridden in init func

	digitalWrite(_cs, LOW);
	delay(10);
	if(cmdList) commandList(cmdList);
	digitalWrite(_cs, HIGH);
}
//	Initialization for ST7735B screens - seems to be no reference to this in code?
//  Legacy?
void ST7735::initB(void) {
	commonInit(Bcmd);
}
//	Initialization for ST7735R screens (green or red tabs) Black tabs don't have
//  anything special in here, however affects some of the color and bit handling in
//  other functions
void ST7735::initR(uint8_t options) {
	commonInit(Rcmd1);
	if(options == INITR_GREENTAB) {
		commandList(Rcmd2green);
		colstart = 2;
		rowstart = 1;
	} else {
		// colstart, rowstart left at default '0' values
		commandList(Rcmd2red);
	}
	commandList(Rcmd3);
	tabcolor=options;
}

inline void ST7735::spiwrite(uint8_t c) {
//	Delay10us();    // not needed and makes TFT only slightly faster than software SPI on Arduinos
	SPI.transfer( c );
}

//	These two appear to be wrappers for writing SPI data, however most functions do it themselves
//	because they need to handle multiple bytes...
void ST7735::writecommand(uint8_t c) {
	digitalWrite(_rs, LOW);
	digitalWrite(_cs, LOW);
	spiwrite(c);
	digitalWrite(_cs, HIGH);
}

void ST7735::writedata(uint8_t c) {
	//	using Arduino "port masks" and direct PORT writing to speed up talking to SS/CS and RS/CD pins
	//*rsport |=  rspinmask;
	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);
	spiwrite(c);
	digitalWrite(_cs, HIGH);
}

//	Companion code for the static init tables.  Reads and issues
//	a series of LCD commands stored in static byte array.
void ST7735::commandList(uint8_t *addr) {
	uint8_t  numCommands, numArgs;
	uint16_t ms;
	numCommands = *addr;addr++;   // Number of commands to follow
	while(numCommands--) {                 // For each command...
		writecommand(*addr); //   Read, issue command
		addr++;
		numArgs  = *addr; addr++;    //   Number of args to follow
		ms       = numArgs & DELAY;          //   If hibit set, delay follows args
		numArgs &= ~DELAY;                   //   Mask out delay bit
		while(numArgs--) {                   //   For each argument...
			writedata(*addr);  //     Read, issue argument
			addr++;
		}
		if(ms) {
			ms = *addr;addr++; // Read post-command delay time (ms)
			//  Tested without this delay and TFT inits without it. Command list
			//  byte array was NOT altered, thus the above line of code required
			//  to step the pointer to the next array element.
//			if(ms == 255) ms = 500;     // If 255, delay for 500 ms
//			delay(ms);
		}
	}
}

void ST7735::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	writecommand(ST7735_CASET); // Column addr set
	writedata(0x00);
	writedata(x0+colstart);     // XSTART 
	writedata(0x00);
	writedata(x1+colstart);     // XEND

	writecommand(ST7735_RASET); // Row addr set
	writedata(0x00);
	writedata(y0+rowstart);     // YSTART
	writedata(0x00);
	writedata(y1+rowstart);     // YEND

	writecommand(ST7735_RAMWR); // write to RAM
}


void ST7735::pushColor(uint16_t color) {
	if (tabcolor == INITR_BLACKTAB)   
		color = swapcolor(color);
	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);

	spiwrite(color >> 8);
	spiwrite(color);

	digitalWrite(_cs, HIGH);
}

void ST7735::drawPixel(int16_t x, int16_t y, uint16_t color) {
	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) 
		return;
	setAddrWindow(x,y,x+1,y+1);

	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);

	spiwrite(color >> 8);
	spiwrite(color);

	digitalWrite(_cs, HIGH);
}


void ST7735::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((y+h-1) >= _height) 
		h = _height-y;
	setAddrWindow(x, y, x, y+h-1);
	if (tabcolor == INITR_BLACKTAB)   
		color = swapcolor(color);
	uint8_t hi = color >> 8, lo = color;
	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);
	while (h--) {
		spiwrite(hi);
		spiwrite(lo);
	}
	digitalWrite(_cs, HIGH);
}


void ST7735::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) 
		return;
	if((x+w-1) >= _width)  
		w = _width-x;
	setAddrWindow(x, y, x+w-1, y);
	if (tabcolor == INITR_BLACKTAB)   
		color = swapcolor(color);
	uint8_t hi = color >> 8, lo = color;

	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);
	while (w--) {
		spiwrite(hi);
		spiwrite(lo);
	}
	digitalWrite(_cs, HIGH);
}

void ST7735::fillScreen(uint16_t color) {
	fillRect(0, 0,  _width, _height, color);
}

// fill a rectangle
void ST7735::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= _width) || (y >= _height)) 
		return;
	if((x + w - 1) >= _width)  
		w = _width  - x;
	if((y + h - 1) >= _height) 
		h = _height - y;
	if (tabcolor == INITR_BLACKTAB)   
		color = swapcolor(color);
	setAddrWindow(x, y, x+w-1, y+h-1);
	uint8_t hi = color >> 8, lo = color;

	digitalWrite(_rs, HIGH);
	digitalWrite(_cs, LOW);
	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
			spiwrite(hi);
			spiwrite(lo);
		}
	}
	digitalWrite(_cs, HIGH);
}


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t ST7735::Color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x08
#define MADCTL_MH  0x04

void ST7735::setRotation(uint8_t m) {
	writecommand(ST7735_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
		case 0:
			writedata(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
			_width  = ST7735_TFTWIDTH;
			_height = ST7735_TFTHEIGHT;
			break;
		case 1:
			writedata(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
			_width  = ST7735_TFTHEIGHT;
			_height = ST7735_TFTWIDTH;
			break;
		case 2:
			writedata(MADCTL_RGB);
			_width  = ST7735_TFTWIDTH;
			_height = ST7735_TFTHEIGHT;
			break;
		case 3:
			writedata(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
			_width  = ST7735_TFTHEIGHT;
			_height = ST7735_TFTWIDTH;
			break;
	}
}

void ST7735::invertDisplay(boolean i) {
	writecommand(i ? ST7735_INVON : ST7735_INVOFF);
}

void ST7735::Delay10us()   {
	volatile int cnt;
	for (cnt = 0; cnt < 100; cnt++) {
		;
	}
}
