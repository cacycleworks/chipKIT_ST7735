#ifndef _TFTDSPI_H
#define _TFTDSPI_H

#include <TFTCommunicator.h>
#include <DSPI.h>

class TFTDSPI : public TFTCommunicator 
{
    public:
        TFTDSPI(DSPI *spi, uint8_t cs, uint8_t dc = 255);
        uint8_t readCommand8();
        uint16_t readCommand16();
        uint32_t readCommand32();
        uint8_t readData8();
        uint16_t readData16();
        uint32_t readData32();
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
        uint8_t streamCommand8();
        uint16_t streamCommand16();
        uint32_t streamCommand32();
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);
        uint8_t streamData8();
        uint16_t streamData16();
        uint32_t streamData32();
        uint8_t nativeWidth() { return 32; };
        void blockData(uint32_t *data, uint32_t len);

    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
};

#endif

