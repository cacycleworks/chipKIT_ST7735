//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
/////////////////////////////////////////////////////////////////////////
#ifndef _ST7735H_
#define _ST7735H_

#include <TFT.h>

class ST7735 : public TFT {

	public:
        static const uint8_t GreenTab   = 0x00;
        static const uint8_t RedTab     = 0x01;
        static const uint8_t BlackTab   = 0x02;
        static const uint8_t TypeB      = 0x03;
        static const uint8_t Width      = 128;
        static const uint8_t Height     = 160;

		ST7735(TFTCommunicator *comms, uint8_t variant) : TFT(comms), _variant(variant) {}

		void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setRotation(uint8_t r);
        void invertDisplay(boolean i);
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

        void update(Framebuffer *fb);

	protected:
		void streamCommands(uint8_t *cmdlist);
		uint8_t colstart, rowstart;
        uint8_t _variant;

        uint32_t _linebuffer[2][160];
        uint8_t _xferline;
};

#endif
/*************************************************** 
  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
