/*
 * Generic touch screen interface for TFT devices
 */


#ifndef _TOUCH_H
#define _TOUCH_H

#include <TFT.h>

class Touch {
    public:
        Touch(TFTCommunicator *comm, uint16_t w, uint16_t h) : _comm(comm), _width(w), _height(h) {}
        virtual void initializeDevice() = 0;
        virtual uint16_t x() = 0;
        virtual uint16_t y() = 0;
        virtual boolean isPressed() = 0;

    protected:
        TFTCommunicator *_comm;
        uint16_t _width;
        uint16_t _height;
};

#endif
