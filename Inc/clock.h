#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

void clock_init_max(void);
void clock_init_timer(void);
void clock_delay_ms(uint32_t milliseconds);

#endif
