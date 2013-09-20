#include <TFT.h>

Framebuffer1::Framebuffer1(int16_t w, int16_t h, uint8_t *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    buffer = b;
    memset(buffer, 0, (w * h) / 8);
    setColor(0, Color::Black);
    setColor(1, Color::White);
}

void Framebuffer1::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    uint8_t pcol = color & 0xFF;
    uint32_t pos = y * _width + x;
    uint32_t bytepos = pos / 8;
    uint32_t bitpos = pos & 8;
    if (color) {
        buffer[bytepos] |= (1<<bitpos);
    } else {
        buffer[bytepos] &= ~(1<<bitpos);
    }
}

void Framebuffer1::fillScreen(uint16_t color) {
    memset(buffer, (color ? 0xFF : 0), (_width * _height) / 8);
}

void Framebuffer1::setColor(uint8_t color, uint16_t rgb) {
    palette[color % 2] = rgb;
}

void Framebuffer1::setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
    palette[color % 2] = color565(r, g, b);
}

void Framebuffer1::loadPalette(const uint16_t *p) {
    for (int i = 0; i < 2; i++) {
        setColor(i, p[i]);
    }
}

void Framebuffer1::loadPalette(const uint8_t p[256][3]) {
    for (int i = 0; i < 2; i++) {
        setColor(i, p[i][0], p[i][1], p[i][2]);
    }
}

void Framebuffer1::loadPalette(const Framebuffer& fb) {
    memcpy(palette, fb.palette, 2);
}

uint16_t Framebuffer1::colorAt(int16_t x, int16_t y) const {
    if (x < 0 || y < 0 || x >= _width || y >= _width) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = s->width * s->height * s->currentframe;
        uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
        return palette[color % 2];
    }
    uint32_t pos = y * _width + x;
    uint32_t bytepos = pos / 8;
    uint32_t bitpos = pos % 8;
    return palette[(buffer[bytepos] & (1<<bitpos)) ? 1 : 0];
}
