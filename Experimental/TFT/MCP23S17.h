#ifndef _MCP23S17_H
#define _MCP23S17_H

class MCP23S17 : public TFTCommunicator {

    public:
        MCP23S17(DSPI *spi, uint8_t cs, uint8_t address, 
                    uint8_t db0, uint8_t db1, uint8_t db2, uint8_t db3, uint8_t db4, uint8_t db5, uint8_t db6, uint8_t db7,
                    uint8_t tcs, uint8_t rs, uint8_t e) : 
                        _spi(spi), _cs(cs), _address(address),
                        _db0(db0), _db1(db1), _db2(db2), _db3(db3),
                        _db4(db4), _db5(db5), _db6(db6), _db7(db7),
                        _tcs(tcs), _rs(rs), _enable(e) {}

        void initializeDevice();

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
        void streamCommand8(uint8_t data);
        void streamCommand16(uint16_t data);
        void streamCommand32(uint32_t data);
        uint8_t streamCommand8();
        uint16_t streamCommand16();
        uint32_t streamCommand32();
        void streamData8(uint8_t data);
        void streamData16(uint16_t data);
        void streamData32(uint32_t data);
        uint8_t streamData8();
        uint16_t streamData16();
        uint32_t streamData32();

        void blockData(uint8_t *data, uint32_t len);
        void blockData(uint16_t *data, uint32_t len);
        void blockData(uint32_t *data, uint32_t len);

        uint8_t nativeWidth() { return 8; }



    private:
        DSPI *_spi;
        uint8_t _cs;
        uint8_t _address;   
        uint8_t _db0;
        uint8_t _db1;
        uint8_t _db2;
        uint8_t _db3;
        uint8_t _db4;
        uint8_t _db5;
        uint8_t _db6;
        uint8_t _db7;
        uint8_t _tcs;
        uint8_t _rs;
        uint8_t _enable;


        void setRegister(uint8_t reg, uint8_t val);
        uint8_t readRegister(uint8_t reg);
        void setPin(uint8_t pin, uint8_t val);
        void setPinMode(uint8_t pin, uint8_t val);

        void clock();
        void setBus(uint8_t val);
};

#endif
