#ifndef _HD44780_H_
#define _HD44780_H_

#include <TFT.h>

class HD44780 : public TFT {

	public:
        static const uint8_t GreenTab   = 0x00;
        static const uint8_t RedTab     = 0x01;
        static const uint8_t BlackTab   = 0x02;
        static const uint8_t TypeB      = 0x03;

		HD44780(TFTCommunicator *comm, uint16_t w, uint16_t h) : TFT(comm) {
            _width = w;
            _height = h;
        };

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color) {} // Not implemented
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {} // Not implemented
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {} // Not implemented
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {} // Not implemented
        void setRotation(uint8_t r) {} // Not implemented
        void invertDisplay(boolean i) {} // Not implemented
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();

#if ARDUINO >= 100
        size_t write(char c);
#else
        void write(char c);
#endif

};

#endif
