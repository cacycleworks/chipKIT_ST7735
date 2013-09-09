#include <DSPI.h>
#include <TFT.h>

#include "kitten1.h"
#include "kitten2.h"
#include "kitten3.h"
#include "kitten4.h"

#define ADA_SCLK	13
#define ADA_MOSI	11
#define ADA_CS		10
#define ADA_DC		8

// Set up the screen to use
DSPI0 spi;
TFTDSPI mySpi(&spi, ADA_CS, ADA_DC);
ST7735 tft(&mySpi, ST7735::BlackTab);

// Create a framebuffer to store the image while we draw it
uint8_t buffer[160 * 128];
Framebuffer fb(160, 128, buffer);

void setup() {
	tft.initializeDevice();
	tft.setRotation(1);

	// Start with a black screen
	fb.fillScreen(0);
	tft.update(fb);
}

void loop()
{
	// Set the palette in the framebuffer to the first image's palette
	fb.loadPalette(kitten1_cmap);
	// Draw the image into the framebuffer
	fb.drawIndexed(0, 0, kitten1, 160, 128);
	// Push the contents of the framebuffer out to the display
	tft.update(fb);
	delay(5000);

	// And do the same with the other images.
	fb.loadPalette(kitten2_cmap);
	fb.drawIndexed(0, 0, kitten2, 160, 128);
	tft.update(fb);
	delay(5000);
	
	fb.loadPalette(kitten3_cmap);
	fb.drawIndexed(0, 0, kitten3, 160, 128);
	tft.update(fb);
	delay(5000);

	fb.loadPalette(kitten4_cmap);
	fb.drawIndexed(0, 0, kitten4, 160, 128);
	tft.update(fb);
	delay(5000);
}
