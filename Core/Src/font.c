/*
 * font.c
 *
 *  Created on: May 6, 2024
 *      Author: phat
 */

#include "font.h"
uint8_t zero [5][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};

uint8_t one [5][3] = {
	{ 0, 1, 0 },
	{ 1, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 1, 1, 1 }
};

uint8_t two [5][3] = {
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 1, 1 }
};

uint8_t four [5][3] = {
	{ 1, 0, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 0, 0, 1 }
};
uint8_t three [5][3] = {
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 1, 1, 1 }
};
uint8_t five [5][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 1, 1, 1 }
};
uint8_t six [5][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 0 },
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};
uint8_t seven [5][3] = {
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 0, 0, 1 },
	{ 0, 0, 1 },
	{ 0, 0, 1 }
};
uint8_t eight [5][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 }
};
uint8_t nine [5][3] = {
	{ 1, 1, 1 },
	{ 1, 0, 1 },
	{ 1, 1, 1 },
	{ 0, 0, 1 },
	{ 1, 1, 1 }
};

void outputNum(uint8_t a[5][3], uint8_t posX, uint8_t posY) {
	uint8_t maxX = posX + 6;
	uint8_t maxY = posY + 12;
	uint8_t x = 0, y = 0;
	for (int i = posY; i <= maxY; i += 3) {

		for (int j = posX; j <= maxX; j += 3) {
			SSD1306_DrawRectangle(j, i, 2, 2, a[y][x]);
			x++;
		}
	}



}
void outputResult(int a, int b, uint8_t posX, uint8_t posY) {
	switch (a) {
	case 1:
		outputNum(one, posX, posY);
		break;
	case 0:
		outputNum(zero, posX, posY);
		break;
	case 2:
		outputNum(two, posX, posY);
		break;
	case 3:
		outputNum(three, posX, posY);
		break;
	case 4:
		outputNum(four, posX, posY);
		break;
	case 5:
		outputNum(five, posX, posY);
		break;
	case 6:
		outputNum(six, posX, posY);
		break;
	case 7:
		outputNum(seven, posX, posY);
		break;
	case 8:
		outputNum(eight, posX, posY);
		break;
	case 9:
		outputNum(nine, posX, posY);
		break;
	}
	posX += 12;
	switch (b) {
	case 1:
		outputNum(one, posX, posY);
		break;
	case 0:
		outputNum(zero, posX, posY);
		break;
	case 2:
		outputNum(two, posX, posY);
		break;
	case 3:
		outputNum(three, posX, posY);
		break;
	case 4:
		outputNum(four, posX, posY);
		break;
	case 5:
		outputNum(five, posX, posY);
		break;
	case 6:
		outputNum(six, posX, posY);
		break;
	case 7:
		outputNum(seven, posX, posY);
		break;
	case 8:
		outputNum(eight, posX, posY);
		break;
	case 9:
		outputNum(nine, posX, posY);
		break;
	}
}

