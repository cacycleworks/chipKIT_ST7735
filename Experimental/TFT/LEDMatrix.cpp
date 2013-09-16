#include <TFT.h>

struct MatrixISRList *ISRlist = NULL;

void LEDMatrix::fillScreen(uint16_t color) {
    for (int i = 0; i < 32; i++) {
        buffer[i] = color ? 0xFFFFFFFF : 0;
    }
}

void LEDMatrix::setPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= _width || y < 0 || y >= _height)
        return;

    if (color) {
        buffer[y] |= (1 << x);
    } else {
        buffer[y] &= ~(1 << x);
    }
}

void LEDMatrix::initializeDevice() {
    currentRow = 0;
    _width = _col->nativeWidth();
    _height = _row->nativeWidth();
#ifdef __PIC32MX__
    T4CONbits.TCKPS = 0b010; // 1:4
    PR4 = 40000;
    IPC4bits.T4IP = 6;
    IFS0bits.T4IF = 0;
    IEC0bits.T4IE = 1;
    T4CONbits.TON = 1;
#endif
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

void LEDMatrix::UpdateISR() {
    currentRow ++;
    currentRow %= _height;
    _col->writeData32(0xFFFFFFFF);
    _row->writeData32(1 << currentRow);
    _col->writeData32(~buffer[currentRow]);
}

#ifdef __PIC32MX__
extern "C" {
    #include <sys/attribs.h>
    void __ISR(_TIMER_4_VECTOR, IPL6) _T4Interrupt(void) {
        struct MatrixISRList *s;
        if (ISRlist) {
            for (s = ISRlist; s; s = s->next) {
                s->matrix->UpdateISR();
            }
        }
        IFS0bits.T4IF = 0;
    }
};
#endif
