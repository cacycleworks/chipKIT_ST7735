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
        static const uint8_t GreenTab   = 0x00;
        static const uint8_t RedTab     = 0x01;
        static const uint8_t BlackTab   = 0x02;
        static const uint8_t TypeB      = 0x03;

		KS0108(TFTCommunicator *chip1) : TFT(), _chip1(chip1), _chip2(NULL), _chip3(NULL) {}
		KS0108(TFTCommunicator *chip1, TFTCommunicator *chip2) : 
            TFT(), _chip1(chip1), _chip2(chip2), _chip3(NULL) {}
		KS0108(TFTCommunicator *chip1, TFTCommunicator *chip2, TFTCommunicator *chip3) : 
            TFT(), _chip1(chip1), _chip2(chip2), _chip3(chip3) {}

		void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

        void update();

	protected:
		void streamCommands(uint8_t *cmdlist);
		uint8_t colstart, rowstart;
        uint8_t _variant;

        void initChip(TFTCommunicator *chip);
        void setPage(TFTCommunicator *chip, uint8_t page);
        void setY(TFTCommunicator *chip, uint8_t y);

        TFTCommunicator *_chip1;
        TFTCommunicator *_chip2;
        TFTCommunicator *_chip3;

        uint8_t *buffer;
};

#endif
