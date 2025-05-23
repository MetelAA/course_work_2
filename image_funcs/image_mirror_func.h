#ifndef CW2_IMAGE_MIRROR_FUNC_H
#define CW2_IMAGE_MIRROR_FUNC_H
#include "../base_structs.h"
#include "file_actions.h"

Error mirror_area(char* input_file_name, char* output_file_name, MirrorSpec *mirror_spec);

#endif
