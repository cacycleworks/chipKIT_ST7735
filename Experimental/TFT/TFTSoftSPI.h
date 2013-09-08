#ifndef _TFTSOFTSPI_H
#define _TFTSOFTSPI_H

#include <TFTCommunicator.h>

class TFTSoftSPI : public TFTCommunicator 
{
    public:
        TFTSoftSPI(uint8_t sdo, uint8_t sck, uint8_t cs, uint8_t dc);
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

    private:
        uint8_t _sdo;
        uint8_t _sck;
        uint8_t _cs;
        uint8_t _dc;
};

#endif

