#include <SRAM.h>

void SRAM::initializeDevice() {
	memset(_buffer, 0, _size);
}

uint8_t SRAM::read8(uint32_t address) {
	return _buffer[address];
}

uint16_t SRAM::read16(uint32_t address) {
	return ((uint16_t *)_buffer)[address];
}

uint32_t SRAM::read32(uint32_t address) {
	return ((uint32_t *)_buffer)[address];
}

void SRAM::read8(uint32_t address, uint8_t *b, uint32_t len) {
	memcpy(b, _buffer+address, len);
}

void SRAM::read16(uint32_t address, uint16_t *b, uint32_t len) {
	memcpy(b, (uint8_t *)(_buffer+address), len*2);
}

void SRAM::read32(uint32_t address, uint32_t *b, uint32_t len) {
	memcpy(b, (uint8_t *)(_buffer+address), len*4);
}

void SRAM::write8(uint32_t address, uint8_t b) {
	_buffer[address] = b;
}

void SRAM::write16(uint32_t address, uint16_t b) {
	((uint16_t *)_buffer)[address] = b;
}

void SRAM::write32(uint32_t address, uint32_t b) {
	((uint32_t *)_buffer)[address] = b;
}

void SRAM::write8(uint32_t address, uint8_t *b, uint32_t len) {
	memcpy(_buffer+address, b, len);
}

void SRAM::write16(uint32_t address, uint16_t *b, uint32_t len) {
	memcpy(_buffer+address, (uint8_t *)b, len*2);
}

void SRAM::write32(uint32_t address, uint32_t *b, uint32_t len) {
	memcpy(_buffer+address, (uint8_t *)b, len*4);
}

void SRAM::setAll8(uint8_t data) {
    memset(_buffer, data, _size);
}

void SRAM::setAll16(uint16_t data) {
    for (uint32_t x = 0; x < _size/2; x++) {
        write16(x, data);
    }
}

void SRAM::setAll32(uint32_t data) {
    for (uint32_t x = 0; x < _size/4; x++) {
        write32(x, data);
    }
}


