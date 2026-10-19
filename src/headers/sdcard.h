#ifndef SDCARD_H
#define SDCARD_H

#include "spi.h"
#include "buffer.h"

#define CMD0            ((buffer) {.buffer={(char) 0b01000000, (char) 0b00000000, (char) 0b00000000, (char) 0b00000000, (char) 0b00000000, (char) 0b10010101}, .position=6})
#define CMD0_RESPONSE   8


int sd_init(void);

#endif