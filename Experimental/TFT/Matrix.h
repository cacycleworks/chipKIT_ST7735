#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <TFT.h>

class Matrix : public TFT {

	public:
        const static int16_t Width = 8;
        const static int16_t Height = 8;

		Matrix(TFTCommunicator *row, TFTCommunicator *col) : TFT(NULL), _row(row), _col(col) {}

        void fillScreen(uint16_t color);
        void setPixel(int16_t x, int16_t y, uint16_t color);
        void setRotation(uint8_t r) {}; // Not implemented
        void invertDisplay(boolean i) {}; // Not implemented
        void displayOn() {} // Not implemented
        void displayOff() {} // Not implemented

        void initializeDevice();
        void ISR();

	protected:
        TFTCommunicator *_row;
        TFTCommunicator *_col;
        uint8_t buffer[8];
        uint8_t currentRow;
};

struct MatrixISRList {
    Matrix *matrix;
    struct MatrixISRList *next;
};

#endif
