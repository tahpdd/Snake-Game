#include "clock.h"
#include "spi.h"
#include "st7735s.h"
#include "uart.h"
#include "snake.h"

#define SNAKE_STEP_MS 150U

int main(void)
{
    uint16_t elapsed = 0U;

    clock_init_max();
    clock_init_timer();
    spi2_init();
    st7735s_init();
    snake_init();
    uart2_init();

    while (1) {
        if (uart2_available()) {
            snake_input(uart2_receive_byte());
        }

        clock_delay_ms(1U);
        elapsed++;

        if (elapsed >= SNAKE_STEP_MS) {
            snake_update();
            elapsed = 0U;
        }
    }
}
