ST7735 Buffered
===============

This is a framebuffered extension to the chipKIT ST7735 library.  It provides
an 8-bit framebuffer with 256 colour palette with high-speed full-frame push
functionality and animated sprites.

Relies on DSPI, GFX and ST7735:

    #include <DSPI.h>
    #include <GFX.h>
    #include <ST7735.h>
    #include <ST7735B.h>

Constructors of the ST7735 are mirrored, so can operate in the same modes as
the normal ST7735 library, including all functions of that library.  It simply
inherits ST7735 as a base class.

Colour Management
-----------------

Palette functions are controlled by the setColor() and loadPalette() functions:

    void setColor(uint8_t color, uint16_t rgb);
    void setColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b);

These two functions set a specific entry in the palette to a certain colour, either
in 16-but 565 RGB format or using individual 8-bit R G and B values.

An entire palette array (either 256 16-bit 565 values, or 256x3 8-bit values) can
be loaded into the palette using these two functions:

    void loadPalette(const uint16_t *p);
    void loadPalette(const uint8_t p[256][3]);

The colour at any point on the screen can be retrieved using:

    uint8_t colorAt(int16_t x, int16_t y);

This is a helper function which returns the 16-bit 565 RGB colour at a specific location
on the screen.  This includes any sprites which may be present at that location.

Drawing
-------

A new bitmap drawing routine which uses an array of 8-bit values instead of 16-bit
values has also been provided.  This doesn't (yet) support transparency, although
that is merely an oversight and will be added shortly.

    void drawIndexed(uint16_t x, uint16_t y, const uint8_t *data, uint16_t w, uint16_t h);

Sprites
-------

Sprites are calculated at update time.  They are overlaid over the display framebuffer
and do not affect the contents of the framebuffer in any way.  A constructor function
creates a struct sprite * structure and appends it to a linked list of sprites.  The
data for a sprite consists of an array of 8-bit values, each value representing a colour
from the palette.  Multiple frames are appended to this array and their position within
the array is calculated from the dimenstions of the sprite.

    struct sprite * addSprite(const uint8_t *data, uint16_t w, uint16_t h, uint8_t t, uint8_t f);

"w" and "h" are the width and height of an individual frame in the sprite (each frame
must be the same size), "t" is the transparency colour, and "f" is the number of frames
present in the sprite.

    struct sprite *spriteAt(int16_t x, int16_t y);

This function returns the sprite visible at a specific point on the screen.  Takes into
account transparency when calculating which sprite is visible.

    void animate(struct sprite *s);
    void animatePingPong(struct sprite *s);

These two functions animate the sprite.  The first steps to the next frame in the sequence,
and when it reaches the end it recycles from the beginning again.  The second, when it reaches
the end, changes direction instead.

    struct sprite *collidesWith(struct sprite *s);

This function returns the first sprite found to be colliding with the specified sprite, or
NULL if no sprite is colliding.

    void removeSprite(struct sprite *s);

Removes a sprite from the internal linked list.  The list closes up around the gap and the
memory for the sprite is freed.

Sprites can be moved around the screen with the functions:

    void moveTo(struct sprite *s, int16_t x, int16_t y);
    void moveBy(struct sprite *s, int16_t dx, int16_t dy);

moveTo() places the sprite at a specified location on the screen.   moveBy() moves it from its
current location to a new one by a specified amount.

The sprite list can be iterated over using the following functions:

    struct sprite *firstSprite();
    struct sprite *nextSprite();

The first gets the first sprite in the list and should be called first.  The second gets the
next sprite, or NULL if there are no more sprites.  Can be used in a for loop:

    for (struct sprite *spr = tft.firstSprite(); spr; spr = tft.nextSprite()) {
        ...
    }

Sprites also contain a small (8 byte) memory area for storing information about an individual
sprite.  This can be accessed using:

    int8_t getSprite(struct sprite *s, uint8_t n);
    void setSprite(struct sprite *s, uint8_t n, int8_t v);

For low-level access to a sprite, the format of the structure is as follows:

    struct sprite {
        int16_t xpos;           // The X and Y position of the sprite
        int16_t ypos;
        uint16_t width;         // The frame width and height
        uint16_t height;
        uint8_t transparent;    // The colour used as transparent
        int8_t frames;          // The number of frames in the sprite
        int8_t currentframe;    // The currently active frame
        int8_t animdir;         // Direction the animation is running (for ping pong)
        int8_t store[8];        // Small data store area
        const uint8_t *data;    // Pointer to the sprite graphic data
        struct sprite *next;    // Linked list pointer to the next sprite
    };

Screen Control
--------------

    void update();

This is probably the single most important function in the buffered library.  It sends the
entire framebuffer to the display in a single transaction as fast as the hardware can take
it.  This function should be called to make any drawing operations that have been performed
visible on the display.

Overloaded functions
--------------------

This is a list of the functions that have been overloaded from the base class by this class:

    void drawPixel(int16_t, int16_t, uint16_t);
    void fillScreen(uint16_t);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);





