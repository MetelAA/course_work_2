#ifndef CW2_IMAGE_SPLIT_FUNC_H
#define CW2_IMAGE_SPLIT_FUNC_H
#include "../base_structs.h"
#include "file_actions.h"

Error split_image(char* input_file_name, char* output_file_name, BorderSplitSpec *split_spec);

#endif
