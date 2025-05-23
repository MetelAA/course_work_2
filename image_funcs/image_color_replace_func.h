#ifndef CW2_IMAGE_COLOR_REPLACE_FUNC_H
#define CW2_IMAGE_COLOR_REPLACE_FUNC_H
#include "../base_structs.h"
#include "file_actions.h"

Error replace_color(char* input_file_name, char* output_file_name, ColorReplaceSpec *replace_spec);

#endif
