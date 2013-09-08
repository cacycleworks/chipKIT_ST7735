#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

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

class Framebuffer {

	public:
        Framebuffer();

        void setColor(uint8_t color, uint16_t rgb);
        void setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b);
        void loadPalette(const uint16_t *p);
        void loadPalette(const uint8_t p[256][3]);
        void drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h);
        void drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t t);
        struct sprite * addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f);
        void removeSprite(struct sprite *s);
        void moveTo(struct sprite *s, int16_t x, int16_t y);
        void moveBy(struct sprite *s, int16_t dx, int16_t dy);
        struct sprite *spriteAt(int16_t x, int16_t y);
        uint8_t colorAt(int16_t x, int16_t y);
        void animate(struct sprite *s);
        void animatePingPong(struct sprite *s);
        struct sprite *collidesWith(struct sprite *s);
        struct sprite *firstSprite();
        struct sprite *nextSprite();
        void setPixel(int16_t, int16_t, uint16_t);
        void fillScreen(uint16_t);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        struct sprite * sprites;
        int8_t getSprite(struct sprite *s, uint8_t n);
        void setSprite(struct sprite *s, uint8_t n, int8_t v);
        void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
        uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

		virtual void update() {};
        virtual uint8_t getBuffer(uint32_t addr) {};
        virtual void setBuffer(uint32_t addr, uint8_t data) {};
        virtual void fillBuffer(uint8_t data) {};
        virtual uint8_t getWidth() {};
        virtual uint8_t getHeight() {};

        uint16_t palette[256];

	private:
        struct sprite *selectedSprite;
};

#endif
