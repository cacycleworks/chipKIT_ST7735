#include <TFT.h>

void HD44780::initializeDevice() {
}

void HD44780::command(uint8_t cmd) {
    _comm->writeCommand8(cmd);
    delay(4);
}

void HD44780::data(uint8_t d) {
    _comm->writeData8(d);
}

void HD44780::clearScreen() {
    command(0b00000001);
}

void HD44780::home() {
    command(0b00000010);
}

void HD44780::displayOn() {
    command(0b00001100 |
        (_cursor ? 0b10 : 0b00) |
        (_blink  ? 0b01 : 0b00));
}

void HD44780::displayOff() {
    command(0b00001000 |
        (_cursor ? 0b10 : 0b00) |
        (_blink  ? 0b01 : 0b00));
}

