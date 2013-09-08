#include <TFT.h>

TFTDSPI::TFTDSPI(DSPI *spi, uint8_t cs, uint8_t dc) {
    _spi = spi;
    _cs = cs;
    _dc = dc;

    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);

    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);

    _spi->begin();
    _spi->setSpeed(20000000UL);
}

void TFTDSPI::writeCommand(uint8_t command) {
    _spi->setTransferSize(DSPI_8BIT);
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    _spi->transfer(command);
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::commandStreamStart() {
    _spi->setTransferSize(DSPI_8BIT);
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
}

void TFTDSPI::commandStreamEnd() {
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::commandStream(uint8_t data) {
    _spi->transfer(data);
}

void TFTDSPI::writeData8(uint8_t data) {
    _spi->setTransferSize(DSPI_8BIT);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::writeData16(uint16_t data) {
    _spi->setTransferSize(DSPI_16BIT);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::writeData32(uint32_t data) {
    _spi->setTransferSize(DSPI_32BIT);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    _spi->transfer(data);
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::dataStreamStart() {
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
}

void TFTDSPI::dataStreamEnd() {
    digitalWrite(_cs, HIGH);
}

void TFTDSPI::dataStream8(uint8_t data) {
    _spi->setTransferSize(DSPI_8BIT);
    _spi->transfer(data);
}

void TFTDSPI::dataStream16(uint16_t data) {
    _spi->setTransferSize(DSPI_16BIT);
    _spi->transfer(data);
}

void TFTDSPI::dataStream32(uint32_t data) {
    _spi->setTransferSize(DSPI_32BIT);
    _spi->transfer(data);
}

