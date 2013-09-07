//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
static char version[]={"tft.ino v1.04 2013-SEP-05"};
char text[28];
//  Version 1.03 : 2013-SEP-04 : majenko updated GFX and ST7735 to work with DSPI! :-)
//  Version 1.04 : 2013-SEP-05 : tweaks to GFX to remove swap() macro and instead
//					use STL's std::swap() <-- needed for ANY STL libraries to compile.
////////////////////////////////////////////////////////////////////////////////
// Adafruit 1.8TFT w/joystick 160x128 in landscape (128x160)
//  Adafruit pins on the shield and why. "SPI:" below means part of hardware SPI
//  13 - SPI:SCLK, serial data clock shared between TFT and SD Card
//  12 - SPI:MISO, data sent from shield to controller (SD Card)
//  11 - SPI:MOSI, data sent to shield from controller, both TFT and SD Card
//  10 - SPI:SS, TFT slave select aka chip select
//   8 - DC or RS for TFT, "data channel" or "register select", a low on this pin tells the TFT it is about to receive a command, while high means data is incoming
//   4 - SPI SS for SD Card
//  A3 - Analog input for the joystick; each of 5 inputs are in a resistor network
#include <DSPI.h>
#include "GFX.h"
#include "ST7735.h"
//  UNO hardware SPI pins
#define ADA_SCLK 13
#define ADA_MOSI 11
#define ADA_CS  10
//	Pinout for Mega: http://forums.adafruit.com/viewtopic.php?uid=115205&f=31&t=36738&start=0
//	#define ADA_SCLK	52	//#define ADA_MOSI	51	//#define ADA_CS		53
#define ADA_DC 		8
// analog pin 3 for button input
#define ADA_JOYSTICK 3
//  Other definitions for the Ada shield and playing with it...
//  Joystick directions - Works with our screen rotation (1), yaay
#define Neutral 0
#define Press 1
#define Up 2
#define Down 3
#define Right 4
#define Left 5
const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };
//	SD card chip select digital pin 4 : Note, I've done zilch for SD Card.
//  who needs SD Card when you've got more than 8K of SRAM?? :P
//	#define SD_CS 4

//  ST7735 class ASSUMES hardware SPI. Software SPI is probably easy enough to
//  implement if you get their source and look for the variable. They use two different
//  constructors. *I* won't ever wire this up needing software SPI...
ST7735 tft = ST7735( ADA_CS, ADA_DC );

// TFT Color definitions, probably belong in ST7735.h ?
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

////////////////////////////////////////////////////////////////////////////////
void setup(){
	//  Setup the Adafruit 1.8" TFT
	tft.initR( INITR_BLACKTAB );    //  tab color very important, there's RED and GREEN, too.
	tft.setRotation(1);
	tft.setTextColor(RED);
	//  size 2 template:	1234567890123 <-- if last char is ON 13, \n not req'd; driver inserts it
	//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
	tft.setTextSize(1); //  1 = 5x8, 2 = 10x16; chars leave blank pixel on bottom
	cls();
	tft.setCursor(0, 20);
	tft.print("Play with joystick -->");
	//  Is this required by law? Who needs Serial when you've got a TFT
	Serial.begin(9600);
}
////////////////////////////////////////////////////////////////////////////////
//  clearscreen helper for tft
void cls() {
	tft.fillScreen(BLACK);
	tft.setCursor(0, 2);
}
////////////////////////////////////////////////////////////////////////////////
void loop() {
	if( doMenu() ){
		//  something happened with joystick, do we care?
	} else {
	}
		//	footer for the screen
		//	normally lives in the else{} above but then you don't see A3 change & that's no fun
		tft.setTextColor(GREEN);
		tft.setCursor(0,105);
		tft.print(  "A0   A1   A2   A3\n");
		sprintf(text,"%-4d %-4d %-4d %-4d\n"
			,analogRead(A0)
			,analogRead(A1)
			,analogRead(A2)
			,analogRead(A3)
		);
		tft.print(text);

		tft.setTextColor(GRAY);
		sprintf(text,"%s\n", version);
		tft.print(text);

		tft.setTextColor(RED);
}
////////////////////////////////////////////////////////////////////////////////
//  note: button is handled in order of Neutral( or none ),
//	then Up, Down, Left, Right, Press in a big ass if-else-if, eff you SO.SE!
bool doMenu( void ){
	uint8_t b = checkJoystick();
	if( b == Neutral ){
		return false;   //  user input didn't happen
	}
	tft.setCursor(0,10);
	//  const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };
	if( b == Up ) {
		tft.setTextColor(RED);
		sprintf(text,"%s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Down ) {
		tft.setTextColor(GREEN);
		sprintf(text,"%s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Left ) {
		tft.setTextColor(YELLOW);
		sprintf(text,"%s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Right ) {
		tft.setTextColor(MAGENTA);
		sprintf(text,"%s\n", Buttons[b]);
		tft.print(text);
	} else if( b == Press ) {
		tft.setTextColor(ORANGE);
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
//  feeding through level shifter. Also, Arduino "Down" A3 joystick is 650.
byte checkJoystick() {
	int joystickState = analogRead(ADA_JOYSTICK);
	if (joystickState < 50) return  Right;	// for rotation(3) Left;	//	right, reads 20
	if (joystickState < 200) return Up;		// for rotation(3) Down;	//	up, reads 183
	if (joystickState < 350) return Press;  // always in the middle ;)	//  push, reads 327
	if (joystickState < 550) return Left;	// for rotation(3) Right;	//  left, reads 511
	if (joystickState < 950) return Down;	// for rotation(3) Up;		//  down, reads 931
	return Neutral;
}
