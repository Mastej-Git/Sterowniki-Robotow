/*
 * circle.h
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_

#include "ILI9341_STM32_Driver.h"

struct Circle {
	int x;
	int y;
	int radius;
	int color;
};

void draw_circle(struct Circle circle);

#endif /* SRC_CIRCLE_H_ */
