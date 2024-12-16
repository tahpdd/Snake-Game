/*
 * snake.h
 *
 *  Created on: Apr 6, 2024
 *      Author: phat
 */

/*
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) | A0 == UP
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) | A1 == DOWN
    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) | B1 == LEFT
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) | A2 == RIGHT

    PULL DOWN PUSH BUTTON
*/

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include <stdint.h>
#include <time.h>
#include "ssd1306.h"


struct snake {
    uint8_t x;
    uint8_t y;
};

void NewFruit(struct snake *s, int snakeLen, uint8_t *fox, uint8_t *foy);


#endif /* INC_SNAKE_H_ */
