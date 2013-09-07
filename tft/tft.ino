/////////////////////////////////////////////////////////////////////////
// Adafruit 1.8TFT w/joystick 160x128 in landscape (128x160)
#include <SPI.h>
#include <GFX.h>
#include <ST7735.h>

//  UNO pins
#define ADA_SCLK 13
#define ADA_MOSI 11
#define ADA_CS  10
// pinout for Mega: http://forums.adafruit.com/viewtopic.php?uid=115205&f=31&t=36738&start=0
//#define ADA_SCLK	52 //#define ADA_MOSI	51 //#define ADA_CS		53
#define ADA_DC 		8

ST7735 tft = ST7735( ADA_CS, ADA_DC );

//  Adafruit pins on the shield and what the h... "SPI:" below means part of hardware SPI
//  13 - SPI:SCLK, serial data clock shared between TFT and SD Card
//  12 - SPI:MISO, data sent from shield to controller (SD Card)
//  11 - SPI:MOSI, data sent to shield from controller, both TFT and SD Card
//  10 - SPI:SS, TFT slave select aka chip select
//   8 - DC or RS, "data channel" or "register select", a low on this pin tells the TFT it is about to receive a command, while high means data is incoming
//   4 - SS for SD Card
//  A3 - Analog input for the joystick; each of 5 inputs are in a resistor network

// TFT Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define ORANGE   0xFA60
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
#define GRAY     0xCCCC


char text[28];
static char sometext[]={"0123456789abcdef0123456789"};

void setup(){
	tft.initR( INITR_BLACKTAB );
	tft.setRotation(1);
	tft.fillScreen(BLACK);
	tft.setTextColor(RED);
	tft.setCursor(0, 10);  tft.setTextSize(1); //  1 = 5x8, 2 = 10x16; chars leave blank pixel on bottom
}
uint8_t y = 150;
void loop()
{
	if( y > 140 ) {
		tft.fillScreen(BLACK);
		y=10;
		tft.setCursor(0, 10);
		tft.setTextColor(RED);
		//	size 1 "0123456789abcdef0123456789"
		tft.print( "Boo! Im a catchedge ghost!" );
		tft.setTextColor(BLUE);
	}
	//	text size 1 "0123456789abcdef0123456789"  16 lines of 0x20 (decimal 26) characters
	tft.print( sometext );
	y+=10;
	delay(300);
}

