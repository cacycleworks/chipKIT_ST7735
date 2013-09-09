#ifndef _AGGREGATOR_H_
#define _AGGREGATOR_H_

#include <TFT.h>

struct AggregatorList {
    TFT *display;
    int16_t x;
    int16_t y;
    struct AggregatorList *next;
};

class Aggregator : public TFT {
	public:
		Aggregator() : TFT(NULL) {};

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i);
        void displayOn() {}; // Not implemented
        void displayOff() {}; // Not implemented

        void initializeDevice();

        void addDisplay(TFT *d, int16_t x, int16_t y);

	protected:
        struct AggregatorList *displays;
};

#endif
