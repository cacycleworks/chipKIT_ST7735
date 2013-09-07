//	ST7735 code to get Adafruit 1.8" TFT shield working with chipKIT uC32
//	Note was not able to make it work on my Uno32 with SPI, DSPI with or without delays in ST7735.cpp//  This port to chipKIT written by Chris Kelley of ca-cycleworks.com  (c) ? Sure, ok same MIT thing, whatever
//	This code derived from Adafruit_ST7735 library. See bottom of .h file for their full MIT license stuff.
////////////////////////////////////////////////////////////////////////////////
//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
static char version[]={"tft.ino v1.05 2013-SEP-06"};
char text[28];
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
#include <GFX.h>
#include <ST7735.h>

//  UNO hardware SPI pins
#define ADA_SCLK 13
#define ADA_MOSI 11
#define ADA_CS  10
#define ADA_DC 	8
// analog pin 3 for button input
#define ADA_JOYSTICK 3
//	SD card chip select digital pin 4 : No work yet for SD Card
//	#define SD_CS 4

////////////////////////////////////////////////////////////////////////////////
// Three versions of the constructor.  Select the one that best suits your needs:
// 1. The default.  Hardware SPI on DSPI0:
ST7735 tft = ST7735( ADA_CS, ADA_DC );

// 2. Hardware SPI where you specify the DSPI channel:
// DSPI0 spi;
// ST7735 tft = ST7735( ADA_CS, ADA_DC, &spi );

// 3. Software SPI.  Specify the data and clock lines to use
// ST7735 tft = ST7735( ADA_CS, ADA_DC, ADA_MOSI, ADA_SCLK );


//  Other definitions for the Ada shield and playing with it...
//  Joystick directions - Works with our screen rotation (1), yaay
enum { Neutral, Press, Up, Down, Right, Left };
const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };

enum COLORS { 	BLACK = 0x0000, BLUE = 0x001F, RED = 0xF800, ORANGE = 0xFA60, GREEN = 0x07E0,
				CYAN = 0x07FF, MAGENTA = 0xF81F, YELLOW = 0xFFE0, GRAY = 0xCCCC, WHITE = 0xFFFF
			};

//	char() values for some special characters defined in GFX.h static font[]
//  not sure what to call solid triangle arrow things, so "pyramids" = pyr  ??
enum arrows { uarr = 0x18, darr = 0x19, larr = 0x1b, rarr = 0x1a, upyr = 0x1e, dpyr = 0x1f, lpyr = 0x11, rpyr = 0x10 };

////////////////////////////////////////////////////////////////////////////////
void setup(){
	//  Setup the Adafruit 1.8" TFT
	tft.initR( INITR_BLACKTAB );    //  "tab color" from screen protector; there's RED and GREEN, too.
	tft.setRotation(1);
	tft.setTextColor(RED);
	//  size 2 template:	1234567890123 <-- if last char is ON 13, \n not req'd; driver inserts it (enabled via wrap member)
	//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
	tft.setTextSize(1); //  1 = 5x8, 2 = 10x16; chars leave blank pixel on bottom
	cls();
	tft.setCursor(0, 20);
	sprintf(text,"Play with joystick --%c", rarr);
	tft.print(text);
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
//	then Up, Down, Left, Right, Press in simple if-else-if
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
//  feeding through level shifter. ( Arduino "Down" A3 joystick is 650 )
//  These numbers tested & consistent with uC32 powered by: USB, +12V, +9V, & +5V
byte checkJoystick() {
	int joystickState = analogRead(ADA_JOYSTICK);
	if (joystickState < 50) return  Right;	// for rotation(3) Left;	//	right, reads 20
	if (joystickState < 200) return Up;		// for rotation(3) Down;	//	up, reads 183
	if (joystickState < 350) return Press;  // always in the middle ;)	//  push, reads 327
	if (joystickState < 550) return Left;	// for rotation(3) Right;	//  left, reads 511
	if (joystickState < 950) return Down;	// for rotation(3) Up;		//  down, reads 931
	return Neutral;
}
