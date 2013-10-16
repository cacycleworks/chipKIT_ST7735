//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
static char version[]={"TFTDemo.ino v1.05 2013-SEP-06"};
char text[40];
//  Version 1.03 : 2013-SEP-04 : majenko updated GFX and ST7735 to work with DSPI! :-)
//  Version 1.04 : 2013-SEP-05 : tweaks to GFX to remove swap() macro and instead
//					use STL's std::swap() <-- needed for ANY STL libraries to compile.
//  Version 1.05 : 2013-SEP-06 : Software SPI implemented by majenko using shiftOut(); also created 8- and 16-bit versions of SPI write
////////////////////////////////////////////////////////////////////////////////
// Adafruit 1.8TFT w/joystick 160x128 in landscape (128x160)
//  Adafruit pins on the shield and why. "SPI:" below means part of hardware SPI
//  13 - SPI:SCLK, serial data clock shared between TFT and SD Card             Mega:52
//  12 - SPI:MISO, data sent from shield to controller (SD Card)                Mega:50
//  11 - SPI:MOSI, data sent to shield from controller, both TFT and SD Card    Mega:51
//  10 - SPI:SS, TFT slave select aka chip select                               Mega:53
//   8 - DC or RS for TFT, "data channel" or "register select", a low on this pin tells the TFT it is about to receive a command, while high means data is incoming
//   4 - SPI SS for SD Card
//  A3 - Analog input for the joystick; each of 5 inputs are in a resistor network
#include <DSPI.h>
#include <TFT.h>

//  UNO hardware SPI pins
#define ADA_SCLK 13
#define ADA_MOSI 11
#define ADA_CS  10
#define ADA_DC 	8
// analog pin 3 for button input
#define ADA_JOYSTICK A3

#define GLCD_DI 8
#define GLCD_CLK 9
#define GLCD_CS1 10
#define GLCD_CS2 11

#define GLCD_D0 34
#define GLCD_D1 35
#define GLCD_D2 36
#define GLCD_D3 37
#define GLCD_D4 38
#define GLCD_D5 39
#define GLCD_D6 40
#define GLCD_D7 41

//	SD card chip select digital pin 4 : No work yet for SD Card
//	#define SD_CS 4

// Choose your communicator.

// Hardware SPI on your channel of choice
DSPI0 spi;
//TFTPMP pmp;
TFTDSPI mySpi(&spi, PIN_D9, PIN_B15);

//DSPI1 spi;
//TFTDSPI mySpi(&spi, IO11, IO12);

// Software SPI
//TFTSoftSPI mySpi(ADA_MOSI, ADA_SCLK, ADA_CS, ADA_DC);

//TFTPar8 chip1(GLCD_CS1, GLCD_DI, GLCD_CLK, GLCD_D0, GLCD_D1, GLCD_D2, GLCD_D3, GLCD_D4, GLCD_D5, GLCD_D6, GLCD_D7);
//TFTPar8 chip2(GLCD_CS2, GLCD_DI, GLCD_CLK, GLCD_D0, GLCD_D1, GLCD_D2, GLCD_D3, GLCD_D4, GLCD_D5, GLCD_D6, GLCD_D7);

// Select your display
uPD161704A tft(&mySpi);
//ST7735 tft(&mySpi, ST7735::RedTab);
//ST7735 tft(&mySpi, ST7735::GreenTab);
//ST7735 tft(&mySpi, ST7735::TypeB);

//KS0108 tft(&chip1, &chip2);
//  Other definitions for the Ada shield and playing with it...
//  Joystick directions - Works with our screen rotation (1), yaay
enum { Neutral, Press, Up, Down, Right, Left };
const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };

//	char() values for some special characters defined in GFX.h static font[]
//  not sure what to call solid triangle arrow things, so "pyramids" = pyr  ??
enum arrows { uarr = 0x18, darr = 0x19, larr = 0x1b, rarr = 0x1a, upyr = 0x1e, dpyr = 0x1f, lpyr = 0x11, rpyr = 0x10 };

////////////////////////////////////////////////////////////////////////////////
void setup(){
//	analogWrite(3, 256);
	pinMode(PIN_D4, OUTPUT);
	digitalWrite(PIN_D4, HIGH);
	pinMode(PIN_D5, OUTPUT);
	digitalWrite(PIN_D5, HIGH);
	//  Setup the Adafruit 1.8" TFT
	tft.initializeDevice();    //  "tab color" from screen protector; there's RED and GREEN, too.
	tft.setRotation(0);
	cls();
	tft.setFont(Fonts::Topaz);
	tft.setTextColor(Color::Red);
}
////////////////////////////////////////////////////////////////////////////////
//  clearscreen helper for tft
void cls() {
	tft.fillScreen(Color::Green);
}
////////////////////////////////////////////////////////////////////////////////
void loop() {
	tft.setCursor(100, 100);
	tft.print(millis());
}
////////////////////////////////////////////////////////////////////////////////
//  note: button is handled in order of Neutral( or none ),
//	then Up, Down, Left, Right, Press in simple if-else-if
bool doMenu( void ){
	uint8_t b = checkJoystick();
	if( b == Neutral ){
		return false;   //  user input didn't happen
	}
	tft.setCursor(0,0);
	//  const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };
	if( b == Up ) {
		tft.setTextColor(Color::Pink);
		sprintf(text,"%6s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Down ) {
		tft.setTextColor(Color::Khaki);
		sprintf(text,"%6s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Left ) {
		tft.setTextColor(Color::RoyalBlue);
		sprintf(text,"%6s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Right ) {
		tft.setTextColor(Color::Violet);
		sprintf(text,"%6s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Press ) {
		tft.setTextColor(Color::Orange);
		sprintf(text,"%s\ncls();\ndelay(1500);\n", Buttons[b]);
		tft.print(text);
		delay(1500);
		cls();
	}
	return true;    //  user input happened
}
////////////////////////////////////////////////////////////////////////////////
//  Check the joystick position - ADC values for chipKIT on 3.3V!
//  btw, assuming the shield gets it's A3 reference voltage as the TFT runs on +5
//  feeding through level shifter. ( Arduino "Down" A3 joystick is 650 )
//  These numbers tested & consistent with uC32 powered by: USB, +12V, +9V, & +5V
byte checkJoystick() {
	int joystickState = analogRead(ADA_JOYSTICK);
	if (joystickState < 50) return  Right;	// for rotation(3) Left;	//	right, reads 20
	if (joystickState < 200) return Up;		// for rotation(3) Down;	//	up, reads 183
	if (joystickState < 350) return Press;  // always in the middle ;)	//  push, reads 327
	if (joystickState < 550) return Left;	// for rotation(3) Right;	//  left, reads 511
	if (joystickState < 1000) return Down;	// for rotation(3) Up;		//  down, reads 931
	return Neutral;
}
