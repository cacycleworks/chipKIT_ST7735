#include <TFT.h>

#define SPI_SPEED 2000000UL
#define SPI_MODE DSPI_MODE3

#define IODIRA 0x00
#define IODIRB 0x01
#define IPOLA 0x02
#define IPOLB 0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA 0x06
#define DEFVALB 0x07
#define INTCONA 0x08
#define INTCONB 0x09
#define IOCONA 0x0A
#define IOCONB 0x0B
#define GPPUA 0x0C
#define GPPUB 0x0D
#define INTFA 0x0E
#define INTFB 0x0F
#define INTCAPA 0x10
#define INTCAPB 0x11
#define GPIOA 0x12
#define GPIOB 0x13
#define OLATA 0x14
#define OLATB 0x15

void MCP23S17::setRegister(uint8_t reg, uint8_t val) {
    _spi->setSpeed(SPI_SPEED);
    _spi->setMode(SPI_MODE);
    _spi->setTransferSize(DSPI_8BIT);
    digitalWrite(_cs, LOW);
    _spi->transfer(0b01000000 | (_address << 1));
    _spi->transfer(reg);
    _spi->transfer(val);
    digitalWrite(_cs, HIGH);
}

uint8_t MCP23S17::readRegister(uint8_t reg) {
    uint8_t val;
    _spi->setSpeed(SPI_SPEED);
    _spi->setMode(SPI_MODE);
    _spi->setTransferSize(DSPI_8BIT);
    digitalWrite(_cs, LOW);
    _spi->transfer(0b01000001 | (_address << 1));
    _spi->transfer(reg);
    val = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    return val;
}

void MCP23S17::setPin(uint8_t pin, uint8_t val) {
    uint8_t pval;
    if (pin >= 16) {
        return;
    }
    if (val) {
        if (pin >= 8) {
            pval = readRegister(OLATB);
            pval |= (1<<(pin-8));
            setRegister(OLATB, pval);
        } else {
            pval = readRegister(OLATA);
            pval |= (1<<pin);
            setRegister(OLATA, pval);
        }
    } else {
        if (pin >= 8) {
            pval = readRegister(OLATB);
            pval &= ~(1<<(pin-8));
            setRegister(OLATB, pval);
        } else {
            pval = readRegister(OLATA);
            pval &= ~(1<<pin);
            setRegister(OLATA, pval);
        }
    }
}

void MCP23S17::setPinMode(uint8_t pin, uint8_t val) {
    uint8_t pval;
    if (pin >= 16) {
        return;
    }
    if (val) {
        if (pin >= 8) {
            pval = readRegister(IODIRB);
            pval |= (1<<(pin-8));
            setRegister(IODIRB, pval);
        } else {
            pval = readRegister(IODIRA);
            pval |= (1<<pin);
            setRegister(IODIRA, pval);
        }
    } else {
        if (pin >= 8) {
            pval = readRegister(IODIRB);
            pval &= ~(1<<(pin-8));
            setRegister(IODIRB, pval);
        } else {
            pval = readRegister(IODIRA);
            pval &= ~(1<<pin);
            setRegister(IODIRA, pval);
        }
    }
}

void MCP23S17::initializeDevice() {
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
    _spi->begin();
    setRegister(0x0A, 0b00111000);


    setPinMode(0, OUTPUT);
    while(1) {
        setPin(0, HIGH);
        setPin(0, LOW);
    }


    setPinMode(_db0, OUTPUT);
    setPinMode(_db1, OUTPUT);
    setPinMode(_db2, OUTPUT);
    setPinMode(_db3, OUTPUT);
    setPinMode(_db4, OUTPUT);
    setPinMode(_db5, OUTPUT);
    setPinMode(_db6, OUTPUT);
    setPinMode(_db7, OUTPUT);
    setPinMode(_tcs, OUTPUT);
    setPinMode(_rs, OUTPUT);
    setPinMode(_enable, OUTPUT);
}

uint8_t MCP23S17::readCommand8() {
    return 0;
}

uint16_t MCP23S17::readCommand16() {
    return 0;
}

uint32_t MCP23S17::readCommand32() {
    return 0;
}

void MCP23S17::setBus(uint8_t val) {
    setPin(_db7, (val >> 7) & 1);
    setPin(_db6, (val >> 6) & 1);
    setPin(_db5, (val >> 5) & 1);
    setPin(_db4, (val >> 4) & 1);
    setPin(_db3, (val >> 3) & 1);
    setPin(_db2, (val >> 2) & 1);
    setPin(_db1, (val >> 1) & 1);
    setPin(_db0, (val >> 0) & 1);
}

void MCP23S17::clock() {
    setPin(_enable, HIGH);
    setPin(_enable, LOW);
}

void MCP23S17::writeCommand8(uint8_t command) {
    setPin(_rs, LOW);
    setPin(_tcs, LOW);
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

void MCP23S17::writeCommand16(uint16_t command) {
    setPin(_rs, LOW);
    setPin(_tcs, LOW);
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

void MCP23S17::writeCommand32(uint32_t command) {
    setPin(_rs, LOW);
    setPin(_tcs, LOW);
    setBus(command >> 24);
    clock();
    setBus(command >> 16);
    clock();
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

void MCP23S17::writeData8(uint8_t command) {
    setPin(_rs, HIGH);
    setPin(_tcs, LOW);
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

void MCP23S17::writeData16(uint16_t command) {
    setPin(_rs, HIGH);
    setPin(_tcs, LOW);
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

void MCP23S17::writeData32(uint32_t command) {
    setPin(_rs, HIGH);
    setPin(_tcs, LOW);
    setBus(command >> 24);
    clock();
    setBus(command >> 16);
    clock();
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
    setPin(_tcs, HIGH);
}

uint8_t MCP23S17::readData8() {
    return 0;
}

uint16_t MCP23S17::readData16() {
    return 0;
}

uint32_t MCP23S17::readData32() {
    return 0;
}

void MCP23S17::streamStart() {
    setPin(_tcs, LOW);
}

void MCP23S17::streamEnd() {
    setPin(_tcs, HIGH);
}

void MCP23S17::streamCommand8(uint8_t command) {
    setPin(_rs, LOW);
    setBus(command);
    clock();
}

void MCP23S17::streamCommand16(uint16_t command) {
    setPin(_rs, LOW);
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
}

void MCP23S17::streamCommand32(uint32_t command) {
    setPin(_rs, LOW);
    setBus(command >> 24);
    clock();
    setBus(command >> 16);
    clock();
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
}

void MCP23S17::streamData8(uint8_t command) {
    setPin(_rs, LOW);
    setBus(command);
    clock();
}

void MCP23S17::streamData16(uint16_t command) {
    setPin(_rs, LOW);
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
}

void MCP23S17::streamData32(uint32_t command) {
    setPin(_rs, LOW);
    setBus(command >> 24);
    clock();
    setBus(command >> 16);
    clock();
    setBus(command >> 8);
    clock();
    setBus(command);
    clock();
}

uint8_t MCP23S17::streamCommand8() {
    return 0;
}

uint16_t MCP23S17::streamCommand16() {
    return 0;
}

uint32_t MCP23S17::streamCommand32() {
    return 0;
}

uint8_t MCP23S17::streamData8() {
    return 0;
}

uint16_t MCP23S17::streamData16() {
    return 0;
}

uint32_t MCP23S17::streamData32() {
    return 0;
}

void MCP23S17::blockData(uint8_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        streamData8(data[i]);
    }
}

void MCP23S17::blockData(uint16_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        streamData16(data[i]);
    }
}

void MCP23S17::blockData(uint32_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        streamData32(data[i]);
    }
}


