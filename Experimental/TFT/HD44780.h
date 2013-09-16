#ifndef _HD44780_H_
#define _HD44780_H_

#include <TFT.h>

class HD44780 : public TFT {

	public:
		HD44780(TFTCommunicator *comm, uint8_t w, uint8_t h) : TFT(comm) { 
            _width = w; 
            _height = h; 
            if (comm->nativeWidth() == 4) {
                _bits = 4;
            } else {
                _bits = 8;
            }
        };


        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color) {} // Not implemented
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {} // Not implemented
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {} // Not implemented
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {} // Not implemented
        void setRotation(uint8_t r) {} // Not implemented
        void invertDisplay(boolean i) {} // Not implemented
        void displayOn();
        void displayOff();

        void initializeDevice();

        void clearScreen();
        void home();

#if ARDUINO >= 100
        size_t write(char c);
#else
        void write(char c);
#endif

        void command(uint8_t cmd);
        void data(uint8_t d);
        uint8_t _bits;
        boolean _cursor;
        boolean _blink;
};

#endif
