#include <DSPI.h>
#include <GFX.h>
#include <ST7735.h>
#include <ST7735B.h>

#include "kitten1.h"
#include "kitten2.h"
#include "kitten3.h"
#include "kitten4.h"

#define ADA_SCLK	13
#define ADA_MOSI	11
#define ADA_CS		IO11
#define ADA_DC		IO12

DSPI1 spi;
ST7735B tft = ST7735B(ADA_CS, ADA_DC, &spi);

void setup() {
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.setTextSize(1);
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
