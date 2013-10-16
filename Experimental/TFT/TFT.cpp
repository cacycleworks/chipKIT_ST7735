//	GFX code to get Adafruit 1.8" TFT shield working with chipKIT uc32 and UNO32
//	This code derived from Adafruit_GFX library. See bottom of .h file for their license stuff.
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same license thing, whatever
////////////////////////////////////////////////////////////////////////////////
#include <TFT.h>

TFT::TFT() {
    _comm = NULL;
    cursor_y = cursor_x = 0;
    textcolor = 0xFFFF;
    textbgcolor = 0;
    wrap = true;
    font = Fonts::Default;
}

TFT::TFT(TFTCommunicator *comm) {
    _comm = comm;
    cursor_y = cursor_x = 0;
    textcolor = 0xFFFF;
    textbgcolor = 0;
    wrap = true;
    font = Fonts::Default;
}


// draw a circle outline
void TFT::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    setPixel(x0, y0+r, color);
    setPixel(x0, y0-r, color);
    setPixel(x0+r, y0, color);
    setPixel(x0-r, y0, color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        setPixel(x0 + x, y0 + y, color);
        setPixel(x0 - x, y0 + y, color);
        setPixel(x0 + x, y0 - y, color);
        setPixel(x0 - x, y0 - y, color);
        setPixel(x0 + y, y0 + x, color);
        setPixel(x0 - y, y0 + x, color);
        setPixel(x0 + y, y0 - x, color);
        setPixel(x0 - y, y0 - x, color);
    }
}

void TFT::drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            setPixel(x0 + x, y0 + y, color);
            setPixel(x0 + y, y0 + x, color);
        } 
        if (cornername & 0x2) {
            setPixel(x0 + x, y0 - y, color);
            setPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            setPixel(x0 - y, y0 + x, color);
            setPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            setPixel(x0 - y, y0 - x, color);
            setPixel(x0 - x, y0 - y, color);
        }
    }
}

void TFT::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    drawVerticalLine(x0, y0-r, 2*r+1, color);
    fillCircleHelper(x0, y0, r, 3, 0, color);
}

// used to do circles and roundrects!
void TFT::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
            drawVerticalLine(x0+x, y0-y, 2*y+0+delta, color);
            drawVerticalLine(x0+y, y0-x, 2*x+0+delta, color);
        }
        if (cornername & 0x2) {
            drawVerticalLine(x0-x, y0-y, 2*y+0+delta, color);
            drawVerticalLine(x0-y, y0-x, 2*x+0+delta, color);
        }
    }
}

// bresenham's algorithm - thx wikpedia
void TFT::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
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


// draw a rectangle
void TFT::drawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    drawHorizontalLine(x, y, w, color);
    drawHorizontalLine(x, y+h-1, w, color);
    drawVerticalLine(x, y, h, color);
    drawVerticalLine(x+w-1, y, h, color);
}

void TFT::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            setPixel(x + j, y + i, color);
        }
    }
}


void TFT::fillScreen(uint16_t color) {
    fillRectangle(0, 0, _width, _height, color);
}

// draw a rounded rectangle!
void TFT::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    // smarter version
    drawHorizontalLine(x+r  , y    , w-2*r, color); // Top
    drawHorizontalLine(x+r  , y+h-1, w-2*r, color); // Bottom
    drawVerticalLine(  x    , y+r  , h-2*r, color); // Left
    drawVerticalLine(  x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    drawCircleHelper(x+r    , y+r    , r, 1, color);
    drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// fill a rounded rectangle!
void TFT::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    // smarter version
    fillRectangle(x+r, y, w-2*r, h, color);

    // draw four corners
    fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// draw a triangle!
void TFT::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}

// fill a triangle!
void TFT::fillTriangle ( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        std::swap(y0, y1); std::swap(x0, x1);
    }
    if (y1 > y2) {
        std::swap(y2, y1); std::swap(x2, x1);
    }
    if (y0 > y1) {
        std::swap(y0, y1); std::swap(x0, x1);
    }

    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        drawHorizontalLine(a, y0, b-a+1, color);
        return;
    }

    int16_t
        dx01 = x1 - x0,
        dy01 = y1 - y0,
        dx02 = x2 - x0,
        dy02 = y2 - y0,
        dx12 = x2 - x1,
        dy12 = y2 - y1,
        sa   = 0,
        sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) std::swap(a,b);
        drawHorizontalLine(a, y, b-a+1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) std::swap(a,b);
        drawHorizontalLine(a, y, b-a+1, color);
    }
}

void TFT::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
    int16_t i, j, byteWidth = (w + 7) / 8;

    for(j=0; j<h; j++) {
        for(i=0; i<w; i++ ) {
            if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
                setPixel(x+i, y+j, color);
            }
        }
    }
}

void TFT::drawRGB(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    int16_t i, j;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            setPixel(x+i, y+j, bitmap[j * w + i]);
        }
    }
}

void TFT::drawRGBA(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h, uint16_t trans) {
    int16_t i, j;
    uint16_t col;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            col = bitmap[j * w + i];
            if (col != trans) {
                setPixel(x+i, y+j, col);
            }
        }
    }
}

uint16_t TFT::stringWidth(char *text) {
    uint16_t w = 0;

    uint8_t lpc = font[0];
    uint8_t bpl = font[1];
    uint8_t startGlyph = font[2]; // First character in data
    uint8_t endGlyph = font[3]; // Last character in data

    for (char *t = text; *t; t++) {
        char c = *t;
        if (c >= startGlyph && c <= endGlyph) {
            uint8_t co = c - startGlyph;
            uint16_t charstart = (co * ((lpc * bpl) + 1)) + 4; // Start of character data
            uint8_t charwidth = font[charstart++];
            w += charwidth;
        }
    }
    return w;
}
        

#if ARDUINO >= 100
size_t TFT::write(uint8_t c) {
#else
void TFT::write(uint8_t c) {
#endif
    uint8_t lpc = font[0];
    uint8_t bpl = font[1];
    uint8_t startGlyph = font[2]; // First character in data
    uint8_t endGlyph = font[3]; // Last character in data

    if (c == '\n') {
        cursor_y += lpc;
        cursor_x = 0;
    } else if (c == '\r') {
        // skip em
    } else {
        if (c >= startGlyph && c <= endGlyph) {
            uint8_t co = c - startGlyph;
            uint16_t charstart = (co * ((lpc * bpl) + 1)) + 4; // Start of character data
            uint8_t charwidth = font[charstart++];
            if (wrap && (cursor_x > (_width - charwidth))) {
                cursor_y += lpc;
                cursor_x = 0;
            }
            cursor_x += drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor);
        }
    }
#if ARDUINO >= 100
    return 1;
#endif
}

// draw a character
uint8_t TFT::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg) {

    uint8_t lpc = font[0];  // Lines per character
    uint8_t bpl = font[1];  // Bytes per line
    uint8_t startGlyph = font[2]; // First character in data
    uint8_t endGlyph = font[3]; // Last character in data

    if (c < startGlyph || c > endGlyph) {
        return 0;
    }

    c = c - startGlyph;

    // Start of this character's data is the character number multiplied by the
    // number of lines in a character (plus one for the character width) multiplied
    // by the number of bytes in a line, and then offset by 4 for the header.
    uint32_t charstart = (c * ((lpc * bpl) + 1)) + 4; // Start of character data
    uint8_t charwidth = font[charstart++]; // The first byte of a block is the width of the character

    for (int8_t i = 0; i < lpc; i++ ) {
        uint64_t line = 0;
        for (int8_t j = 0; j < bpl; j++) {
            line <<= 8;
            line |= font[charstart + (i * bpl) + j];
        }

        for (int8_t j = 0; j < charwidth; j++) {
            if (line & 0x1) {
                setPixel(x+j, y+i, color);
            } else if (bg != color) {
                setPixel(x+j, y+i, bg);
            }
            line >>= 1;
        }
    }
    return charwidth;
}

void TFT::setCursor(int16_t x, int16_t y) {
    cursor_x = x;
    cursor_y = y;
}
int16_t TFT::getCursor(boolean x) {
    if( x )
        return cursor_x;
    return cursor_y;
}

void TFT::setTextColor(uint16_t c) {
    textcolor = c;
}

void TFT::setTextColor(uint16_t fg, uint16_t bg) {
   textcolor = fg;
   textbgcolor = bg;
}

void TFT::invertTextColor( ){
	setTextColor( textbgcolor, textcolor );
}

void TFT::setTextWrap(boolean w) {
  wrap = w;
}

uint16_t TFT::color565(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void TFT::setFont(const uint8_t *f) {
    font = f;
}

void TFT::update(Framebuffer *fb) {
    update(fb, 0, 0);
}

void TFT::update(Framebuffer *fb, int16_t dx, int16_t dy) {
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            setPixel(x, y, fb->colorAt(x + dx, y + dy));
        }
    }
}

uint16_t TFT::getTextColor() {
    return textcolor;
}
