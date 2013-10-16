#include <TFT.h>

Framebuffer::Framebuffer() {
    _width = _height = _masterWidth = _masterHeight = 0;
    sprites = NULL;
    buffer = NULL;
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

Framebuffer::Framebuffer(int16_t w, int16_t h, DataStore *b) {
    _width = w;
    _height = h;
    _masterWidth = w;
    _masterHeight = h;
    sprites = NULL;
    buffer = b;
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

void Framebuffer::initializeDevice() {
    sprites = NULL;
	buffer->initializeDevice();
}

void Framebuffer::translateCoordinates(int16_t *x, int16_t *y) {
    int16_t t;
    switch (rotation) {
        case 1:
            t = *x;
            *x = _width - *y;
            *y = t;
            break;
        case 2:
            *x = _width - *x;
            *y = _height - *y;
            break;
        case 3:
            t = *x;
            *x = *y;
            *y = _height - t;
            break;
    }
}

void Framebuffer::setPixel(int16_t x, int16_t y, uint16_t color) {
    translateCoordinates(&x, &y);

    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    
    uint8_t pcol = color & 0xFF;
    uint32_t pos = y * _width + x;
    bufferWrite(pos, pcol);
}

void Framebuffer::fillScreen(uint16_t color) {
    buffer->setAll8(color);
}

void Framebuffer::drawVerticalLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    drawLine(x, y, x, y+h-1, color);
}

void Framebuffer::drawHorizontalLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    drawLine(x, y, x+w-1, y, color);
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
    palette[color] = color565(r, g, b);
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

void Framebuffer::loadPalette(Framebuffer *fb) {
    memcpy(palette, fb->palette, 256);
}

void Framebuffer::drawIndexed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            setPixel(x + i, y + j, data[pos]);
        }
    }
}

void Framebuffer::drawIndexed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t t) {
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

void Framebuffer::drawTransformed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t transform) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            switch (transform) {
                default:
                    setPixel(x + i, y + j, data[pos]);
                    break;
                case MirrorH:
                    setPixel(w - (x + i) - 1, y + j, data[pos]);
                    break;
                case MirrorV:
                    setPixel(x + i, h - (y + j) - 1, data[pos]);
                    break;
                case Rotate180:
                    setPixel(w - (x + i) - 1, h - (y + j) - 1, data[pos]);
                    break;
            }
        }
    }
}

void Framebuffer::drawTransformed(int16_t x, int16_t y, const uint8_t *data, uint16_t w, uint16_t h, uint8_t transform, uint8_t t) {
    uint32_t pos;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            if (data[pos] != t) {
                switch (transform) {
                    default:
                        setPixel(x + i, y + j, data[pos]);
                        break;
                    case MirrorH:
                        setPixel(w - (x + i) - 1, y + j, data[pos]);
                        break;
                    case MirrorV:
                        setPixel(x + i, h - (y + j) - 1, data[pos]);
                        break;
                    case Rotate180:
                        setPixel(w - (x + i) - 1, h - (y + j) - 1, data[pos]);
                        break;
                }
            }
        }
    }
}

void Framebuffer::drawIndexed(int16_t x, int16_t y, Framebuffer *fb) {
    uint32_t pos;
    uint16_t w = fb->_width;
    uint16_t h = fb->_height;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            setPixel(x + i, y + j, fb->bufferRead(pos));
        }
    }
}

void Framebuffer::drawIndexed(int16_t x, int16_t y, Framebuffer *fb, uint8_t t) {
    uint32_t pos;
    uint16_t w = fb->_width;
    uint16_t h = fb->_height;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            if (fb->bufferRead(pos) != t) {
                setPixel(x + i, y + j, fb->bufferRead(pos));
            }
        }
    }
}

void Framebuffer::drawTransformed(int16_t x, int16_t y, Framebuffer *fb, uint8_t transform) {
    uint32_t pos;
    uint16_t w = fb->_width;
    uint16_t h = fb->_height;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            switch (transform) {
                default:
                    setPixel(x + i, y + j, fb->bufferRead(pos));
                    break;
                case MirrorH:
                    setPixel(w - (x + i) - 1, y + j, fb->bufferRead(pos));
                    break;
                case MirrorV:
                    setPixel(x + i, h - (y + j) - 1, fb->bufferRead(pos));
                    break;
                case Rotate180:
                    setPixel(w - (x + i) - 1, h - (y + j) - 1, fb->bufferRead(pos));
                    break;
            }
        }
    }
}

void Framebuffer::drawTransformed(int16_t x, int16_t y, Framebuffer *fb, uint8_t transform, uint8_t t) {
    uint32_t pos;
    uint16_t w = fb->_width;
    uint16_t h = fb->_height;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pos = j * w + i;
            if (fb->bufferRead(pos) != t) {
                switch (transform) {
                    default:
                        setPixel(x + i, y + j, fb->bufferRead(pos));
                        break;
                    case MirrorH:
                        setPixel(w - (x + i) - 1, y + j, fb->bufferRead(pos));
                        break;
                    case MirrorV:
                        setPixel(x + i, h - (y + j) - 1, fb->bufferRead(pos));
                        break;
                    case Rotate180:
                        setPixel(w - (x + i) - 1, h - (y + j) - 1, fb->bufferRead(pos));
                        break;
                }
            }
        }
    }
}

struct sprite * Framebuffer::addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f) {
    struct sprite *scan;
    struct sprite *s = (struct sprite *)malloc(sizeof(struct sprite));
    if (!s) {
        return NULL;
    }
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
    if (sprites == NULL) {
        sprites = s;
        return s;
    }
    for (scan = sprites; scan->next; scan = scan->next);
    scan->next = s;
    return s;
}

void Framebuffer::removeSprite(struct sprite *s) {
    struct sprite *scan;
    struct sprite *last = NULL;

    if (sprites == s) {
        scan = s;
        sprites = sprites->next;
        free(s);
        return;
    }

    for (scan = sprites; scan; scan = scan->next) {
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
    if (sprites == NULL) {
        return NULL;
    }
    for (scan = sprites; scan; scan = scan->next) {
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

uint16_t Framebuffer::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }
    struct sprite *s = spriteAt(x, y);
    if (s) {
        uint32_t offset = s->width * s->height * s->currentframe;
        uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
        return palette[color];
    }
    uint32_t pos = y * _width + x;
    return palette[bufferRead(pos)];
}

void Framebuffer::getScanLine(uint16_t y, uint16_t *data) {
	uint8_t bufferdata[_masterWidth];
	buffer->read8(y * _masterWidth, bufferdata, _masterWidth);
	for (uint16_t x = 0; x < _masterWidth; x++) {
        if (sprites != NULL) {
            struct sprite *s = spriteAt(x, y);
            if (s) {
                uint32_t offset = s->width * s->height * s->currentframe;
                uint8_t color = s->data[offset + (y - s->ypos) * s->width + (x - s->xpos)];
                data[x] = palette[color];
            } else {
                data[x] = palette[bufferdata[x]];
            }
        } else {
            data[x] = palette[bufferdata[x]];
        }
	}
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
    for (scan = sprites; scan; scan = scan->next) {
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
    selectedSprite = sprites;
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

void Framebuffer::copyRect(int16_t dx, int16_t dy, int16_t sx, int16_t sy, uint16_t w, uint16_t h) {
    uint32_t dpos;
    uint32_t spos;
    translateCoordinates(&dx, &dy);
    for (int y = 0; y < w; y++) {
        for (int x = 0; x < h; x++) {
            if (sx > dx && sy > dy) {
                dpos = (y + dy) * _width + (x + dx);
                spos = (y + sy) * _width + (x + sx);
            } else if(sx <= dx && sy > dy) {
                dpos = (y + dy) * _width + ((w - x) + dx);
                spos = (y + sy) * _width + ((w - x) + sx);
            } else if(sx > dx && sy <= dy) {
                dpos = ((h - y) + dy) * _width + (x + dx);
                spos = ((h - y) + sy) * _width + (x + sx);
            } else if(sx <= dx && sy <= dy) {
                dpos = ((h - y) + dy) * _width + ((w - x) + dx);
                spos = ((h - y) + sy) * _width + ((w - x) + sx);
            }
            bufferWrite(dpos, bufferRead(spos));
        }
    }
}

void Framebuffer::drawRLE(int16_t x, int16_t y, const uint8_t *data) {
    uint32_t ptr = 0;
    if (data[0] != 'R' || data[1] != 'L' || data[2] != 'E') {
        return;
    }
    ptr = 3;
    uint8_t depth = data[3];
    if (depth != 8 && depth != 16) {
        return;
    }
    uint32_t dlen = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
    uint16_t w = data[8] << 8 | data[9];
    uint16_t h = data[10] << 8 | data[11];
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < dlen) {
        if (data[12+i] != data[13+i]) {
            setPixel(x + px, y + py, data[12+i]);
            i++;
            px ++;
            if (px == w) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = data[12+i];
            if (depth == 8) {
                len = data[14+i];
                i += 3;
            } else if (depth == 16) {
                len = data[14+i] << 8 | data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                setPixel(x + px, y + py, col);
                px ++;
                if (px == w) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

void Framebuffer::drawRLE(int16_t x, int16_t y, const uint8_t *data, uint8_t t) {
    uint32_t ptr = 0;
    if (data[0] != 'R' || data[1] != 'L' || data[2] != 'E') {
        return;
    }
    ptr = 3;
    uint8_t depth = data[3];
    if (depth != 8 && depth != 16) {
        return;
    }
    uint32_t dlen = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
    uint16_t w = data[8] << 8 | data[9];
    uint16_t h = data[10] << 8 | data[11];
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < dlen) {
        if (data[12+i] != data[13+i]) {
            if (data[12+i] != t) {
                setPixel(x + px, y + py, data[12+i]);
            }
            i++;
            px ++;
            if (px == w) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = data[12+i];
            if (depth == 8) {
                len = data[14+i];
                i += 3;
            } else if (depth == 16) {
                len = data[14+i] << 8 | data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                if (col != t) {
                    setPixel(x + px, y + py, col);
                }
                px ++;
                if (px == w) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

void Framebuffer::drawRLETransformed(int16_t x, int16_t y, const uint8_t *data, uint8_t transform) {
    uint32_t ptr = 0;
    if (data[0] != 'R' || data[1] != 'L' || data[2] != 'E') {
        return;
    }
    ptr = 3;
    uint8_t depth = data[3];
    if (depth != 8 && depth != 16) {
        return;
    }
    uint32_t dlen = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
    uint16_t w = data[8] << 8 | data[9];
    uint16_t h = data[10] << 8 | data[11];
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < dlen) {
        if (data[12+i] != data[13+i]) {
            switch (transform) {
                default:
                    setPixel(x + px, y + py, data[12+i]);
                    break;
                case MirrorH:
                    setPixel(w - (x + px) - 1, y + py, data[12+i]);
                    break;
                case MirrorV:
                    setPixel(x + px, h - (y + py) - 1, data[12+i]);
                    break;
                case Rotate180:
                    setPixel(w - (x + px) - 1, h - (y + py) - 1, data[12+i]);
                    break;
            }
            i++;
            px ++;
            if (px == w) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = data[12+i];
            if (depth == 8) {
                len = data[14+i];
                i += 3;
            } else if (depth == 16) {
                len = data[14+i] << 8 | data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                switch (transform) {
                    default:
                        setPixel(x + px, y + py, col);
                        break;
                    case MirrorH:
                        setPixel(w - (x + px) - 1, y + py, col);
                        break;
                    case MirrorV:
                        setPixel(x + px, h - (y + py) - 1, col);
                        break;
                    case Rotate180:
                        setPixel(w - (x + px) - 1, h - (y + py) - 1, col);
                        break;
                }
                px ++;
                if (px == w) {
                    px = 0;
                    py++;
                }
            }
        }
    }

}

void Framebuffer::drawRLETransformed(int16_t x, int16_t y, const uint8_t *data, uint8_t transform, uint8_t t) {
    uint32_t ptr = 0;
    if (data[0] != 'R' || data[1] != 'L' || data[2] != 'E') {
        return;
    }
    ptr = 3;
    uint8_t depth = data[3];
    if (depth != 8 && depth != 16) {
        return;
    }
    uint32_t dlen = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7];
    uint16_t w = data[8] << 8 | data[9];
    uint16_t h = data[10] << 8 | data[11];
    int16_t px = 0;
    int16_t py = 0;

    uint32_t i = 0;
    while (i < dlen) {
        if (data[12+i] != data[13+i]) {
            if (data[12+i] != t) {
                switch (transform) {
                    default:
                        setPixel(x + px, y + py, data[12+i]);
                        break;
                    case MirrorH:
                        setPixel(w - (x + px) - 1, y + py, data[12+i]);
                        break;
                    case MirrorV:
                        setPixel(x + px, h - (y + py) - 1, data[12+i]);
                        break;
                    case Rotate180:
                        setPixel(w - (x + px) - 1, h - (y + py) - 1, data[12+i]);
                        break;
                }
            }
            i++;
            px ++;
            if (px == w) {
                px = 0;
                py++;
            }
        } else {
            uint16_t len = 0;
            uint8_t col = data[12+i];
            if (depth == 8) {
                len = data[14+i];
                i += 3;
            } else if (depth == 16) {
                len = data[14+i] << 8 | data[15+i];
                i += 4;
            }
            for (uint32_t j = 0; j < len; j++) {
                if (col != t) {
                    switch (transform) {
                        default:
                            setPixel(x + px, y + py, col);
                            break;
                        case MirrorH:
                            setPixel(w - (x + px) - 1, y + py, col);
                            break;
                        case MirrorV:
                            setPixel(x + px, h - (y + py) - 1, col);
                            break;
                        case Rotate180:
                            setPixel(w - (x + px) - 1, h - (y + py) - 1, col);
                            break;
                    }
                }
                px ++;
                if (px == w) {
                    px = 0;
                    py++;
                }
            }
        }
    }
}

uint8_t Framebuffer::bufferRead(uint32_t addr) {
    return buffer->read8(addr);
}

void Framebuffer::bufferWrite(uint32_t addr, uint8_t value) {
    buffer->write8(addr, value);
}

void Framebuffer::setRotation(uint8_t rot) {
    rotation = rot % 4;
}

uint16_t Framebuffer::getWidth() {
    if (rotation == 0 || rotation == 2) {
        return _width;
    }
    return _height;
}

uint16_t Framebuffer::getHeight() {
    if (rotation == 0 || rotation == 2) {
        return _height;
    }
    return _width;
}


