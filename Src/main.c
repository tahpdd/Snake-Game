#include "clock.h"
#include "spi.h"
#include "st7735s.h"

int main(void)
{
    clock_init_max();
    clock_init_timer();
    spi2_init();
    st7735s_init();
    st7735s_fill_screen(ST7735S_BLUE);

    while (1) {

    }
}
