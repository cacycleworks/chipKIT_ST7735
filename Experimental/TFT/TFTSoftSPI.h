#ifndef _TFTSOFTSPI_H
#define _TFTSOFTSPI_H

#include <TFTCommunicator.h>

class TFTSoftSPI : public TFTCommunicator 
{
    public:
        TFTSoftSPI(uint8_t sdo, uint8_t sck, uint8_t cs, uint8_t dc);
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

        uint8_t nativeWidth() { return 8; };

    private:
        uint8_t _sdo;
        uint8_t _sck;
        uint8_t _cs;
        uint8_t _dc;
};

#endif

