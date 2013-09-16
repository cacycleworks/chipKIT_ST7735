#include <TFT.h>

RawPar::RawPar(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                 uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14, uint8_t d15,
                 uint8_t d16, uint8_t d17, uint8_t d18, uint8_t d19, uint8_t d20, uint8_t d21, uint8_t d22, uint8_t d23,
                 uint8_t d24, uint8_t d25, uint8_t d26, uint8_t d27, uint8_t d28, uint8_t d29, uint8_t d30, uint8_t d31) {
    _d[0] = d0;
    _d[1] = d1;
    _d[2] = d2;
    _d[3] = d3;
    _d[4] = d4;
    _d[5] = d5;
    _d[6] = d6;
    _d[7] = d7;
    _d[8] = d8;
    _d[9] = d9;
    _d[10] = d10;
    _d[11] = d11;
    _d[12] = d12;
    _d[13] = d13;
    _d[14] = d14;
    _d[15] = d15;
    _d[16] = d16;
    _d[17] = d17;
    _d[18] = d18;
    _d[19] = d19;
    _d[20] = d20;
    _d[21] = d21;
    _d[22] = d22;
    _d[23] = d23;
    _d[24] = d24;
    _d[25] = d25;
    _d[26] = d26;
    _d[27] = d27;
    _d[28] = d28;
    _d[29] = d29;
    _d[30] = d30;
    _d[31] = d31;

    _width = 0;
    for (int i = 0; i < 32; i++) {
        if (_d[i] != 255) { 
            pinMode(_d[i], OUTPUT); digitalWrite(_d[i], HIGH); 
            _width++;
        }
    }

}

void RawPar::setBus(uint32_t value) {
    for (int i = 0; i < 32; i++) {
        if (_d[i] != 255) {
            digitalWrite(_d[i], (value >> i) & 1);
        }
    }
}

void RawPar::writeCommand(uint8_t command) {
    setBus(command);
}

void RawPar::commandStreamStart() {
}

void RawPar::commandStreamEnd() {
}

void RawPar::commandStream(uint8_t data) {
    setBus(data);
}

void RawPar::writeData8(uint8_t data) {
    setBus(data);
}

void RawPar::writeData16(uint16_t data) {
    setBus(data);
}

void RawPar::writeData32(uint32_t data) {
    setBus(data);
}

void RawPar::dataStreamStart() {
}

void RawPar::dataStreamEnd() {
}

void RawPar::dataStream8(uint8_t data) {
    setBus(data);
}

void RawPar::dataStream16(uint16_t data) {
    setBus(data);
}

void RawPar::dataStream32(uint32_t data) {
    setBus(data);
}

uint8_t RawPar::nativeWidth() {
    return _width;
}

