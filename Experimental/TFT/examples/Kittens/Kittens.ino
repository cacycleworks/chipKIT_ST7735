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

DSPI0 spi;
TFTDSPI mySpi(&spi, ADA_CS, ADA_DC);

ST7735FB tft(&mySpi, ST7735FB::BlackTab);

void setup() {
	tft.initializeDevice();
	tft.setRotation(1);
	tft.fillScreen(0);
	tft.update();
}

void loop()
{
	tft.loadPalette(kitten1_cmap);
	tft.drawIndexed(0, 0, kitten1, 160, 128);
	tft.update();
	delay(5000);

	tft.loadPalette(kitten2_cmap);
	tft.drawIndexed(0, 0, kitten2, 160, 128);
	tft.update();
	delay(5000);
	
	tft.loadPalette(kitten3_cmap);
	tft.drawIndexed(0, 0, kitten3, 160, 128);
	tft.update();
	delay(5000);

	tft.loadPalette(kitten4_cmap);
	tft.drawIndexed(0, 0, kitten4, 160, 128);
	tft.update();
	delay(5000);
}
