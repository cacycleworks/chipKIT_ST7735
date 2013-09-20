#ifndef _FRAMEBUFFER1_H
#define _FRAMEBUFFER1_H

#include <TFT.h>

class Framebuffer1 : public Framebuffer {
    public:
        Framebuffer1(int16_t w, int16_t h, uint8_t *b);

        // Basic drawing primitives
        void fillScreen(uint16_t c);
        void setPixel(int16_t x, int16_t y, uint16_t c);

        void setColor(uint8_t color, uint16_t rgb);
        void setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b);
        void loadPalette(const uint16_t *p);
        void loadPalette(const uint8_t p[256][3]);
        void loadPalette(const Framebuffer& fb);
        uint16_t colorAt(int16_t x, int16_t y) const;

        uint16_t palette[2];
};

#endif
