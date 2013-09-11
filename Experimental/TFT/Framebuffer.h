#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include <TFT.h>

struct sprite {
    int16_t xpos;
    int16_t ypos;
    uint16_t width;
    uint16_t height;
    uint8_t transparent;
    int8_t frames;
    int8_t currentframe;
    int8_t animdir;
    int8_t store[8];
    const uint8_t *data;
    struct sprite *next;
};

class Framebuffer : public TFT {
    public:
        Framebuffer(int16_t w, int16_t h, uint8_t *b);

        static const uint8_t MirrorH = 0x01;
        static const uint8_t MirrorV = 0x02;
        static const uint8_t Rotate180 = 0x03;

        // Basic drawing primitives
        void setPixel(int16_t x, int16_t y, uint16_t c);
        void drawIndexed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h);
        void drawIndexed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t t);
        void drawIndexed(int16_t x, int16_t y, const Framebuffer& fb);
        void drawIndexed(int16_t x, int16_t y, const Framebuffer& fb, uint8_t t);

        void drawTransformed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t transform);
        void drawTransformed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t transform, uint8_t t);
        void drawTransformed(int16_t x, int16_t y, const Framebuffer& fb, uint8_t transform);
        void drawTransformed(int16_t x, int16_t y, const Framebuffer& fb, uint8_t transform, uint8_t t);

        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        void fillScreen(uint16_t);

        // Color control
        void setColor(uint8_t color, uint16_t rgb);
        void setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b);
        void loadPalette(const uint16_t *p);
        void loadPalette(const uint8_t p[256][3]);
        void loadPalette(const Framebuffer& fb);
        uint16_t colorAt(int16_t x, int16_t y) const;

        // Sprites
        struct sprite * addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f);
        void removeSprite(struct sprite *s);
        void moveTo(struct sprite *s, int16_t x, int16_t y);
        void moveBy(struct sprite *s, int16_t dx, int16_t dy);
        struct sprite *spriteAt(int16_t x, int16_t y) const;
        void animate(struct sprite *s);
        void animatePingPong(struct sprite *s);
        struct sprite *collidesWith(struct sprite *s);
        struct sprite *firstSprite();
        struct sprite *nextSprite();
        int8_t getSprite(struct sprite *s, uint8_t n);
        void setSprite(struct sprite *s, uint8_t n, int8_t v);

        uint8_t *buffer;
        uint16_t palette[256];
        struct sprite *sprites;
//        int16_t _width, _height;
        struct sprite *selectedSprite;
};

#endif
