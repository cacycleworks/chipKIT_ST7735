#include <TFT.h>

TFTPar8::TFTPar8(uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
    _cs = cs;
    _dc = dc;
    _clk = clk;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;
    _d4 = d4;
    _d5 = d5;
    _d6 = d6;
    _d7 = d7;

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);
    pinMode(_d4, OUTPUT);
    pinMode(_d5, OUTPUT);
    pinMode(_d6, OUTPUT);
    pinMode(_d7, OUTPUT);

    digitalWrite(_cs, LOW);
    digitalWrite(_dc, LOW);
    digitalWrite(_clk, LOW);
}

void TFTPar8::clock() {
    digitalWrite(_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk, LOW);
    delayMicroseconds(1);
}

void TFTPar8::setBus(uint8_t value) {
    digitalWrite(_d7, value & 0x80);
    digitalWrite(_d6, value & 0x40);
    digitalWrite(_d5, value & 0x20);
    digitalWrite(_d4, value & 0x10);
    digitalWrite(_d3, value & 0x08);
    digitalWrite(_d2, value & 0x04);
    digitalWrite(_d1, value & 0x02);
    digitalWrite(_d0, value & 0x01);
}

void TFTPar8::writeCommand8(uint8_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, HIGH);
    setBus(command);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::writeCommand16(uint16_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, HIGH);
    setBus((command >> 8) & 0xFF);
    clock();
    setBus(command & 0xFF);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::writeCommand32(uint32_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, HIGH);
    setBus((command >> 24) & 0xFF);
    clock();
    setBus((command >> 16) & 0xFF);
    clock();
    setBus((command >> 8) & 0xFF);
    clock();
    setBus(command & 0xFF);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::streamStart() {
    digitalWrite(_cs, HIGH);
}

void TFTPar8::streamEnd() {
    digitalWrite(_cs, LOW);
}

void TFTPar8::writeData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, HIGH);
    setBus(data);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::writeData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, HIGH);
    setBus(data >> 8);
    clock();
    setBus(data & 0xFF);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::writeData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, HIGH);
    setBus((data >> 24) & 0xFF);
    clock();
    setBus((data >> 16) & 0xFF);
    clock();
    setBus((data >> 8) & 0xFF);
    clock();
    setBus(data & 0xFF);
    clock();
    digitalWrite(_cs, LOW);
}

void TFTPar8::streamCommand8(uint8_t data) {
    digitalWrite(_dc, LOW);
    setBus(data);
    clock();
}

void TFTPar8::streamCommand16(uint16_t data) {
    digitalWrite(_dc, LOW);
    setBus(data >> 8);
    clock();
    setBus(data & 0xFF);
    clock();
}

void TFTPar8::streamCommand32(uint32_t data) {
    digitalWrite(_dc, LOW);
    setBus((data >> 24) & 0xFF);
    clock();
    setBus((data >> 16) & 0xFF);
    clock();
    setBus((data >> 8) & 0xFF);
    clock();
    setBus(data & 0xFF);
    clock();
}

void TFTPar8::streamData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    setBus(data);
    clock();
}

void TFTPar8::streamData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    setBus(data >> 8);
    clock();
    setBus(data & 0xFF);
    clock();
}

void TFTPar8::streamData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 24) & 0xFF);
    clock();
    setBus((data >> 16) & 0xFF);
    clock();
    setBus((data >> 8) & 0xFF);
    clock();
    setBus(data & 0xFF);
    clock();
}


