#include <DSPI.h>
#include <GFX.h>
#include <ST7735.h>
#include <ST7735B.h>

#define ADA_SCLK 	13
#define ADA_MOSI 	11
#define ADA_CS  	10
#define ADA_DC 		8
#define ADA_JS		A3
DSPI0 spi;

ST7735B tft = ST7735B(ADA_CS, ADA_DC, &spi);

const uint8_t spr[] = 
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

uint8_t alien[] = 
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

struct sprite *mySprite1;

#define NALIEN 10
struct sprite *aliens[NALIEN];
int8_t adx[NALIEN];
int8_t ady[NALIEN];

void setup() {


	tft.sprites = NULL;
	tft.setColor(0, 0, 0, 0);
	tft.setColor(1, 0, 255, 255);
	tft.setColor('*', 255, 255, 255);
	tft.setColor('%', 255, 128, 128);
	tft.setColor('#', 255, 0, 0);
	tft.setColor('$', 128, 0, 0);
	tft.setColor('o', 0, 255, 128);
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.setTextSize(1);
	tft.fillScreen(0);
	tft.setCursor(0, 0);
	tft.update();
	mySprite1 = tft.addSprite(spr, 16, 16, '.', 5);

	mySprite1->xpos = 40;
	mySprite1->ypos = 40;

	for (int i = 0; i < NALIEN; i++) {
		aliens[i] = tft.addSprite(alien, 11, 8, '.', 2);
		aliens[i]->xpos = rand() % (160 - 11);
		aliens[i]->ypos = rand() % (128 - 8);
		adx[i] = 0;
		while (adx[i] == 0) {
			adx[i] = rand() % 5 - 2;
		}
		ady[i] = 0;
		while (ady[i] == 0) {
			ady[i] = rand() % 5 - 2;
		}
	}

}

void loop() {
	static uint32_t blip = millis();
	static uint32_t score = 0;
	
	switch(js()) {
		case 1: 
			mySprite1->xpos++;
			break;
		case 2: 
			mySprite1->ypos--;
			break;
		case 4: 
			mySprite1->xpos--;
			break;
		case 5: 
			mySprite1->ypos++;
			break;
	}

	tft.animatePingPong(mySprite1);
	if (millis() - blip >= 500) {
		blip = millis();
		for (int i = 0; i < NALIEN; i++) {
			tft.animate(aliens[i]);
		}
	}

	for (int i = 0; i < NALIEN; i++) {
		aliens[i]->xpos += adx[i];
		aliens[i]->ypos += ady[i];

		if (aliens[i]->xpos >= (159 - 11)) {
			adx[i] = -adx[i];
		}

		if (aliens[i]->xpos <= 0) {
			adx[i] = -adx[i];
		}
	
		if (aliens[i]->ypos >= (127 -8)) {
			ady[i] = -ady[i];
		}
	
		if (aliens[i]->ypos <= 0) {
			ady[i] = -ady[i];
		}
	}

	struct sprite *col;
	while ((col = tft.collidesWith(mySprite1)) != NULL) {
		col->xpos = rand() % (160 - 11);
		col->ypos = rand() % (128 - 8);
		score++;
	}
	tft.setCursor(0, 115);
	tft.setTextColor(1);
	tft.print("Score: ");
	tft.print(score);

	tft.update();
}

uint8_t js() {
	uint16_t jv = analogRead(IO9);

	if (jv > 15 && jv < 25) {
		return 1;
	}
	if (jv > 175 && jv < 195) {
		return 2;
	}
	if (jv > 320 && jv < 345) {
		return 3;
	}
	if (jv > 510 && jv < 530) {
		return 4;
	}
	if (jv > 940 && jv < 960) {
		return 5;
	}
	return 0;
}
