#ifndef _TFTPAR4_H
#define _TFTPAR4_H

#include <TFTCommunicator.h>

class TFTPar4 : public TFTCommunicator 
{
    public:
        TFTPar4(uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
        TFTPar4(uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
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

        uint8_t nativeWidth() { return 4; };

    private:
        uint8_t _cs;
        uint8_t _dc;
        uint8_t _clk;
        uint8_t _d0;
        uint8_t _d1;
        uint8_t _d2;
        uint8_t _d3;

        void clock();
        void setBus(uint8_t);
};

#endif

