#ifndef _DOGME_H
#define _DOGME_H

#include <TFT.h>

class DOGMe : public HD44780 {
    public:
        DOGMe(TFTCommunicator *comm, uint8_t w, uint8_t h) : HD44780(comm, w, h) {};
        void initializeDevice();
        void table(uint8_t tab);
        void setBits(uint8_t b);
        void setLines(uint8_t l);
        void setFunction();
        void setContrast(uint8_t c);
        void setBias(uint8_t b);
        void setFollower(uint8_t f);
        void singleHeight();
        void doubleHeight();
        void write(uint8_t c);

    private:
        uint8_t _table;
        uint8_t _lines;
};

#endif
