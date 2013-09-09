#include <TFT.h>

RawPar8::RawPar8(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;
    _d4 = d4;
    _d5 = d5;
    _d6 = d6;
    _d7 = d7;

    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);
    pinMode(_d4, OUTPUT);
    pinMode(_d5, OUTPUT);
    pinMode(_d6, OUTPUT);
    pinMode(_d7, OUTPUT);

    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
    digitalWrite(_d0, LOW);
}

void RawPar8::setBus(uint8_t value) {
    digitalWrite(_d7, value & 0x80);
    digitalWrite(_d6, value & 0x40);
    digitalWrite(_d5, value & 0x20);
    digitalWrite(_d4, value & 0x10);
    digitalWrite(_d3, value & 0x08);
    digitalWrite(_d2, value & 0x04);
    digitalWrite(_d1, value & 0x02);
    digitalWrite(_d0, value & 0x01);
}

void RawPar8::writeCommand(uint8_t command) {
    setBus(command);
}

void RawPar8::commandStreamStart() {
}

void RawPar8::commandStreamEnd() {
}

void RawPar8::commandStream(uint8_t data) {
    setBus(data);
}

void RawPar8::writeData8(uint8_t data) {
    setBus(data);
}

void RawPar8::writeData16(uint16_t data) {
    setBus(data & 0xFF);
}

void RawPar8::writeData32(uint32_t data) {
    setBus(data & 0xFF);
}

void RawPar8::dataStreamStart() {
}

void RawPar8::dataStreamEnd() {
}

void RawPar8::dataStream8(uint8_t data) {
    setBus(data);
}

void RawPar8::dataStream16(uint16_t data) {
    setBus(data & 0xFF);
}

void RawPar8::dataStream32(uint32_t data) {
    setBus(data & 0xFF);
}

