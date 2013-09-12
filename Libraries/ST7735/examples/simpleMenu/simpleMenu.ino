//	Demonstration code for Adafruit 1.8" TFT shield and ST7735 class
////////////////////////////////////////////////////////////////////////////////
// Adafruit 1.8TFT w/joystick 160x128 in landscape (128x160, portrait)
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
//  size 1 template:	12345678901234567890123456 <-- if last char is ON 26, \n not req'd; driver inserts it
static char version[]={"simpleMenu.ino 2013SEP11"};
char text[64];  // Made buffer big enough to hold two lines of text

////////////////////////////////////////////////////////////////////////////////
//  Static menu manager
#define MAX_SELECTIONS 4
#define MAX_PROMPT_LEN 20
typedef struct _selection {
	char label[MAX_PROMPT_LEN];
	void(*function) ( int );
	int fn_arg;
} SELECTION ;

typedef struct _menu {
	int id;
	char label[MAX_PROMPT_LEN];
	int num_selections;
	SELECTION selection[MAX_SELECTIONS];
} MENU;
//  enumerated menu ids must be in order of static MENU menu[], as they are same as array's index
enum _menus { MAIN_MENU, DEPOSIT_MENU, WITHDRAWL_MENU, BALANCE_MENU };
enum _menu_keys { DEPOSIT, WITHDRAWL, BALANCE, CHECKING, SAVINGS };
//  MENU menu[] is simple static list of menus; the only "nesting" is that the [0] entry
//	must be the top of the menus, a la MAIN_MENU otherwise, nesting is defined by the selections array
static MENU menu[] = {
	{ MAIN_MENU, "Main Menu", 4, {
		{"Perform A Deposit", goto_menu, DEPOSIT_MENU},
		{"Perform a Withdrawl", goto_menu, WITHDRAWL_MENU },
		{"Get Balance", goto_menu, BALANCE_MENU },
		{"Hide Menu", menu_hide, 0} }
	},
	{ DEPOSIT_MENU, "Deposit Menu", 3, {
		{"Deposit to Checking", do_deposit, CHECKING},
		{"Deposit to Savings", do_deposit, SAVINGS},
		{"Go Back", goto_menu, MAIN_MENU} }
	},
	{ WITHDRAWL_MENU, "Withdrawl Menu", 3, {
		{"Withdrawl: Checking", do_withdrawl, CHECKING},
		{"Withdrawl: Savings", do_withdrawl, SAVINGS},
		{"Go Back", goto_menu, MAIN_MENU} }
	},
	{ BALANCE_MENU, "Acct Balance Menu", 3, {
		{"Checking Balance", show_balance, CHECKING},
		{"Savings Balance", show_balance, SAVINGS},
		{"Go Back", goto_menu, MAIN_MENU} }
	}
};
MENU * curr_menu = menu;
int menu_enable = 0;
//  curr_selection is the SELECTION array index of the curr_menu
int curr_selection = 0;
static uint16_t menu_color = WHITE;
////////////////////////////////////////////////////////////////////////////////
// Set & display active menu
void goto_menu ( ) {
	//  a_menu is working copy of curr_menu, which will get reset to our parent
	static MENU *a_menu = curr_menu;
	//	Create a selection pointer for convenience
	//  the LAST selection in a menu must be to "go up" a menu
	static SELECTION *selptr = &a_menu->selection[ curr_selection ];
	curr_menu = &menu[selptr->fn_arg ];
	curr_selection=0;
	cls();
	draw_menu();
	return;
}
void goto_menu ( int newmenu ) {
	curr_menu = &menu[newmenu];
	curr_selection=0;
	cls();
	draw_menu();
	return;
}
////////////////////////////////////////////////////////////////////////////////
void menu_hide( int ){ menu_enable = 0; cls; draw_menu(); }
void do_deposit( int key ){
	tft.setCursor(0,60);
	sprintf( text, "%s %d", __FUNCTION__, key );
	tft.print( text );
}
void do_withdrawl( int key ){
	tft.setCursor(0,60);
	sprintf( text, "%s %d", __FUNCTION__, key );
	tft.print( text );
}
void show_balance( int key ){
	tft.setCursor(0,60);
	sprintf( text, "%s %d", __FUNCTION__, key );
	tft.print( text );
}
////////////////////////////////////////////////////////////////////////////////
bool doMenu( void ){
	uint8_t b = checkJoystick();
	if( b == Neutral ){
		return false;   //  user input didn't happen
	}
	//  enable menu if up, else ignore input & return
	if( ! menu_enable ) {
		if( b == Up ) {
			menu_enable = 1;
			curr_selection = 0;   //  start with top item as selected
			cls();
			draw_menu();
		}
		return 0;
	}
	SELECTION *selptr = &curr_menu->selection[ curr_selection ];
	tft.setCursor(0,10);
	//  const char* Buttons[]={"Neutral", "Press", "Up", "Down", "Right", "Left" };
	if( b == Up ) {
		if(curr_selection > 0)
			curr_selection--;
		else    //  wrap around
		    curr_selection = curr_menu->num_selections-1;
	} else if( b == Down ) {
		if(curr_selection < curr_menu->num_selections-1 )
			curr_selection++;
		else
		    curr_selection=0;
	} else if( b == Left ) {    //  back out to higher menu
		menu_parent();
	} else if( b == Right || b == Press ) {
		// curr_menu->selection[curr_selection].function();
		selptr->function( selptr->fn_arg );
	}
	if( b == Up || b == Down )
	    draw_menu( );
	return true;    //  user input happened
}
////////////////////////////////////////////////////////////////////////////////
//  Finds parent of current menu and resets curr_menu to it and draws menu
void menu_parent( ){
    curr_selection=0;
	//  already at top of menu, so hide it. &menu[0] used as is more obvious than just 'menu'
	if( curr_menu == &menu[0] && menu_enable ) {
	    menu_enable = false;
	} else {
		//  a_menu is working copy of curr_menu, which will get reset to our parent
		MENU *a_menu = curr_menu;
		//	Create a selection pointer for convenience
		//  the LAST selection in a menu must be to "go up" a menu
		static int num_menus=sizeof(_menus);
		SELECTION *selptr = &a_menu->selection[ a_menu->num_selections - 1 ];
		for( int menuidx = 0; menuidx < num_menus ; menuidx++ ) {
		    if( selptr->fn_arg == menu[menuidx].id ) {
		        curr_menu=&menu[menuidx];
		        curr_selection=0;
		        break;
	        }
	    }
	}
	cls();
	draw_menu();
}
////////////////////////////////////////////////////////////////////////////////
//  displays the currently selected menu (or uarr for menu if not enabled)
void draw_menu( ){
	if( ! menu_enable ) {
		cls();
		sprintf( text, "%c for menu", uarr );
		tft.print( text );
		guiFooter();
		return;
	}
	uint16_t colorsave = tft.getTextColor();
	tft.setTextColor( menu_color );
	tft.setCursor(0, 2);
	//  magic number alert! set %-20.20s to same value as MAX_PROMPT_LEN
	sprintf( text, "%-20.20s\n", curr_menu->label );
	tft.print(text);
	int selection_num = 0;
	// Loop through the actual number of selections in THIS menu
	for(selection_num=0; selection_num < curr_menu->num_selections; selection_num++)
	{
		// Create a pointer for convenience
		SELECTION *selptr = &curr_menu->selection[selection_num];
		//	If this is the "active" menu selection (determine by referencing the global
		//	variable 'curr_selection' then draw it in inverse text.
		if (selection_num == curr_selection)
		    tft.invertTextColor();
		// Print the prompt string
		//	setcur(selection_num + MENU_INDENT_Y, MENU_INDENT_X);
		sprintf( text, "  %-20.20s\n", selptr->label );
		tft.print(text);
		// Turn inverse back off if need be
		if (selection_num == curr_selection)
		    tft.invertTextColor();
	}

	tft.setTextColor( colorsave );

}
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

	draw_menu();
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
		//  something happened with joystick, an update() action could be called here
	} 
	//	footer for the screen; could live in else{} but then you won't see A3 change while pushing button
	guiFooter();
}


void guiFooter(){
	//	footer for the screen
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

