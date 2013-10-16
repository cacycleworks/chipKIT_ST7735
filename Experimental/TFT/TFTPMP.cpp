#include <TFT.h>

TFTPMP::TFTPMP() {
}

void TFTPMP::initializeDevice() {
    PMCON = 1<<9 | 1<<8;
    //                          WAITB   WAITM    WAITE
    PMMODE = 1<<10 | 0b10<<8 | (2<<6) | (2<<2) | 1;
    PMADDR = 0;
    PMAEN = 1;
    PMCONSET = 1<<15;
}

void TFTPMP::writeCommand8(uint8_t command) {
    writeCommand16(command);
}

void TFTPMP::writeCommand16(uint16_t command) {
    PMADDR = 0;
    PMDIN = command;
    while (PMSTAT & (1<<15));
}

void TFTPMP::writeCommand32(uint32_t command) {
    writeCommand16(command >> 16);
    writeCommand16(command); 
}

void TFTPMP::streamStart() {
}

void TFTPMP::streamEnd() {
}

void TFTPMP::writeData8(uint8_t data) {
    writeData16(data);
}

void TFTPMP::writeData16(uint16_t data) {
    PMADDR = 1;
    PMDIN = data;
    while (PMSTAT & (1<<15));
}

void TFTPMP::writeData32(uint32_t data) {
    writeData16(data >> 16);
    writeData16(data);
}

void TFTPMP::streamCommand8(uint8_t data) {
    writeCommand8(data);
}

void TFTPMP::streamCommand16(uint16_t data) {
    writeCommand16(data);
}

void TFTPMP::streamCommand32(uint32_t data) {
    writeCommand32(data);
}

void TFTPMP::streamData8(uint8_t data) {
    writeData8(data);
}

void TFTPMP::streamData16(uint16_t data) {
    writeData16(data);
}

void TFTPMP::streamData32(uint32_t data) {
    writeData32(data);
}

uint8_t TFTPMP::streamCommand8() { return 0; }
uint16_t TFTPMP::streamCommand16() { return 0; }
uint32_t TFTPMP::streamCommand32() { return 0; }
uint8_t TFTPMP::streamData8() { return 0; }
uint16_t TFTPMP::streamData16() { return 0; }
uint32_t TFTPMP::streamData32() { return 0; }

void TFTPMP::blockData(uint8_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData8(data[i]);
    }
}

void TFTPMP::blockData(uint16_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData16(data[i]);
    }
}

void TFTPMP::blockData(uint32_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; i++) {
        writeData32(data[i]);
    }
}

uint8_t TFTPMP::readCommand8() {
    return 0;
} 

uint16_t TFTPMP::readCommand16() {
    return 0;
} 

uint32_t TFTPMP::readCommand32() {
    return 0;
} 

uint8_t TFTPMP::readData8() {
    return 0;
} 

uint16_t TFTPMP::readData16() {
    return 0;
} 

uint32_t TFTPMP::readData32() {
    return 0;
} 




