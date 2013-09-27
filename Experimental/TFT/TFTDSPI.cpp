#include <TFT.h>

#ifdef __PIC32MX__

#define SPI_MODE DSPI_MODE0
#define SPI_SPEED 20000000UL

TFTDSPI::TFTDSPI(DSPI *spi, uint8_t cs, uint8_t dc) {
    _spi = spi;
    _cs = cs;
    _dc = dc;

    pinMode(_cs, OUTPUT);
    if (_dc != 255) pinMode(_dc, OUTPUT);

    digitalWrite(_cs, HIGH);
    if (_dc != 255) digitalWrite(_dc, HIGH);

    _spi->begin();
    _spi->setSpeed(SPI_SPEED);
}

uint8_t TFTDSPI::readCommand8() {
    uint8_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    return out;
}

void TFTDSPI::writeCommand8(uint8_t command) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    _spi->transfer(command);
    digitalWrite(_cs, HIGH);
}

uint16_t TFTDSPI::readCommand16() {
    uint16_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::writeCommand16(uint16_t command) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    _spi->transfer(command);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
}

uint32_t TFTDSPI::readCommand32() {
    uint32_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::writeCommand32(uint32_t command) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    if (_dc != 255) digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    _spi->transfer(command);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
}

uint8_t TFTDSPI::readData8() {
    uint8_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    return out;
}

void TFTDSPI::writeData8(uint8_t data) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
}

uint16_t TFTDSPI::readData16() {
    uint16_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::writeData16(uint16_t data) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
}

uint32_t TFTDSPI::readData32() {
    uint32_t out;
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    out = _spi->transfer(0);
    digitalWrite(_cs, HIGH);
    return out;
    _spi->setTransferSize(DSPI_8BIT);
}

void TFTDSPI::writeData32(uint32_t data) {
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    if (_dc != 255) digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
}

void TFTDSPI::streamStart() {
    digitalWrite(_cs, LOW);
}

void TFTDSPI::streamEnd() {
    digitalWrite(_cs, HIGH);
    _spi->setTransferSize(DSPI_8BIT);
}

void TFTDSPI::streamCommand8(uint8_t data) {
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    _spi->transfer(data);
}

uint8_t TFTDSPI::streamCommand8() {
    uint8_t out;
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    out = _spi->transfer(0);
    return out;
}

void TFTDSPI::streamCommand16(uint16_t data) {
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    _spi->transfer(data);
    _spi->setTransferSize(DSPI_8BIT);
}

uint16_t TFTDSPI::streamCommand16() {
    uint16_t out;
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    out = _spi->transfer(0);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::streamCommand32(uint32_t data) {
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    _spi->transfer(data);
    _spi->setTransferSize(DSPI_8BIT);
}

uint32_t TFTDSPI::streamCommand32() {
    uint32_t out;
    if (_dc != 255) digitalWrite(_dc, LOW);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    out = _spi->transfer(0);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::streamData8(uint8_t data) {
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    _spi->transfer(data);
}

uint8_t TFTDSPI::streamData8() {
    uint8_t out;
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_8BIT);
    out = _spi->transfer(0);
    return out;
}

void TFTDSPI::streamData16(uint16_t data) {
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    _spi->transfer(data);
    _spi->setTransferSize(DSPI_8BIT);
}

uint16_t TFTDSPI::streamData16() {
    uint16_t out;
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_16BIT);
    out = _spi->transfer(0);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::streamData32(uint32_t data) {
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    _spi->transfer(data);
    _spi->setTransferSize(DSPI_8BIT);
}

uint32_t TFTDSPI::streamData32() {
    uint32_t out;
    if (_dc != 255) digitalWrite(_dc, HIGH);
    _spi->setMode(SPI_MODE);
    _spi->setSpeed(SPI_SPEED);
    _spi->setTransferSize(DSPI_32BIT);
    out = _spi->transfer(0);
    _spi->setTransferSize(DSPI_8BIT);
    return out;
}

void TFTDSPI::blockData(uint32_t *data, uint32_t len) {
    streamStart();
    for (uint8_t i = 0; i < len; i++) {
        streamData32(data[i]);
    }
    streamEnd();
}


#endif

