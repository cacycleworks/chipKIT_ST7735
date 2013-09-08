/*
 * Framebuffered and paletted superclass for the ST7735 AdaFruit 1.8" TFT screen.
 *
 * This class allocates a buffer of 160 x 128 x 8 bits, plus a palette of 256 x 16 bits,
 * so requires at least 21KiB of RAM to operate.  It WILL NOT work on the UNO32, but 
 * should work on the uC32, and certainly on the MAX32 (with hardware mods for high speed
 * SPI support)
 *
 * Requires at least version 105 of the ST7735 library
 */

#ifndef _ST7735FBH_
#define _ST7735FBH_

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

class ST7735FB : public ST7735 {

	public:
        ST7735FB(TFTCommunicator *comm, uint8_t variant) : ST7735(comm, variant) {
            this->sprites = NULL;
            setColor(0, Color::Black);
            setColor(1, Color::DarkBlue);
            setColor(2, Color::DarkRed);
            setColor(3, Color::DarkMagenta);
            setColor(4, Color::DarkGreen);
            setColor(5, Color::DarkCyan);
            setColor(6, Color::Orange);
            setColor(7, Color::Gray75);
            setColor(8, Color::Gray50);
            setColor(9, Color::Blue);
            setColor(10, Color::Red);
            setColor(11, Color::Magenta);
            setColor(12, Color::Green);
            setColor(13, Color::Cyan);
            setColor(14, Color::Yellow);
            setColor(15, Color::White);
        };

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

		void update();

        void setPixel(int16_t, int16_t, uint16_t);
        void fillScreen(uint16_t);
        void drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        struct sprite * sprites;
        int8_t getSprite(struct sprite *s, uint8_t n);
        void setSprite(struct sprite *s, uint8_t n, int8_t v);

	private:
        uint16_t palette[256];
        uint8_t buffer[ST7735FB::Width * ST7735::Height];
        struct sprite *selectedSprite;
};

#endif
