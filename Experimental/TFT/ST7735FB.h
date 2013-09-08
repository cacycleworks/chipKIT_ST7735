/*
 * Framebuffered and paletted superclass for the ST7735 AdaFruit 1.8" TFT screen.
 *
 * This class allocates a buffer of 160 x 128 x 8 bits, plus a palette of 256 x 16 bits,
 * so requires at least 21KiB of RAM to operate.  It WILL NOT work on the UNO32, but 
 * should work on the uC32, and certainly on the MAX32 (with hardware mods for high speed
 * SPI support)
 *
 * Requires at least version 105 of the ST7735 library
 */

#ifndef _ST7735FBH_
#define _ST7735FBH_

#include <TFT.h>

class ST7735FB : public ST7735, public Framebuffer {

	public:
        using Framebuffer::fillScreen;
        using ST7735::initializeDevice;

        ST7735FB(TFTCommunicator *comm, uint8_t variant) : ST7735(comm, variant), Framebuffer() {}; 

		void update();
        uint8_t getBuffer(uint32_t addr);
        void setBuffer(uint32_t addr, uint8_t data);
        void fillBuffer(uint8_t data);
        uint8_t getWidth();
        uint8_t getHeight();

	protected:
        uint8_t buffer[ST7735FB::Width * ST7735::Height];
};

#endif
