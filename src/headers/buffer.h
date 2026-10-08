#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE	(unsigned short)512

typedef struct {
	char buffer[BUFFER_SIZE];
	short position;
	unsigned short FULL : 1;

} buffer;

extern buffer rx_buffer;
extern buffer tx_buffer;
extern buffer empty_buffer;
extern buffer spi_rx_buffer;

#endif