//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
/////////////////////////////////////////////////////////////////////////
#include <TFT.h>

static inline uint16_t swapcolor(uint16_t x) {
    return (x << 11) | (x & 0x07E0) | (x >> 11);
}

void ST7735FB::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x > _width || y < 0 || y > _height) {
        return;
    }
    uint8_t pcol = color & 0xFF;
    uint32_t pos = y * _width + x;
    buffer[pos] = pcol;
}

void ST7735FB::update() {
    setAddrWindow(0, 0, _width, _height);
    uint32_t pixpair = 0;
    uint16_t color = 0;

    _comm->dataStreamStart();
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x+=2) {
            color = this->palette[colorAt(x, y)];
            if (_variant == ST7735FB::BlackTab) color = swapcolor(color);
            pixpair = color << 16;
            color = this->palette[colorAt(x+1, y)];
            if (_variant == ST7735FB::BlackTab) color = swapcolor(color);
            pixpair |= color;
            _comm->dataStream32(pixpair);
        }
    }
    _comm->dataStreamEnd();
}

void ST7735FB::fillScreen(uint16_t color) {
    memset(buffer, (color & 0xFF), ST7735FB::Width * ST7735FB::Height);
}
void ST7735FB::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    this->drawLine(x, y, x, y+h-1, color);
}


void ST7735FB::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    this->drawLine(x, y, x+w-1, y, color);
}

void ST7735FB::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  for (int16_t i=x; i<x+w; i++) {
    drawVerticalLine(i, y, h, color);
  }
}

void ST7735FB::setColor(uint8_t color, uint16_t rgb) {
    palette[color] = rgb;
}

void ST7735FB::setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
    palette[color] = this->color565(r, g, b);
}

void ST7735FB::loadPalette(const uint16_t *p) {
    for (int i = 0; i < 256; i++) {
        setColor(i, p[i]);
    }
}

void ST7735FB::loadPalette(const uint8_t p[256][3]) {
    for (int i = 0; i < 256; i++) {
        setColor(i, p[i][0], p[i][1], p[i][2]);
    }
}

void ST7735FB::drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            setPixel(x + i, y + j, data[pos]);
        }
    }
}

void ST7735FB::drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t t) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            if (data[pos] != t) {
                setPixel(x + i, y + j, data[pos]);
            }
        }
    }
}

struct sprite * ST7735FB::addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f) {
    struct sprite *scan;
    struct sprite *s = (struct sprite *)malloc(sizeof(struct sprite));
    s->data = data;
    s->width = w;
    s->height = h;
    s->xpos = _width+1;
    s->ypos = _height+1;
    s->transparent = t;
    s->frames = f;
    s->currentframe = 0;
    s->animdir = 1;
    s->next = NULL;
    if (this->sprites == NULL) {
        this->sprites = s;
        return s;
    }
    for (scan = this->sprites; scan->next; scan = scan->next);
    scan->next = s;
    return s;
}

void ST7735FB::removeSprite(struct sprite *s) {
    struct sprite *scan;
    struct sprite *last = NULL;

    if (this->sprites == s) {
        scan = s;
        this->sprites = this->sprites->next;
        free(s);
        return;
    }

    for (scan = this->sprites; scan; scan = scan->next) {
        if (scan == s) {
            if (last) {
                last->next = scan->next;
                free(s);
                return;
            }
        }
        last = scan;
    }
}

struct sprite *ST7735FB::spriteAt(int16_t x, int16_t y) {
    struct sprite *scan;
    if (this->sprites == NULL) {
        return NULL;
    }
    for (scan = this->sprites; scan; scan = scan->next) {
        if (scan->xpos <= x && scan->ypos <= y && (scan->xpos + scan->width) > x && (scan->ypos + scan->height) > y) {
            uint32_t offset = scan->width * scan->height * scan->currentframe;
            uint8_t color = scan->data[offset + (y - scan->ypos) * scan->width + (x - scan->xpos)];
            if (color != scan->transparent) {
                return scan;
            }
        }
    }
    return NULL;
}

uint8_t ST7735FB::colorAt(int16_t x, int16_t y) {
    struct sprite *s = this->spriteAt(x, y);
    if (s) {
        uint32_t offset = s->width * s->height * s->currentframe;
        uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
        return color;
    }
    uint32_t pos = y * _width + x;
    return this->buffer[pos];
}

void ST7735FB::animate(struct sprite *s) {
    s->currentframe++;
    if (s->currentframe >= s->frames) {
        s->currentframe = 0;
    }
}

void ST7735FB::animatePingPong(struct sprite *s) {
    s->currentframe += s->animdir;
    if (s->currentframe >= s->frames) {
        s->animdir = -1;
        s->currentframe = s->frames-1;
    }
    if (s->currentframe < 0) {
        s->animdir = 1;
        s->currentframe = 0;
    }
}

struct sprite *ST7735FB::collidesWith(struct sprite *s) {
    struct sprite *scan;
    int16_t sl = s->xpos;
    int16_t st = s->ypos;
    int16_t sr = s->xpos + s->width;
    int16_t sb = s->ypos + s->height;
    for (scan = this->sprites; scan; scan = scan->next) {
        if (scan == s) continue;
        int16_t dl= scan->xpos;
        int16_t dt = scan->ypos;
        int16_t dr = scan->xpos + scan->width;
        int16_t db = scan->ypos + scan->height;

        if (sl <= dr && sr >= dl && st <= db && sb >= dt) {
            return scan;
        }
    }
    return NULL;
}

void ST7735FB::moveTo(struct sprite *s, int16_t x, int16_t y) {
    s->xpos = x;
    s->ypos = y;
}

void ST7735FB::moveBy(struct sprite *s, int16_t dx, int16_t dy) {
    s->xpos += dx;
    s->ypos += dy;
}

struct sprite *ST7735FB::firstSprite() {
    selectedSprite = this->sprites;
    return selectedSprite;
}

struct sprite *ST7735FB::nextSprite() {
    if (selectedSprite == NULL) {
        return NULL;
    }
    selectedSprite = selectedSprite->next;
    return selectedSprite;
}

int8_t ST7735FB::getSprite(struct sprite *s, uint8_t n) {
    n = n & 0x07;
    return s->store[n];
}

void ST7735FB::setSprite(struct sprite *s, uint8_t n, int8_t v) {
    n = n & 0x07;
    s->store[n] = v;
}


