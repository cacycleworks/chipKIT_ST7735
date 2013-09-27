#include <TFT.h>

TFTPar4::TFTPar4(uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    _cs = 255;
    _dc = dc;
    _clk = clk;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;

    pinMode(_dc, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);

    digitalWrite(_dc, LOW);
    digitalWrite(_clk, LOW);
}

TFTPar4::TFTPar4(uint8_t cs, uint8_t dc, uint8_t clk, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
    _cs = cs;
    _dc = dc;
    _clk = clk;
    _d0 = d0;
    _d1 = d1;
    _d2 = d2;
    _d3 = d3;

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_clk, OUTPUT);
    pinMode(_d0, OUTPUT);
    pinMode(_d1, OUTPUT);
    pinMode(_d2, OUTPUT);
    pinMode(_d3, OUTPUT);

    digitalWrite(_cs, LOW);
    digitalWrite(_dc, LOW);
    digitalWrite(_clk, LOW);
}

void TFTPar4::clock() {
    digitalWrite(_clk, LOW);
    delayMicroseconds(1);
    digitalWrite(_clk, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clk, LOW);
    delayMicroseconds(100);
}

void TFTPar4::setBus(uint8_t value) {
    digitalWrite(_d3, value & 0x08);
    digitalWrite(_d2, value & 0x04);
    digitalWrite(_d1, value & 0x02);
    digitalWrite(_d0, value & 0x01);
}

void TFTPar4::writeCommand8(uint8_t command) {
    digitalWrite(_dc, LOW);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((command >> 4) & 0x0F);
    clock();
    setBus(command & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::writeCommand16(uint16_t command) {
    digitalWrite(_dc, LOW);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((command >> 12) & 0x0F);
    clock();
    setBus((command >> 8) & 0x0F);
    clock();
    setBus((command >> 4) & 0x0F);
    clock();
    setBus(command & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::writeCommand32(uint32_t command) {
    digitalWrite(_dc, LOW);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((command >> 28) & 0x0F);
    clock();
    setBus((command >> 24) & 0x0F);
    clock();
    setBus((command >> 20) & 0x0F);
    clock();
    setBus((command >> 16) & 0x0F);
    clock();
    setBus((command >> 12) & 0x0F);
    clock();
    setBus((command >> 8) & 0x0F);
    clock();
    setBus((command >> 4) & 0x0F);
    clock();
    setBus(command & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::streamStart() {
    if(_cs != 255) digitalWrite(_cs, HIGH);
}

void TFTPar4::streamEnd() {
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::writeData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::writeData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::writeData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    if(_cs != 255) digitalWrite(_cs, HIGH);
    setBus((data >> 28) & 0x0F);
    clock();
    setBus((data >> 24) & 0x0F);
    clock();
    setBus((data >> 20) & 0x0F);
    clock();
    setBus((data >> 16) & 0x0F);
    clock();
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
    if(_cs != 255) digitalWrite(_cs, LOW);
}

void TFTPar4::streamCommand8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}

void TFTPar4::streamCommand16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}

void TFTPar4::streamCommand32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 28) & 0x0F);
    clock();
    setBus((data >> 24) & 0x0F);
    clock();
    setBus((data >> 20) & 0x0F);
    clock();
    setBus((data >> 16) & 0x0F);
    clock();
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}

void TFTPar4::streamData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}

void TFTPar4::streamData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}

void TFTPar4::streamData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    setBus((data >> 28) & 0x0F);
    clock();
    setBus((data >> 24) & 0x0F);
    clock();
    setBus((data >> 20) & 0x0F);
    clock();
    setBus((data >> 16) & 0x0F);
    clock();
    setBus((data >> 12) & 0x0F);
    clock();
    setBus((data >> 8) & 0x0F);
    clock();
    setBus((data >> 4) & 0x0F);
    clock();
    setBus(data & 0x0F);
    clock();
}


