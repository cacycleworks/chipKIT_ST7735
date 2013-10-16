#include <TFT.h>
/*
  lcd.command(0x29);      // 4 bit interface    0b00101001  => table 1
  lcd.command(0x1C);      // bias set           0b00011100
  lcd.command(0x52);      // power control      0b01010010
  lcd.command(0x69);      // follower control   0b01101001
  lcd.command(0x74);      // set contrast
  lcd.command(0x38);      // function set
*/
void DOGMe::initializeDevice() {
    _comm->initializeDevice();
    _table = 0;

//    setBits(_bits);
//    setBias(1);
//    setFollower(1);

    if (_bits == 4) {
        command(0x29);      // 4 bit interface    0b00101001  => table 1
    } else {
        command(0x21);      // 4 bit interface    0b00101001  => table 1
    }
    command(0x1C);      // bias set           0b00011100
    command(0x52);      // power control      0b01010010
    command(0x69);      // follower control   0b01101001
    command(0x74);      // set contrast
    command(0x38);      // function set

    //singleHeight();
    //displayOn();
    //clearScreen();
    //home();
    //setContrast(100);
}

void DOGMe::table(uint8_t tab) {
    _table = tab & 0b11;
    setFunction();
}

void DOGMe::setBias(uint8_t b) {
    table(1);
    command(0b00010100 | (b ? 0b00001000 : 0b00000000));
    table(0);
}

void DOGMe::setBits(uint8_t b) {
    _bits = b;
    setFunction();
    setFunction();
}

void DOGMe::setLines(uint8_t l) {
    _lines = l;
    setFunction();
}

void DOGMe::setFunction() {
    uint8_t function = 0b00100000;
    function |= (_bits  == 8 ? 0b00001000 : 0);
    function |= (_lines == 2 ? 0b00000100 : 0);
    function |= _table;
    command(function);
}

void DOGMe::setContrast(uint8_t c) {
    if (c > 99) c = 99;
    table(1);
    uint8_t contrast = c * 64 / 100;
    command(0b01010000 | ((contrast >> 4) & 0b11));
    command(0b0111 | (contrast & 0x0F));
    table(0);
}

void DOGMe::write(uint8_t c) {
    data(c);
}

void DOGMe::setFollower(uint8_t f) {
    table(1);
    command(0b01101000 | (f & 0b111));
    table(0);
}

void DOGMe::singleHeight() {
    table(2);
    command(0b00010000);
    table(0);
}

void DOGMe::doubleHeight() {
    table(2);
    command(0b00011000);
    table(0);
}

