#ifndef _TFTPAR8_H
#define _TFTPAR8_H

#include <TFTCommunicator.h>

class TFTPar8 : public TFTCommunicator 
{
    public:
        TFTPar8(uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
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
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _clk;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;
        uint8_t _d4;
        uint8_t _d5;
        uint8_t _d6;
        uint8_t _d7;

        void clock();
        void setBus(uint8_t);
};

#endif

