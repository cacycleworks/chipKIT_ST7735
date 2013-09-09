/*
 * Sprite demonstration
 * 
 * Shows the capabilities of the sprite drawing facilities of the
 * Framebuffer virtual display device.
 */

#include <DSPI.h>
#include <TFT.h>

// These are sprites:

const uint8_t alien1[] = 
	"..o.....o.."
	"...o...o..."
	"..ooooooo.."
	".oo.ooo.oo."
	"ooooooooooo"
	"o.ooooooo.o"
	"o.o.....o.o"
	"...oo.oo..."

	"..o.....o.."
	"o..o...o..o"
	"o.ooooooo.o"
	"ooo.ooo.ooo"
	"ooooooooooo"
	".ooooooooo."
	"..o.....o.."
	".o.......o."
;

const uint8_t alien2[] = 
	"....eeee...."
	".eeeeeeeeee."
	"eeeeeeeeeeee"
	"eee..ee..eee"
	"eeeeeeeeeeee"
	"...ee..ee..."
	"..ee.ee.ee.."
	"ee........ee"

	"....eeee...."
	".eeeeeeeeee."
	"eeeeeeeeeeee"
	"eee..ee..eee"
	"eeeeeeeeeeee"
	"..eee..eee.."
	".ee..ee..ee."
	"..ee....ee.."
;

const uint8_t alien3[] =
	"...ww..."
	"..wwww.."
	".wwwwww."
	"ww.ww.ww"
	"wwwwwwww"
	".w.ww.w."
	"w......w"
	".w....w."

	"...ww..."
	"..wwww.."
	".wwwwww."
	"ww.ww.ww"
	"wwwwwwww"
	"..w..w.."
	".w.ww.w."
	"w.w..w.w"
;

const uint8_t target[] = 
	".**************."
	"**%%%%%%%%%%%%**"
	"*%%##########%%*"
	"*%##$$$$$$$$##%*"
	"*%#$$......$$#%*"
	"*%#$........$#%*"
	"*%#$........$#%*"
	"*%#$........$#%*"
	"*%#$........$#%*"
	"*%#$........$#%*"
	"*%#$........$#%*"
	"*%#$$......$$#%*"
	"*%##$$$$$$$$##%*"
	"*%%##########%%*"
	"**%%%%%%%%%%%%**"
	".**************."

	"................"
	"..************.."
	".**%%%%%%%%%%**."
	".*%%########%%*."
	".*%##$$$$$$##%*."
	".*%#$$....$$#%*."
	".*%#$......$#%*."
	".*%#$......$#%*."
	".*%#$......$#%*."
	".*%#$......$#%*."
	".*%##$....$$#%*."
	".*%#$$$$$$$##%*."
	".*%%########%%*."
	".**%%%%%%%%%%**."
	"..************.."
	"................"

	"................"
	"................"
	"...**********..."
	"..**%%%%%%%%**.."
	"..*%%######%%*.."
	"..*%##$$$$##%*.."
	"..*%#$$..$$#%*.."
	"..*%#$....$#%*.."
	"..*%#$....$#%*.."
	"..*%#$$..$$#%*.."
	"..*%##$$$$##%*.."
	"..*%%######%%*.."
	"..**%%%%%%%%**.."
	"...**********..."
	"................"
	"................"

	"................"
	"................"
	"................"
	"....********...."
	"...*%%%%%%%%*..."
	"...*%######%*..."
	"...*%#$$$$#%*..."
	"...*%#$..$#%*..."
	"...*%#$..$#%*..."
	"...*%#$$$$#%*..."
	"...*%######%*..."
	"...*%%%%%%%%*..."
	"....********...."
	"................"
	"................"
	"................"

	"................"
	"................"
	"................"
	"................"
	".....******....."
	"....*%%%%%%*...."
	"....*%####%*...."
	"....*%#$$#%*...."
	"....*%#$$#%*...."
	"....*%####%*...."
	"....*%%%%%%*...."
	".....******....."
	"................"
	"................"
	"................"
	"................";


#define ADA_SCLK 	13
#define ADA_MOSI 	11
#define ADA_CS  	10
#define ADA_DC 		8
#define ADA_JS		A3

// Configure the display
DSPI0 spi;
TFTDSPI mySpi(&spi, ADA_CS, ADA_DC);
ST7735 tft(&mySpi, ST7735::BlackTab);

// Create a framebuffer for us to do all our work in
uint8_t buffer[ST7735::Height * ST7735::Width];
Framebuffer fb(ST7735::Height, ST7735::Width, buffer);

// This is the hunter sprite/
struct sprite *mySprite1;

// Add a random alien to the sprite list at a random position
// travelling in a random direction at a random speed.
void addAlien() {
	struct sprite *temp;
	uint8_t anum = rand() % 3;

	switch (anum) {
		case 0:
			temp = fb.addSprite(alien1, 11, 8, '.', 2);
			break;
		case 1:
			temp = fb.addSprite(alien2, 12, 8, '.', 2);
			break;
		case 2:
			temp = fb.addSprite(alien3, 8, 8, '.', 2);
			break;
	}
	if (!temp) { // Failed to add a sprite - memory allocation error?
		return;
	}

	fb.moveTo(temp, rand() % (160 - 11), rand() % (128 - 8));
	fb.setSprite(temp, 0, rand() % 7 - 3);
	fb.setSprite(temp, 1, rand() % 7 - 3);		
}

void setup() {
	// Set up the colours we want to use in our framebuffer
	fb.setColor(0, 0, 0, 0);
	fb.setColor(1, 0, 255, 255);
	fb.setColor('*', 255, 255, 255);
	fb.setColor('%', 255, 128, 128);
	fb.setColor('#', 255, 0, 0);
	fb.setColor('$', 128, 0, 0);
	fb.setColor('o', 0, 255, 128);
	fb.setColor('e', 0, 128, 255);
	fb.setColor('w', 255, 0, 128);

	// Turn on the display etc
	tft.initializeDevice();
	tft.setRotation(1);

	// Start with an empty screen and the Sinclair font
	fb.fillScreen(0);
	fb.setCursor(0, 0);
	fb.setFont(Fonts::Sinclair);
	tft.update(fb);

	// Add the hunter sprite to the sprite list
	mySprite1 = fb.addSprite(target, 16, 16, '.', 5);

	mySprite1->xpos = 40;
	mySprite1->ypos = 40;

	// Add a few initial aliens to go hunting
	for (int i = 0; i < 5; i++) {
		addAlien();
	}
}

void loop() {
	static uint32_t blip = millis();  // This is our animation timing counter
	static uint32_t score = 0;	// The player's score

	// Handle the joystick input to move the hunter or add more aliens to the
	// screen.
	switch(js()) {
		case 1: 
			mySprite1->xpos++;
			break;
		case 2: 
			mySprite1->ypos--;
			break;
		case 3:
			addAlien();
			break;
		case 4: 
			mySprite1->xpos--;
			break;
		case 5: 
			mySprite1->ypos++;
			break;
	}

	// Animate the hunter sprite
	fb.animatePingPong(mySprite1);

	// If the animation timer has passed then animate all the aliens
	if (millis() - blip >= 500) {
		blip = millis();
		for (struct sprite *spr = fb.firstSprite(); spr; spr = fb.nextSprite()) {
			if (spr != mySprite1) {
				fb.animate(spr);
			}
		}
	}

	// Move the aliens around the screen
	for (struct sprite *spr = fb.firstSprite(); spr; spr = fb.nextSprite()) {
		if (spr != mySprite1) {
			fb.moveBy(spr, fb.getSprite(spr, 0), fb.getSprite(spr, 1));
			if (spr->xpos < 0) {
				spr->xpos = 0;
				fb.setSprite(spr, 0, 0 - fb.getSprite(spr, 0)); 
			}
			if (spr->xpos > 159 - spr->width) {
				spr->xpos = 159 - spr->width;
				fb.setSprite(spr, 0, 0 - fb.getSprite(spr, 0)); 
			}
			if (spr->ypos < 0) {
				spr->ypos = 0;
				fb.setSprite(spr, 1, 0 - fb.getSprite(spr, 1)); 
			}
			if (spr->ypos > 127 - 8) {
				spr->ypos = 127 - 8;
				fb.setSprite(spr, 1, 0 - fb.getSprite(spr, 1)); 
			}
		}
	}

	// Check to see if we have collided with an alien
	struct sprite *col;
	while ((col = fb.collidesWith(mySprite1)) != NULL) {
		// Yes, so remove it and increase our score.
		fb.removeSprite(col);
		score++;
	}

	// Display our current score
	fb.setCursor(0, 115);
	fb.setTextColor(1);
	fb.print("Score: ");
	fb.print(score);

	// And push the frame to the screen
	tft.update(fb);
}

uint8_t js() {
	uint16_t jv = analogRead(ADA_JS);

	if (jv > 15 && jv < 25) {
		return 1;
	}
	if (jv > 175 && jv < 195) {
		return 2;
	}
	if (jv > 320 && jv < 345) {
		return 3;
	}
	if (jv > 505 && jv < 530) {
		return 4;
	}
	if (jv > 920 && jv < 960) {
		return 5;
	}
	return 0;
}
