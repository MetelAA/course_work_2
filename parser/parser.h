#ifndef CW2_PARSER_H
#define CW2_PARSER_H

#include "../base_structs.h"
#include "validator/canvas_entity_validator.h"

enum FuncType get_func_type(int argc, char **argv);
bool get_mirror_args(int argc, char **argv, MirrorSpec *spec);
bool get_copy_args(int argc, char **argv, CopySpec* spec);
bool get_color_replacement_args(int argc, char **argv, ColorReplaceSpec* spec);
bool get_border_split_args(int argc, char **argv, BorderSplitSpec* spec);
bool get_input_file_name_and_has_iFlag(int argc, char **argv, char* file_name);
bool get_output_file_name_and_has_it(int argc, char** argv, char* file_name);

#endif