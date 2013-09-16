#ifndef _TFTDSPI_H
#define _TFTDSPI_H

#include <TFTCommunicator.h>
#include <DSPI.h>

class TFTDSPI : public TFTCommunicator 
{
    public:
        TFTDSPI(DSPI *spi, uint8_t cs, uint8_t dc);
        void writeCommand(uint8_t command);
        void writeData8(uint8_t data);
        void writeData16(uint16_t data);
        void writeData32(uint32_t data);
        void commandStreamStart();
        void commandStreamEnd();
        void commandStream(uint8_t);
        void dataStreamStart();
        void dataStreamEnd();
        void dataStream8(uint8_t);
        void dataStream16(uint16_t);
        void dataStream32(uint32_t);
        uint8_t nativeWidth() { return 32; };


    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _dc;
};

#endif

