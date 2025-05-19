#ifndef CW2_PARSER_H
#define CW2_PARSER_H

#include "../base_structs.h"

enum FuncType get_func_type(int argc, char **argv);
bool get_mirror_args(int argc, char **argv, MirrorSpec *spec);
bool get_copy_args(int argc, char **argv, CopySpec* spec);
bool get_color_replacement_args(int argc, char **argv, ColorReplaceSpec* spec);
bool get_border_split_args(int argc, char **argv, BorderSplitSpec* spec);
bool get_input_file_name_and_has_iFlag(int argc, char **argv, char* file_name);
bool get_output_file_name_and_has_it(int argc, char** argv, char* file_name);

static struct option long_opt_for_parse_args[] = {
        {"mirror", no_argument, NULL, 's'},
        {"copy", no_argument, NULL, 's'},
        {"colorReplace", no_argument, NULL, 's'},
        {"split", no_argument, NULL, 's'},
        {"info", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 's'},
        {"axis", required_argument, NULL, 'a'},
        {"left_up", required_argument, NULL, 'l'},
        {"right_down", required_argument, NULL, 'r'},
        {"dest_left_up", required_argument, NULL, 'd'},
        {"color_replace", required_argument, NULL, 'r'},
        {"old_color", required_argument, NULL, 'o'},
        {"number_x", required_argument, NULL, 'x'},
        {"number_y", required_argument, NULL, 'y'},
        {"thickness", required_argument, NULL, 't'},
        {"color", required_argument, NULL, 'c'},
};

#endif