#include <TFT.h>

Framebuffer::Framebuffer() {
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
}

void Framebuffer::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x > getWidth() || y < 0 || y > getHeight()) {
        return;
    }
    uint8_t pcol = color & 0xFF;
    uint32_t pos = y * getWidth() + x;
    setBuffer(pos, pcol);
}

void Framebuffer::fillScreen(uint16_t color) {
    fillBuffer(color & 0xFF);
}

void Framebuffer::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    this->drawLine(x, y, x, y+h-1, color);
}


void Framebuffer::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    this->drawLine(x, y, x+w-1, y, color);
}

void Framebuffer::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  for (int16_t i=x; i<x+w; i++) {
    drawVerticalLine(i, y, h, color);
  }
}

void Framebuffer::setColor(uint8_t color, uint16_t rgb) {
    palette[color] = rgb;
}

void Framebuffer::setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b) {
    palette[color] = this->color565(r, g, b);
}

void Framebuffer::loadPalette(const uint16_t *p) {
    for (int i = 0; i < 256; i++) {
        setColor(i, p[i]);
    }
}

void Framebuffer::loadPalette(const uint8_t p[256][3]) {
    for (int i = 0; i < 256; i++) {
        setColor(i, p[i][0], p[i][1], p[i][2]);
    }
}

void Framebuffer::drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            setPixel(x + i, y + j, data[pos]);
        }
    }
}

void Framebuffer::drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t t) {
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

struct sprite * Framebuffer::addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f) {
    struct sprite *scan;
    struct sprite *s = (struct sprite *)malloc(sizeof(struct sprite));
    s->data = data;
    s->width = w;
    s->height = h;
    s->xpos = getWidth()+1;
    s->ypos = getHeight()+1;
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

void Framebuffer::removeSprite(struct sprite *s) {
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

struct sprite *Framebuffer::spriteAt(int16_t x, int16_t y) {
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

uint8_t Framebuffer::colorAt(int16_t x, int16_t y) {
    struct sprite *s = this->spriteAt(x, y);
    if (s) {
        uint32_t offset = s->width * s->height * s->currentframe;
        uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
        return color;
    }
    uint32_t pos = y * getWidth() + x;
    return getBuffer(pos);
}

void Framebuffer::animate(struct sprite *s) {
    s->currentframe++;
    if (s->currentframe >= s->frames) {
        s->currentframe = 0;
    }
}

void Framebuffer::animatePingPong(struct sprite *s) {
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

struct sprite *Framebuffer::collidesWith(struct sprite *s) {
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

void Framebuffer::moveTo(struct sprite *s, int16_t x, int16_t y) {
    s->xpos = x;
    s->ypos = y;
}

void Framebuffer::moveBy(struct sprite *s, int16_t dx, int16_t dy) {
    s->xpos += dx;
    s->ypos += dy;
}

struct sprite *Framebuffer::firstSprite() {
    selectedSprite = this->sprites;
    return selectedSprite;
}

struct sprite *Framebuffer::nextSprite() {
    if (selectedSprite == NULL) {
        return NULL;
    }
    selectedSprite = selectedSprite->next;
    return selectedSprite;
}

int8_t Framebuffer::getSprite(struct sprite *s, uint8_t n) {
    n = n & 0x07;
    return s->store[n];
}

void Framebuffer::setSprite(struct sprite *s, uint8_t n, int8_t v) {
    n = n & 0x07;
    s->store[n] = v;
}

void Framebuffer::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            setPixel(y0, x0, color);
        } else {
            setPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

uint16_t Framebuffer::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

