#ifndef _TFTPMP_H
#define _TFTPMP_H

#include <TFT.h>

class TFTPMP : public TFTCommunicator 
{
    public:
        TFTPMP();
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
        uint8_t streamCommand8();
        uint16_t  streamCommand16();
        uint32_t streamCommand32();
        uint8_t streamData8();
        uint16_t streamData16();
        uint32_t streamData32();
        void streamCommand8(uint8_t);
        void streamCommand16(uint16_t);
        void streamCommand32(uint32_t);
        void streamData8(uint8_t);
        void streamData16(uint16_t);
        void streamData32(uint32_t);
        void blockData(uint8_t *, uint32_t);
        void blockData(uint16_t *, uint32_t);
        void blockData(uint32_t *, uint32_t);

        uint8_t nativeWidth() { return 16; };
        void initializeDevice();
};

#endif

