#ifndef _RAWPAR_H
#define _RAWPAR_H

#include <TFTCommunicator.h>

class RawPar : public TFTCommunicator 
{
    public:
        RawPar(uint8_t d0, uint8_t d1 = 255, uint8_t d2 = 255, uint8_t d3 = 255, uint8_t d4 = 255, uint8_t d5 = 255, uint8_t d6 = 255, uint8_t d7 = 255,
               uint8_t d8 = 255, uint8_t d9 = 255, uint8_t d10 = 255, uint8_t d11 = 255, uint8_t d12 = 255, uint8_t d13 = 255, uint8_t d14 = 255, uint8_t d15 = 255,
               uint8_t d16 = 255, uint8_t d17 = 255, uint8_t d18 = 255, uint8_t d19 = 255, uint8_t d20 = 255, uint8_t d21 = 255, uint8_t d22 = 255, uint8_t d23 = 255,
               uint8_t d24 = 255, uint8_t d25 = 255, uint8_t d26 = 255, uint8_t d27 = 255, uint8_t d28 = 255, uint8_t d29 = 255, uint8_t d30 = 255, uint8_t d31 = 255);

        void writeCommand8(uint8_t command);
        void writeCommand16(uint16_t command);
        void writeCommand32(uint32_t command);
        void writeData8(uint8_t data);
        void writeData16(uint16_t data);
        void writeData32(uint32_t data);
        void streamStart();
        void streamEnd();
        void streamCommand8(uint8_t);
        void streamCommand16(uint16_t);
        void streamCommand32(uint32_t);
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);
        void setBus(uint32_t);

        uint8_t nativeWidth();

    private:
        uint8_t _d[32];
        uint8_t _width;
};

#endif

