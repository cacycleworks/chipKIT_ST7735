#include <TFT.h>

Framebuffer1::Framebuffer1(int16_t w, int16_t h, DataStore *b) {
    _width = w;
    _height = h;
    sprites = NULL;
    buffer = b;
    setColor(0, Color::Black);
    setColor(1, Color::White);
}

void Framebuffer1::initializeDevice() {
    buffer->initializeDevice();
}

void Framebuffer1::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    uint8_t pcol = color & 0xFF;
    uint32_t pos = y * _width + x;
    uint32_t bytepos = pos / 8;
    uint32_t bitpos = pos & 8;
    uint8_t newval;
    if (color) {
	newval = buffer->read8(bytepos) | (1<<bitpos);
    } else {
	newval = buffer->read8(bytepos) & ~(1<<bitpos);
    }
    buffer->write8(bytepos, newval);
}

void Framebuffer1::fillScreen(uint16_t color) {
    for (uint32_t x = 0; x < (_width * _height) / 8; x++) {
        buffer->write8(x, color ? 0xFF : 0);
    }
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

void Framebuffer1::loadPalette(Framebuffer *fb) {
    memcpy(palette, fb->palette, 2);
}

uint16_t Framebuffer1::colorAt(int16_t x, int16_t y) {
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
    return palette[(buffer->read8(bytepos) & (1<<bitpos)) ? 1 : 0];
}

void Framebuffer1::getScanLine(uint16_t y, uint16_t *data) {
	uint8_t bufferdata[_width/8];
	buffer->read8((y * _width) / 8, bufferdata, _width / 8);
	for (uint16_t x = 0; x < _width; x++) {
		struct sprite *s = spriteAt(x, y);
		if (s) {
			uint32_t offset = s->width * s->height * s->currentframe;
			uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
			data[x] = palette[color % 2];
		} else {
			uint16_t bytepos = x / 8;
			uint16_t bitpos = x % 8;
    			data[x] = palette[(buffer->read8(bytepos) & (1<<bitpos)) ? 1 : 0];
		}
	}
}
