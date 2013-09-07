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

#ifndef _ST7735BH_
#define _ST7735BH_

#include <WProgram.h>
#include <DSPI.h>
#include <GFX.h>
#include <ST7735.h>

struct sprite {
    int16_t xpos;
    int16_t ypos;
    uint16_t width;
    uint16_t height;
    uint8_t transparent;
    int8_t frames;
    int8_t currentframe;
    int8_t animdir;
    const uint8_t *data;
    struct sprite *next;
};

class ST7735B : public ST7735 {

	public:
        ST7735B(uint8_t CS, uint8_t RS) : ST7735(CS, RS) { this->sprites = NULL; };
        ST7735B(uint8_t CS, uint8_t RS, DSPI *SPI) : ST7735(CS, RS, SPI) { this->sprites = NULL; };
        ST7735B(uint8_t CS, uint8_t RS, uint8_t SDO, uint8_t SCK) : ST7735(CS, RS, SDO, SCK) { this->sprites = NULL; };

        void setColor(uint8_t color, uint16_t rgb);
        void setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b);
        void loadPalette(const uint16_t *p);
        void loadPalette(const uint8_t p[256][3]);
        void drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h);

        struct sprite * addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f);
        struct sprite *spriteAt(int16_t x, int16_t y);
        uint8_t colorAt(int16_t x, int16_t y);
        void animate(struct sprite *s);
        void animatePingPong(struct sprite *s);
        struct sprite *collidesWith(struct sprite *s);

		void update();

        void drawPixel(int16_t, int16_t, uint16_t);
        void fillScreen(uint16_t);
        void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
        void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
        struct sprite * sprites;

	private:
        uint16_t palette[256];
		void spiwrite32(uint32_t);
        uint8_t buffer[ST7735_TFTWIDTH * ST7735_TFTHEIGHT];
};

#endif
