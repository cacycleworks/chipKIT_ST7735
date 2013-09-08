#ifndef _TFT_COMMUNICATOR_H
#define _TFT_COMMUNICATOR_H

class TFTCommunicator
{
    public:
        virtual void writeCommand(uint8_t command) {};
        virtual void writeData8(uint8_t data) {};
        virtual void writeData16(uint16_t data) {};
        virtual void writeData32(uint32_t data) {};
        virtual void commandStreamStart() {};
        virtual void commandStreamEnd() {};
        virtual void commandStream(uint8_t command) {};
        virtual void dataStreamStart() {};
        virtual void dataStreamEnd() {};
        virtual void dataStream8(uint16_t data) {};
        virtual void dataStream16(uint16_t data) {};
        virtual void dataStream32(uint16_t data) {};
};

#endif
