/*
 * snake.c
 *
 *  Created on: Apr 6, 2024
 *      Author: phat
 */
#include <snake.h>

/*
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) | A0 == UP
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) | A1 == DOWN
    HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) | B1 == LEFT
    HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) | A2 == RIGHT
    
    PULL DOWN PUSH BUTTON
*/
const uint8_t fx[23] = { 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73 };
const uint8_t fy[18] = { 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 52, 55 };

void NewFruit(struct snake *s, int snakeLen, uint8_t *fox, uint8_t *foy) {
    srand(HAL_GetTick() + HAL_GetTick());
    uint8_t fnx = rand() % 22;
    uint8_t fny = rand() % 17;
    uint8_t valid = 1;

    while ( 1 ) {
        int i = 0;
    	for (i = 0; i < snakeLen; i++) {
    		if (fx[fnx] == s[i].x && fy[fny] == s[i].y) {
    			valid = 0;
    		    fnx = rand() % 17;
    		    fny = rand() % 17;
    			break;
    		}
    	}
    	if (i == snakeLen) break;
    	if (valid == 1) {
    		break;
    	}
    }
    *fox = fx[fnx];
    *foy = fy[fny];
    //SSD1306_DrawFilledRectangle(*fox, *foy, 2, 2, 1);
    SSD1306_DrawRectangle(*fox, *foy, 2, 2, 1);
}

