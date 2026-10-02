#ifndef UART
#define UART

#define BUFFER_SIZE	512

typedef struct {
	char buffer[BUFFER_SIZE];
	short position;
	unsigned short FULL : 1;

} uart_buffer;

extern uart_buffer rx_buffer;
extern uart_buffer tx_buffer;

typedef struct {
	
	unsigned int NUL : 1;
	unsigned int SOH : 1;
	unsigned int STX : 1;
	unsigned int ETX : 1;
	unsigned int EOT : 1;
	unsigned int ENQ : 1;
	unsigned int ACK : 1;
	unsigned int BEL : 1;
	unsigned int BS : 1;
	unsigned int HT : 1;
	unsigned int LF : 1;
	unsigned int VT : 1;
	unsigned int FF : 1;
	unsigned int CR : 1;
	unsigned int SO : 1;
	unsigned int SI : 1;
	unsigned int DLE : 1;
	unsigned int DC1 : 1;
	unsigned int DC2 : 1;
	unsigned int DC3 : 1;
	unsigned int DC4 : 1;
	unsigned int NAK : 1;
	unsigned int SYN : 1;
    unsigned int ETB : 1;
    unsigned int CAN : 1;
    unsigned int EM : 1;
    unsigned int SUB : 1;
    unsigned int ESC : 1;
    unsigned int FS : 1;
    unsigned int GS : 1;
    unsigned int RS : 1;
    unsigned int US : 1;

} ascii_ctrl;

extern ascii_ctrl ASCII_CTRL;

void uart2_init(void);
void uart2_send(void);

#endif
