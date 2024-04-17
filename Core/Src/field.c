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

void change_position(struct Field *field, int rand_x, int rand_y) {
	field->border.x = rand_x;
	field->border.y = rand_y;
	field->fill.x = rand_x + 3;
	field->fill.y = rand_y + 3;
}
