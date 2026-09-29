# Stm32-Texteditor
This project, based on the STM32 Nucleo-F446RE, will communicate with my computer via UART. On the computer side I will use a serial monitor like PUTTY or minicom. Once opend the Nucleo board will display a basic shell-like interface where I will have a few basic commands to create and manage text files. Those text files will be stored on an SD card that will be formatted to FAT32. My final goal is for the data on the SD card to be readable by any device. 
I want to build this project without relying on any external libraries, effectivley I want to build this from scratch. I will try to make a conscious effort to name and link every resource that helped me along the way. 

## Why I'm doing this from scratch
I want to build this from scratch so that I learn how a Cortex-M series CPU works and what is going on behind the scenes before the main() function is called. Furthermore, I want to learn how SD cards store data and how UART works on a deeper level. In conclusion, I am doing this project to understand what the CubeIDE and the HAL functions are doing behind the scenes.


## Description of the different Programms
### The Linker Script and the Reset Handler
The [linker script](linker/stm32flinker.ld) serves as a map so that during compilation the linker puts the code into the correct places. Per the STM32F446RE Reference Manual, the Flash starts at address 0x08000000 and has a length of 512kB and the RAM starts at address 0x20000000 and has a length of 128kB. Meaning, the Flash and RAM inside the MEMORY part of the linker script are as follows:
```
rom (rx) : ORIGIN = 0x08000000, LENGTH = 512k 
ram (rwx): ORIGIN = 0x20000000, LENGTH = 128k
```
Now we can start describing how and where code will be put inside those memory regions using the SECTIONS part. The three common sections are .text, .data and .bss they hold the program code, the initialized and the uninitialized variabels respectivley. Furthermore, inside each of those sections, variables have been defined to show the start and the end of each section so that we can later initialize the C runtime environment. The first section named .vectors is the section that will hold the vector table (pointers to different interrupts and handlers). Again, reading from the Reference Manual the first two addresses (meaning 0x08000000 and 0x08000004) hold the Stack Pointer and the Program Counter respectively. Since the stack pointer grows downwards, we define the _estack variable to be at the end of RAM. Each section is aligned by 4 addresses since the STM32 is a 32 bit microcontroller.

Next, the vector table has to be defined, that is done inside the [startup](startup/startup.c) file. I have written that file in C, eventough typically that is done in assembly, the reason for that is that C makes it more readable, a considerations is that the __attrubute keyword will be needed for the compiler to asign the vector table to the correct place. Looking at that file the type called isr_t is just a function pointer that takes no input. After that ,using the __attribute keyword, the compiler is told that the following array should be in the .vectors section, after that we just need to define an array of type isr_t where the addresses of the different interrupts and reset handlers are stored in the order given again by the Reference Manual (meaning the first is the Stack Pointer, the second is the Reset Handler etc.).

Now we can define the Handlers, starting with the reset_handler. The reset_handler has the simple task of starting the C runtime environment and call main(), to start the C runtime environment we need to first copy the initialized variables to ram and secondly set the uninitialized variables to zero, then we can safely call main(). In a embedded device the main function should never be exited but just as a precaution if that ever should happen the reset_handler will just get stuck in a infinit loop.

The microcontroller also requires that we define the Hard Fault Handler (which will be called in case of any system error) and the Non-Maskable Interrupt, for now in my case they simply do nothing.


The STM32F446RE Reference Manual and the following video served as my main resources for this part:
https://youtu.be/MhOba73z-dQ?si=8CAdLMkpidwIjhpF

### UART Interface
The [UART](src/uart.c) interface in this project will be used to communicate between the microcontroller and the serial monitor on my PC. The baud rate has been chosen to be 9600 because, as stated in the Referance Manual, at this speed and oversampling by 16 the error rate is 0%. UART2 outputs through port A and is directly conected to the ST-Link portion of the Nucleo board making it ideal for the Microcontoller to PC bridge.

The reciver works via the RX interrupt. During the RX interrupt ISR the content the RX register are copied to a buffer that is shared with the main program. Since this interface will be used as a sort of shell the CR (Carriage Return) and LF (Line Feed) characters will set a software flag that alerts the main program, further char checks and flags will be added as needed. The use of the RX interrupt rather than the DMA or direct polling was chosen becaus human input is too slow, therefore any other methode would in this case just do nothing for most of the time.

The transmitter works by sending an entire sting of text at a time. Currently no TX interrupt is used, however, as the project comes along the use of this interrupt may become necessary.
