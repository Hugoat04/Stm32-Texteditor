#ifndef UART
#define UART

#define BUFFER_SIZE	(unsigned short)512

typedef struct {
	char buffer[BUFFER_SIZE];
	short position;
	unsigned short FULL : 1;

} uart_buffer;

extern uart_buffer rx_buffer;
extern uart_buffer tx_buffer;
extern uart_buffer empty_buffer;

typedef struct {

	volatile unsigned int SR;
	volatile unsigned int DR;
	volatile unsigned int BRR;
	volatile unsigned int CR1;
	volatile unsigned int CR2;
	volatile unsigned int CR3;
	volatile unsigned int GTPR;

} uart_regs;

extern uart_regs *UART2;

void uart2_init(void);
void uart2_send(void);

#endif
