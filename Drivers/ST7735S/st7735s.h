#ifndef ST7735S_H
#define ST7735S_H

#include <stdint.h>

#define ST7735S_WIDTH  160U
#define ST7735S_HEIGHT 128U
#define ST7735S_RED    0x001FU
#define ST7735S_BLUE   0xF800U

void st7735s_init(void);
void st7735s_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void st7735s_fill_screen(uint16_t color);

#endif
