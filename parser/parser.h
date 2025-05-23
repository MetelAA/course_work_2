#ifndef CW2_PARSER_H
#define CW2_PARSER_H

#include "../base_structs.h"
#include "validator/canvas_entity_validator.h"

Error get_outimage_border_args(int argc, char **argv, OutimageBorderSpec *spec);
Error get_white_area_border_argsError(int argc, char **argv, WhiteAreaBorder *spec);

Error get_func_type(int argc, char **argv, enum FuncType* fType);
Error get_mirror_args(int argc, char **argv, MirrorSpec *spec);
Error get_copy_args(int argc, char **argv, CopySpec* spec);
Error get_color_replacement_args(int argc, char **argv, ColorReplaceSpec* spec);
Error get_border_split_args(int argc, char **argv, BorderSplitSpec* spec);
bool get_input_file_name_and_has_iFlag(int argc, char **argv, char* file_name);
bool get_output_file_name_and_has_it(int argc, char** argv, char* file_name);

static struct option long_opt[] = {
        {"outimage_border",         no_argument, NULL, 'z'},
        {"white_area_border",         no_argument, NULL, 'w'},

        {"mirror",       no_argument, NULL, 'm'},
        {"copy",         no_argument, NULL, 'p'},
        {"color_replace", no_argument, NULL, 'e'},
        {"split",        no_argument, NULL, 's'},
        {"info",         no_argument, NULL, 'f'},
        {"help",         no_argument, NULL, 'h'},
        {"axis",         required_argument, NULL, 'a'},
        {"left_up",      required_argument, NULL, 'l'},
        {"right_down",   required_argument, NULL, 'r'},
        {"dest_left_up", required_argument, NULL, 'd'},
        {"old_color",         required_argument, NULL, '_'},
        {"new_color",      required_argument, NULL, 'n'},
        {"number_x",         required_argument, NULL, 'x'},
        {"number_y",      required_argument, NULL, 'y'},
        {"thickness",   required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {0,0,0,0}
};

#endif