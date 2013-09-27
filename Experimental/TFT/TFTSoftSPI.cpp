#include <TFT.h>

TFTSoftSPI::TFTSoftSPI(uint8_t sdo, uint8_t sck, uint8_t cs, uint8_t dc) {
    _sdo = sdo;
    _sck = sck;
    _cs = cs;
    _dc = dc;

    pinMode(_sdo, OUTPUT);
    pinMode(_sck, OUTPUT);
    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);

    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);
}

void TFTSoftSPI::writeCommand8(uint8_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, command);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::writeCommand16(uint16_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, command >> 8);
    shiftOut(_sdo, _sck, MSBFIRST, command);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::writeCommand32(uint32_t command) {
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, command >> 24);
    shiftOut(_sdo, _sck, MSBFIRST, command >> 16);
    shiftOut(_sdo, _sck, MSBFIRST, command >> 8);
    shiftOut(_sdo, _sck, MSBFIRST, command);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::streamStart() {
    digitalWrite(_cs, LOW);
}

void TFTSoftSPI::streamEnd() {
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::writeData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, data);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::writeData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, data >> 8);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::writeData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 24) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 16) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >>  8) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
    digitalWrite(_cs, HIGH);
}

void TFTSoftSPI::streamCommand8(uint8_t data) {
    digitalWrite(_dc, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, data);
}

void TFTSoftSPI::streamCommand16(uint16_t data) {
    digitalWrite(_dc, LOW);
    shiftOut(_sdo, _sck, MSBFIRST, data >> 8);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
}

void TFTSoftSPI::streamCommand32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 24) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 16) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >>  8) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
}

void TFTSoftSPI::streamData8(uint8_t data) {
    digitalWrite(_dc, HIGH);
    shiftOut(_sdo, _sck, MSBFIRST, data);
}

void TFTSoftSPI::streamData16(uint16_t data) {
    digitalWrite(_dc, HIGH);
    shiftOut(_sdo, _sck, MSBFIRST, data >> 8);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
}

void TFTSoftSPI::streamData32(uint32_t data) {
    digitalWrite(_dc, HIGH);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 24) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >> 16) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, (data >>  8) & 0xFF);
    shiftOut(_sdo, _sck, MSBFIRST, data & 0xFF);
}

