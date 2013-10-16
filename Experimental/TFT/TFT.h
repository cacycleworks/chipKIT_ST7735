#ifndef _TFT_H
#define _TFT_H

#if ARDUINO >= 100
# include <Arduino.h>
# include <Print.h>
#else
# include <WProgram.h>
#endif

#define RGB(r,g,b) ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

#include <algorithm>

// Base classes
#include <TFTCommunicator.h>
#include <DataStore.h>
#include <Color.h>
#include <Fonts.h>

class Framebuffer;

class TFT : public Print
{
    public:
        TFT();
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
        void setTextColor(uint16_t c);
        void setTextColor(uint16_t fg, uint16_t bg);
        uint16_t getTextColor();
        void invertTextColor();
        void setTextWrap(boolean w);
        uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

        void fillScreen(uint16_t color);
        void fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void setFont(const uint8_t *f);
        virtual void setPixel(int16_t x, int16_t y, uint16_t color) = 0;
        virtual void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) = 0;
        virtual void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) = 0;
        virtual void initializeDevice() = 0;
        virtual void displayOn() = 0;
        virtual void displayOff() = 0;
        virtual void invertDisplay(boolean i) = 0;
        virtual void update(Framebuffer *fb);
        virtual void update(Framebuffer *fb, int16_t dx, int16_t dy);
        virtual uint16_t stringWidth(char *text);
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
        uint8_t drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);

        virtual uint16_t getWidth() { return _width; };
        virtual uint16_t getHeight() { return _height; };


    private:
        void drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
        void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

    protected:
        const uint8_t *font;

};

// Supplorted communication systems
#ifdef __PIC32MX__
#include <TFTDSPI.h>
// Not ready yet: #include <TFTSPI.h>
#endif

#include <TFTSoftSPI.h>
#include <TFTPar4.h>
#include <TFTPar8.h>
#include <RawPar.h>
#include <TFTPMP.h>
#include <MCP23S17.h>

// Storage devices
#include <SPIRAM.h>
#include <SRAM.h>

// Virtual display devices
#include <Framebuffer.h>
#include <Framebuffer1.h>
#include <Aggregator.h>

// Supported devices
#include <ST7735.h>
#include <KS0108.h>
#include <LEDMatrix.h>
#include <HD44780.h>
#include <DOGMe.h>
#include <ILI9340.h>
#include <BD663474.h>
#include <SSD1289.h>

// Touchscreen devices
#include <Touch.h>
#include <XPT2046.h>
#endif


