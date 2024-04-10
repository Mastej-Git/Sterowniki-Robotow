/*
 * circle.c
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#include "circle.h"

void draw_circle(struct Circle circle) {
	ILI9341_Draw_Horizontal_Line(circle.x + 11, circle.y, 8, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 8, circle.y + 1, 14, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 7, circle.y + 2, 16, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 5, circle.y + 3, 20, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 4, circle.y + 4, 22, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 3, circle.y + 5, 24, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 3, circle.y + 6, 24, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 2, circle.y + 7, 26, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 8, 28, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 9, 28, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 10, 28, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 11, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 12, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 13, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 14, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 15, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 16, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 17, 30, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x, circle.y + 18, 30, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 19, 28, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 20, 28, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 1, circle.y + 21, 28, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 2, circle.y + 22, 26, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 3, circle.y + 23, 24, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 3, circle.y + 24, 24, circle.color);

	ILI9341_Draw_Horizontal_Line(circle.x + 4, circle.y + 25, 22, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 5, circle.y + 26, 20, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 7, circle.y + 27, 16, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 8, circle.y + 28, 14, circle.color);
	ILI9341_Draw_Horizontal_Line(circle.x + 11, circle.y + 29, 8, circle.color);
}
