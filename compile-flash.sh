#!/bin/bash

arm-none-eabi-gcc -nostdlib -mcpu=cortex-m4 -fno-builtin -Wl,-T linker/stm32flinker.ld src/main.c startup/startup.c src/uart.c src/interrupt.c src/spi.c -o a.out
arm-none-eabi-objcopy -O binary a.out bin/test.bin
st-flash write bin/test.bin 0x08000000
rm a.out
