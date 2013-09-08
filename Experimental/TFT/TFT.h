#ifndef _TFT_H
#define _TFT_H

#if ARDUINO >= 100
# include <Arduino.h>
# include <Print.h>
#else
# include <WProgram.h>
#endif

#include <algorithm>

// Base classes
#include <TFTCommunicator.h>
#include <Color.h>

class TFT : public Print
{
    public:
        TFT(TFTCommunicator *comms);
        void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        void drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
        void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        void fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
        void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
        void drawRGB(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h);
        void drawRGBA(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, uint16_t trans);
        void setCursor(int16_t x, int16_t y);
        int16_t getCursor(boolean x);
        void setTextSize(uint8_t s);
        uint8_t getTextSize();
        void setTextColor(uint16_t c);
        void setTextColor(uint16_t fg, uint16_t bg);
        void invertTextColor();
        void setTextWrap(boolean w);
        int16_t width(void);
        int16_t height(void);
        uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

        virtual void setPixel(int16_t x, int16_t y, uint16_t color) {};
        void fillScreen(uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        virtual void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {};
        virtual void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {};
        virtual void initializeDevice() {};
        virtual void displayOn() {};
        virtual void displayOff() {};
        virtual void invertDisplay(boolean i) {};
#if ARDUINO >= 100
        size_t write(uint8_t c);
#else
        void write(uint8_t c);
#endif
        TFTCommunicator *_comm;
        int16_t cursor_x, cursor_y;
        uint8_t textsize;
        boolean wrap;
        uint16_t textcolor, textbgcolor;
        int16_t _width;
        int16_t _height;
        uint8_t rotation;

    private:
        void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
        void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
        void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);

};

// Supplorted communication systems
#include <TFTDSPI.h>
#include <TFTSoftSPI.h>

// Supported devices
#include <ST7735.h>

#endif


