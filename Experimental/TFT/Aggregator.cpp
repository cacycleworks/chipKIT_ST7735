#include <TFT.h>

void Aggregator::fillScreen(uint16_t color) {
    struct AggregatorList *s;
    if (!displays) {
        return;
    }
    for (s = displays; s; s = s->next) {
        s->display->fillScreen(color);
    }
}

void Aggregator::invertDisplay(boolean i) {
    struct AggregatorList *s;
    if (!displays) {
        return;
    }
    for (s = displays; s; s = s->next) {
        s->display->invertDisplay(i);
    }
}

void Aggregator::setPixel(int16_t x, int16_t y, uint16_t color) {
    struct AggregatorList *s;
    if (!displays) {
        return;
    }
    for (s = displays; s; s = s->next) {
        s->display->setPixel(x - s->x, y - s->y, color);
    }
}

void Aggregator::initializeDevice() {
    displays = NULL;
    _width = 65535;
    _height = 65535;
}

void Aggregator::addDisplay(TFT *d, int16_t x, int16_t y) {
    struct AggregatorList *n = (struct AggregatorList *)malloc(sizeof(struct AggregatorList));
    struct AggregatorList *s;

    if (!n) {
        return;
    }

    n->display = d;
    n->x = x;
    n->y = y;
    n->next = NULL;

    if (!displays) {
        displays = n;
    } else {
        for (s = displays; s->next; s = s->next);
        s->next = n;
    }
}

