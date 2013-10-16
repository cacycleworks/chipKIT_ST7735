#include <SPIRAM.h>

#define RAMSPEED 10000000UL

void SPIRAM::initializeDevice() {
    _spi->begin();
    _spi->setSpeed(RAMSPEED);
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);
}

uint8_t SPIRAM::read8(uint32_t address) {
    uint8_t b;  
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    b = _spi->transfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

uint16_t SPIRAM::read16(uint32_t address) {
    uint16_t b;  
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    b = _spi->transfer(0x00) << 8;
    b |= _spi->transfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

uint32_t SPIRAM::read32(uint32_t address) {
    uint32_t b;  
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    b = _spi->transfer(0x00) << 24;
    b |= _spi->transfer(0x00) << 16;
    b |= _spi->transfer(0x00) << 8;
    b |= _spi->transfer(0x00);
    digitalWrite(_cs, HIGH);
    return b;
}

void SPIRAM::read8(uint32_t address, uint8_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = _spi->transfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPIRAM::read16(uint32_t address, uint16_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = _spi->transfer(0x00) << 8;
        b[i] |= _spi->transfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPIRAM::read32(uint32_t address, uint32_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x03);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        b[i] = _spi->transfer(0x00) << 24;
        b[i] |= _spi->transfer(0x00) << 16;
        b[i] |= _spi->transfer(0x00) << 8;
        b[i] |= _spi->transfer(0x00);
    }
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write8(uint32_t address, uint8_t b) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    _spi->transfer(b);
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write16(uint32_t address, uint16_t b) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    _spi->transfer((b >> 8) & 0xFF);
    _spi->transfer(b & 0xFF);
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write32(uint32_t address, uint32_t b) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    _spi->transfer((b >> 24) & 0xFF);
    _spi->transfer((b >> 16) & 0xFF);
    _spi->transfer((b >> 8) & 0xFF);
    _spi->transfer(b & 0xFF);
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write8(uint32_t address, uint8_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        _spi->transfer(b[i]);
    }
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write16(uint32_t address, uint16_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        _spi->transfer((b[i] >> 8) & 0xFF);
        _spi->transfer(b[i] & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}

void SPIRAM::write32(uint32_t address, uint32_t *b, uint32_t len) {
    _spi->setSpeed(RAMSPEED);
    digitalWrite(_cs, LOW);
    _spi->transfer(0x02);
    _spi->transfer((address >> 16) & 0xFF);
    _spi->transfer((address >> 8) & 0xFF);
    _spi->transfer((address >> 0) & 0xFF);
    for (uint32_t i = 0; i < len; i++) {
        _spi->transfer((b[i] >> 24) & 0xFF);
        _spi->transfer((b[i] >> 16) & 0xFF);
        _spi->transfer((b[i] >> 8) & 0xFF);
        _spi->transfer(b[i] & 0xFF);
    }
    digitalWrite(_cs, HIGH);
}


