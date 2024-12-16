/*
 * font.h
 *
 *  Created on: May 6, 2024
 *      Author: phat
 */

#ifndef INC_FONT_H_
#define INC_FONT_H_

#include "stdint.h"
#include "ssd1306.h"


void outputNum(uint8_t a[5][3], uint8_t posX, uint8_t posY);
void outputResult(int a, int b, uint8_t posX, uint8_t posY);

#endif /* INC_FONT_H_ */
