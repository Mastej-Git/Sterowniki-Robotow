/*
 * rect.c
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#include "rect.h"

void draw_rect(struct Rect rect) {
	ILI9341_Draw_Rectangle(rect.x, rect.y, rect.width, rect.height, rect.color);
}
