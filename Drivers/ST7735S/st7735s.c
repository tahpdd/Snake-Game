#include "clock.h"
#include "gpio.h"
#include "spi.h"
#include "st7735s.h"

#define LCD_CS_PIN  12U
#define LCD_RST_PIN 11U
#define LCD_DC_PIN  14U
#define LCD_X_OFFSET 1U
#define LCD_Y_OFFSET 2U

static void st7735s_write_command(uint8_t command)
{
    gpio_clear_pin(GPIO_PORT_B, LCD_DC_PIN);
    spi2_send_byte(command);
}

static void st7735s_write_command_data(uint8_t command, const uint8_t *data, uint8_t size)
{
    gpio_clear_pin(GPIO_PORT_B, LCD_DC_PIN);
    spi2_send_byte(command);
    gpio_set_pin(GPIO_PORT_B, LCD_DC_PIN);

    for (uint8_t i = 0U; i < size; ++i) {
        spi2_send_byte(data[i]);
    }

}

static void st7735s_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t column_data[4] = {
        (uint8_t)((x0 + LCD_X_OFFSET) >> 8),
        (uint8_t)(x0 + LCD_X_OFFSET),
        (uint8_t)((x1 + LCD_X_OFFSET) >> 8),
        (uint8_t)(x1 + LCD_X_OFFSET)
    };
    uint8_t row_data[4] = {
        (uint8_t)((y0 + LCD_Y_OFFSET) >> 8),
        (uint8_t)(y0 + LCD_Y_OFFSET),
        (uint8_t)((y1 + LCD_Y_OFFSET) >> 8),
        (uint8_t)(y1 + LCD_Y_OFFSET)
    };

    st7735s_write_command_data(0x2AU, column_data, 4U);
    st7735s_write_command_data(0x2BU, row_data, 4U);
}

static void st7735s_write_color(uint16_t color)
{
    spi2_send_byte((uint8_t)(color >> 8));
    spi2_send_byte((uint8_t)color);
}

static void st7735s_start_pixels(void)
{
    gpio_clear_pin(GPIO_PORT_B, LCD_DC_PIN);
    spi2_send_byte(0x2CU);
    gpio_set_pin(GPIO_PORT_B, LCD_DC_PIN);
}

void st7735s_init(void)
{
    uint8_t orientation = 0xA8U;
    uint8_t color_mode = 0x05U;

    gpio_init_output(GPIO_PORT_B, LCD_CS_PIN);
    gpio_init_output(GPIO_PORT_B, LCD_RST_PIN);
    gpio_init_output(GPIO_PORT_B, LCD_DC_PIN);
    gpio_set_pin(GPIO_PORT_B, LCD_CS_PIN);

    gpio_clear_pin(GPIO_PORT_B, LCD_RST_PIN);
    clock_delay_ms(20U);
    gpio_set_pin(GPIO_PORT_B, LCD_RST_PIN);
    clock_delay_ms(150U);

    gpio_clear_pin(GPIO_PORT_B, LCD_CS_PIN);
    st7735s_write_command(0x01U);
    clock_delay_ms(150U);
    st7735s_write_command(0x11U);
    clock_delay_ms(200U);
    st7735s_write_command_data(0x36U, &orientation, 1U);
    st7735s_write_command_data(0x3AU, &color_mode, 1U);
    st7735s_write_command(0x29U);
    clock_delay_ms(100U);
    gpio_set_pin(GPIO_PORT_B, LCD_CS_PIN);
}

void st7735s_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= ST7735S_WIDTH || y >= ST7735S_HEIGHT) {
        return;
    }

    gpio_clear_pin(GPIO_PORT_B, LCD_CS_PIN);
    st7735s_set_window(x, y, x, y);
    st7735s_start_pixels();
    st7735s_write_color(color);
    gpio_set_pin(GPIO_PORT_B, LCD_CS_PIN);
}

void st7735s_fill_screen(uint16_t color)
{
    gpio_clear_pin(GPIO_PORT_B, LCD_CS_PIN);
    st7735s_set_window(0U, 0U, ST7735S_WIDTH - 1U, ST7735S_HEIGHT - 1U);
    st7735s_start_pixels();

    for (uint32_t i = 0U; i < ST7735S_WIDTH * ST7735S_HEIGHT; ++i) {
        st7735s_write_color(color);
    }

    gpio_set_pin(GPIO_PORT_B, LCD_CS_PIN);
}
