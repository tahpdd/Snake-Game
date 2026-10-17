#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
    GPIO_PORT_I
} GPIO_Port;

void gpio_init_output(GPIO_Port port, uint8_t pin);
void gpio_init_af(GPIO_Port port, uint8_t pin, uint8_t alternate_function);
void gpio_set_pin(GPIO_Port port, uint8_t pin);
void gpio_clear_pin(GPIO_Port port, uint8_t pin);
void gpio_toggle_pin(GPIO_Port port, uint8_t pin);

#endif
