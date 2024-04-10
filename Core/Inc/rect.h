/*
 * rect.h
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#ifndef INC_RECT_H_
#define INC_RECT_H_

#include "ILI9341_STM32_Driver.h"

struct Rect {
	int x;
	int y;
	int width;
	int height;
	int color;
};

void draw_rect(struct Rect rect);

#endif /* INC_RECT_H_ */
