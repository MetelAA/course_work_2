#ifndef CW2_IMAGE_COPY_FUNC_H
#define CW2_IMAGE_COPY_FUNC_H
#include "../base_structs.h"
#include "file_actions.h"

Error copy_area(char* input_file_name, char* output_file_name, CopySpec *copy_spec);

#endif
