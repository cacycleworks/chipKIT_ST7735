#include <TFT.h>

#define TOUCH_CMD_X        0xD0
#define TOUCH_CMD_Y        0x90

#define XPT2046_SMPSIZE 20

void XPT2046::initializeDevice() {
    pressed = false;
    pos.x = 0;
    pos.y = 0;
}

uint16_t XPT2046::x() {
    return pos.x;
}

uint16_t XPT2046::y() {
    return pos.y;
}

boolean XPT2046::isPressed() {
    return pressed;
}

void XPT2046::sample() {

    uint32_t temp;

    struct coord tpos;
    temp = 0;
    for (uint8_t i = 0; i < XPT2046_SMPSIZE; i++) {
        _comm->streamStart();
        _comm->streamCommand8(TOUCH_CMD_X);
        temp += _comm->streamCommand16() >> 3;
        _comm->streamEnd();
    }
    pos.x = temp / XPT2046_SMPSIZE;
    temp = 0;
    for (uint8_t i = 0; i < XPT2046_SMPSIZE; i++) {
        _comm->streamStart();
        _comm->streamCommand8(TOUCH_CMD_Y);
        temp += _comm->streamCommand16() >> 3;
        _comm->streamEnd();
    }
    pos.y = temp / XPT2046_SMPSIZE;

    if ((pos.x > 0xFFF) || (pos.y > 0xFFF)) {
        pressed = 0;
        return;
    }
    
    pressed = 1;
}

