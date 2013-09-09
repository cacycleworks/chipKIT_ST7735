#include <TFT.h>

struct MatrixISRList *ISRlist = NULL;

void Matrix::fillScreen(uint16_t color) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = color ? 255 : 0;
    }
}

void Matrix::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
        return;

    if (color) {
        buffer[y] |= (1 << x);
    } else {
        buffer[y] &= ~(1 << x);
    }
}

void Matrix::initializeDevice() {
    currentRow = 0;
    T4CONbits.TCKPS = 0b010; // 1:4
    PR4 = 2000;
    IPC4bits.T4IP = 6;
    IFS0bits.T4IF = 0;
    IEC0bits.T4IE = 1;
    T4CONbits.TON = 1;
    struct MatrixISRList *n = (struct MatrixISRList *)malloc(sizeof(struct MatrixISRList));
    struct MatrixISRList *s;
    n->matrix = this;
    n->next = NULL;
    if (!ISRlist) {
        ISRlist = n;
    } else {
        for (s = ISRlist; s->next; s = s->next);
        s->next = n;
    }
}

void Matrix::ISR() {
    currentRow ++;
    currentRow %= 8;
    _col->writeData8(255);
    _row->writeData8(1 << currentRow);
    _col->writeData8(~buffer[currentRow]);
}

extern "C" {
    #include <sys/attribs.h>
    void __ISR(_TIMER_4_VECTOR, IPL6) _T4Interrupt(void) {
        struct MatrixISRList *s;
        if (ISRlist) {
            for (s = ISRlist; s; s = s->next) {
                s->matrix->ISR();
            }
        }
        IFS0bits.T4IF = 0;
    }
};
