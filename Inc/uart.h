#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart2_init(void);
uint8_t uart2_available(void);
uint8_t uart2_receive_byte(void);

#endif
