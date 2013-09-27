#ifndef _XPT2046_H
#define _XPT2046_H

#include <TFT.h>

struct coord {
    uint16_t x;
    uint16_t y;
};

class XPT2046 : public Touch {
    public: 
        XPT2046(TFTCommunicator *comm) : Touch(comm) {}

        void sample();
        uint16_t x();
        uint16_t y();
        boolean isPressed();

        void initializeDevice();

    private:
        struct coord pos;
        boolean pressed;
};

#endif

