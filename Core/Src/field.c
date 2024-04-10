/*
 * field.c
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#include "field.h"

void draw_field(struct Field field) {
	ILI9341_Draw_Rectangle(field.border.x, field.border.y, field.border.width, field.border.height, field.border.color);
	ILI9341_Draw_Rectangle(field.fill.x, field.fill.y, field.fill.width, field.fill.height, field.fill.color);
}
