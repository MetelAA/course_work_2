#ifndef CW2_CANVAS_ENTITY_VALIDATOR_H
#define CW2_CANVAS_ENTITY_VALIDATOR_H
#include "../../base_structs.h"
#include "base_validator.h"

bool get_canvas_point_from_string(char* s, Point * point);
bool check_axis(char *s);
bool get_color_from_string(char *s, Rgb* color);
bool get_split_counts(char *s, int *rez);
bool get_thickness(char *s, int *rez);

#endif
