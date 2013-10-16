#ifndef _TFT_COMMUNICATOR_H
#define _TFT_COMMUNICATOR_H

class TFTCommunicator
{
    public:
        virtual uint8_t readCommand8() = 0;
        virtual uint16_t readCommand16() = 0;
        virtual uint32_t readCommand32() = 0;
        virtual uint8_t readData8() = 0;
        virtual uint16_t readData16() = 0;
        virtual uint32_t readData32() = 0;
        virtual void writeCommand8(uint8_t command) = 0;
        virtual void writeCommand16(uint16_t command) = 0;
        virtual void writeCommand32(uint32_t command) = 0;
        virtual void writeData8(uint8_t data) = 0;
        virtual void writeData16(uint16_t data) = 0;
        virtual void writeData32(uint32_t data) = 0;
        virtual void streamStart() = 0;
        virtual void streamEnd() = 0;
        virtual void streamCommand8(uint8_t data) = 0;
        virtual void streamCommand16(uint16_t data) = 0;
        virtual void streamCommand32(uint32_t data) = 0;
        virtual uint8_t streamCommand8() = 0;
        virtual uint16_t streamCommand16() = 0;
        virtual uint32_t streamCommand32() = 0;
        virtual void streamData8(uint8_t data) = 0;
        virtual void streamData16(uint16_t data) = 0;
        virtual void streamData32(uint32_t data) = 0;
        virtual uint8_t streamData8() = 0;
        virtual uint16_t streamData16() = 0;
        virtual uint32_t streamData32() = 0;
        virtual uint8_t nativeWidth() = 0;
        virtual void blockData(uint8_t *data, uint32_t len) = 0;
        virtual void blockData(uint16_t *data, uint32_t len) = 0;
        virtual void blockData(uint32_t *data, uint32_t len) = 0;
        virtual void initializeDevice() = 0;
};

#endif
