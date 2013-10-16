#ifndef _SSD1289_H_
#define _SSD1289+H_

#include <TFT.h>

class SSD1289 : public TFT {

	public:
        static const uint16_t Width      = 240;
        static const uint16_t Height     = 320;

		SSD1289(TFTCommunicator *comms) : TFT(comms) {}

		void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
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

};

#endif
