#ifndef UART
#define UART

#define BUFFER_SIZE	255

extern volatile char uart2_buffer[BUFFER_SIZE];
extern volatile int flag;

void uart2_init(void);
void uart2_send(volatile char *);
// void uart2_recieve(char *);

#endif
