#include "snake.h"
#include "st7735s.h"

#define CELL_SIZE 10U
#define COLS (ST7735S_WIDTH / CELL_SIZE)
#define ROWS (ST7735S_HEIGHT / CELL_SIZE)
#define MAX_LENGTH (COLS * ROWS)

static uint8_t snake_x[MAX_LENGTH];
static uint8_t snake_y[MAX_LENGTH];
static uint16_t length;
static uint8_t food_x, food_y;
static uint32_t food_seed = 1U;
static int8_t dx, dy;
static int8_t next_dx, next_dy;

static void snake_draw_cell(uint8_t x, uint8_t y, uint16_t color)
{
    for (uint8_t row = 0U; row < CELL_SIZE; row++) {
        for (uint8_t col = 0U; col < CELL_SIZE; col++) {
            st7735s_draw_pixel(x * CELL_SIZE + col, y * CELL_SIZE + row, color);
        }
    }
}

static void snake_place_food(void)
{
    uint16_t i;

    do {
        food_seed = food_seed * 1664525U + 1013904223U;
        food_x = food_seed % COLS;
        food_y = (food_seed / COLS) % ROWS;

        for (i = 0U; i < length; i++) {
            if (snake_x[i] == food_x && snake_y[i] == food_y) {
                break;
            }
        }
    } while (i < length);

    snake_draw_cell(food_x, food_y, ST7735S_RED);
}

void snake_init(void)
{
    length = 3U;
    dx = next_dx = 1;
    dy = next_dy = 0;
    st7735s_fill_screen(ST7735S_BLACK);

    for (uint16_t i = 0U; i < length; i++) {
        snake_x[i] = COLS / 2U - i;
        snake_y[i] = ROWS / 2U;
        snake_draw_cell(snake_x[i], snake_y[i], ST7735S_WHITE);
    }

    snake_place_food();
}

void snake_input(uint8_t key)
{
    if ((key == 'w' || key == 'W') && dy != 1) {
        next_dx = 0;
        next_dy = -1;
    } else if ((key == 's' || key == 'S') && dy != -1) {
        next_dx = 0;
        next_dy = 1;
    } else if ((key == 'a' || key == 'A') && dx != 1) {
        next_dx = -1;
        next_dy = 0;
    } else if ((key == 'd' || key == 'D') && dx != -1) {
        next_dx = 1;
        next_dy = 0;
    }
}

void snake_update(void)
{
    int x = snake_x[0] + next_dx;
    int y = snake_y[0] + next_dy;

    if (x < 0 || x >= (int)COLS || y < 0 || y >= (int)ROWS) {
        snake_init();
        return;
    }

    for (uint16_t i = 0U; i < length - 1U; i++) {
        if (snake_x[i] == x && snake_y[i] == y) {
            snake_init();
            return;
        }
    }

    uint8_t eat = x == food_x && y == food_y;

    if (eat) {
        length++;
    } else {
        snake_draw_cell(snake_x[length - 1U], snake_y[length - 1U], ST7735S_BLACK);
    }

    for (uint16_t i = length - 1U; i > 0U; i--) {
        snake_x[i] = snake_x[i - 1U];
        snake_y[i] = snake_y[i - 1U];
    }

    snake_x[0] = x;
    snake_y[0] = y;
    dx = next_dx;
    dy = next_dy;
    snake_draw_cell(x, y, ST7735S_WHITE);

    if (eat) {
        if (length == MAX_LENGTH) {
            snake_init();
            return;
        }

        snake_place_food();
    }
}
