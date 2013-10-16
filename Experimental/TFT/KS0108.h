//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
/////////////////////////////////////////////////////////////////////////
#ifndef _KS0108H_
#define _KS0108H_

#include <TFT.h>

class KS0108 : public TFT {

	public:
		KS0108(TFTCommunicator *chip) : TFT(chip) {}

		void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void fillScreen(uint16_t color);
        void doSetPixel(int16_t x, int16_t y, uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

        void updateScreen();

	protected:
		void streamCommands(uint8_t *cmdlist);
		uint8_t colstart, rowstart;
        uint8_t _variant;

        void setPage(uint8_t page);
        void setY(uint8_t y);

        uint8_t buffer[64 * 8];
};

#endif
