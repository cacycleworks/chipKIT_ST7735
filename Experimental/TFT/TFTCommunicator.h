#ifndef _TFT_COMMUNICATOR_H
#define _TFT_COMMUNICATOR_H

class TFTCommunicator
{
    public:
        virtual void writeCommand(uint8_t command) = 0;
        virtual void writeData8(uint8_t data) = 0;
        virtual void writeData16(uint16_t data) = 0;
        virtual void writeData32(uint32_t data) = 0;
        virtual void commandStreamStart() = 0;
        virtual void commandStreamEnd() = 0;
        virtual void commandStream(uint8_t command) = 0;
        virtual void dataStreamStart() = 0;
        virtual void dataStreamEnd() = 0;
        virtual void dataStream8(uint8_t data) = 0;
        virtual void dataStream16(uint16_t data) = 0;
        virtual void dataStream32(uint32_t data) = 0;
        virtual uint8_t nativeWidth() = 0;
        virtual void blockData(uint32_t *data, uint32_t len) = 0;
};

#endif
