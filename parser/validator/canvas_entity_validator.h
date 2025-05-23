#ifndef CW2_CANVAS_ENTITY_VALIDATOR_H
#define CW2_CANVAS_ENTITY_VALIDATOR_H
#include "../../base_structs.h"
#include "base_validator.h"

Error get_canvas_point_from_string(char* s, Point * point);
Error check_axis(char *s);
Error get_color_from_string(char *s, Rgb* color);
Error get_split_counts(char *s, int *rez);
Error get_thickness(char *s, int *rez);

#endif
