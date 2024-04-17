/*
 * field.h
 *
 *  Created on: 10 kwi 2024
 *      Author: mmast
 */

#ifndef INC_FIELD_H_
#define INC_FIELD_H_

#include "rect.h"

struct Field {
	struct Rect border;
	struct Rect fill;
};

void draw_field(struct Field field);
void change_position(struct Field *field, int rand_x, int rand_y);

#endif /* INC_FIELD_H_ */
