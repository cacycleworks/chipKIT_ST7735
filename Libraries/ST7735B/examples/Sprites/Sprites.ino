#include <DSPI.h>
#include <GFX.h>
#include <ST7735.h>
#include <ST7735B.h>

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
DSPI0 spi;


ST7735B tft = ST7735B(ADA_CS, ADA_DC, &spi);

struct sprite *mySprite1;

void addAlien() {
	struct sprite *temp;
	uint8_t anum = rand() % 3;

	switch (anum) {
		case 0:
			temp = tft.addSprite(alien1, 11, 8, '.', 2);
			break;
		case 1:
			temp = tft.addSprite(alien2, 12, 8, '.', 2);
			break;
		case 2:
			temp = tft.addSprite(alien3, 8, 8, '.', 2);
			break;
	}

	tft.moveTo(temp, rand() % (160 - 11), rand() % (128 - 8));
	tft.setSprite(temp, 0, rand() % 7 - 3);
	tft.setSprite(temp, 1, rand() % 7 - 3);		
}

void setup() {
	tft.sprites = NULL;
	tft.setColor(0, 0, 0, 0);
	tft.setColor(1, 0, 255, 255);
	tft.setColor('*', 255, 255, 255);
	tft.setColor('%', 255, 128, 128);
	tft.setColor('#', 255, 0, 0);
	tft.setColor('$', 128, 0, 0);
	tft.setColor('o', 0, 255, 128);
	tft.setColor('e', 0, 128, 255);
	tft.setColor('w', 255, 0, 128);
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.setTextSize(1);
	tft.fillScreen(0);
	tft.setCursor(0, 0);
	tft.update();

	mySprite1 = tft.addSprite(target, 16, 16, '.', 5);

	mySprite1->xpos = 40;
	mySprite1->ypos = 40;

	for (int i = 0; i < 5; i++) {
		addAlien();
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

	tft.animatePingPong(mySprite1);
	if (millis() - blip >= 500) {
		blip = millis();
		for (struct sprite *spr = tft.firstSprite(); spr; spr = tft.nextSprite()) {
			if (spr != mySprite1) {
				tft.animate(spr);
			}
		}
	}

	for (struct sprite *spr = tft.firstSprite(); spr; spr = tft.nextSprite()) {
		if (spr != mySprite1) {
			tft.moveBy(spr, tft.getSprite(spr, 0), tft.getSprite(spr, 1));
			if (spr->xpos < 0) {
				spr->xpos = 0;
				tft.setSprite(spr, 0, 0 - tft.getSprite(spr, 0)); 
			}
			if (spr->xpos > 159 - spr->width) {
				spr->xpos = 159 - spr->width;
				tft.setSprite(spr, 0, 0 - tft.getSprite(spr, 0)); 
			}
			if (spr->ypos < 0) {
				spr->ypos = 0;
				tft.setSprite(spr, 1, 0 - tft.getSprite(spr, 1)); 
			}
			if (spr->ypos > 127 - 8) {
				spr->ypos = 127 - 8;
				tft.setSprite(spr, 1, 0 - tft.getSprite(spr, 1)); 
			}
		}
	}

	struct sprite *col;
	while ((col = tft.collidesWith(mySprite1)) != NULL) {
		tft.removeSprite(col);
		score++;
	}
	tft.setCursor(0, 115);
	tft.setTextColor(1);
	tft.print("Score: ");
	tft.print(score);

	tft.update();
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
	if (jv > 510 && jv < 530) {
		return 4;
	}
	if (jv > 940 && jv < 960) {
		return 5;
	}
	return 0;
}
