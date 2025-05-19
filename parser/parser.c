#include "parser.h"
#include "../base_structs.h"
#include "validator/canvas_entity_validator.h"

enum FuncType func_status_is_empty(const enum FuncType *fType, enum FuncType setV);


enum FuncType get_func_type(int argc, char **argv) {

    if (argc == 1) {
        return infoFunc;
    }

    static struct option long_opt[] = {
            {"mirror",       no_argument, NULL, 'm'},
            {"copy",         no_argument, NULL, 'c'},
            {"colorReplace", no_argument, NULL, 'r'},
            {"split",        no_argument, NULL, 's'},
            {"info",         no_argument, NULL, 'i'},
            {"help",         no_argument, NULL, 'h'},
            {0,              0, 0,              0}
    };

    int opt;
    enum FuncType fType = emptyFunc;
    while ((opt = getopt_long(argc, argv, "h", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'm':
                fType = func_status_is_empty(&fType, mirrorFunc);
                break;
            case 'c':
                fType = func_status_is_empty(&fType, copyFunc);
                break;
            case 'r':
                fType = func_status_is_empty(&fType, colorReplaceFunc);
                break;
            case 's':
                fType = func_status_is_empty(&fType, splitFunc);
                break;
            case 'i':
                fType = func_status_is_empty(&fType, infoFunc);
                break;
            case 'h':
                fType = func_status_is_empty(&fType, helpFunc);
                break;
            case '?':
                continue;
            default:
                return errorFunc;
        }
    }
    return fType;
}

enum FuncType func_status_is_empty(const enum FuncType *fType, enum FuncType setV) {
    if ((*fType) != emptyFunc)
        return extraFunc;
    return setV;
}

bool get_mirror_args(int argc, char **argv, MirrorSpec *spec) {
    static struct option long_opt[] = {
            {"axis",         required_argument, NULL, 'a'},
            {"left_up",      required_argument, NULL, 'l'},
            {"right_down",   required_argument, NULL, 'r'},
            {0,0,0,0}
    };


    int opt;
    while((opt = getopt_long(argc, argv, "a:l:r:", long_opt, NULL)) != -1){
        switch(opt){
            case 'a':
                if(!check_axis(optarg))
                    return false;
                spec->axis = optarg[0];
            break;
            case 'l': {
                Point *point = malloc(sizeof(Point));
                if(!get_canvas_point_from_string(optarg, point))
                    return false;
                spec->start_area = point;
            }
            break;
            case 'r': {
                Point *point = malloc(sizeof(Point));
                if(!get_canvas_point_from_string(optarg, point))
                    return false;
                spec->end_area = point;
            }
            break;
            case '?':
                continue;
        }
    }
    return true;
}

bool get_copy_args(int argc, char **argv, CopySpec* spec) {
    static struct option long_opt[] = {
            {"left_up",      required_argument, NULL, 'l'},
            {"right_down",   required_argument, NULL, 'r'},
            {"dest_left_up", required_argument, NULL, 'd'},
            {0,0,0,0}
    };
    int opt;
    while((opt = getopt_long(argc, argv, "l:r:d:", long_opt, NULL)) != -1){
        switch(opt){
            case 'l': {
                Point *point = malloc(sizeof(Point));
                if(!get_canvas_point_from_string(optarg, point))
                    return false;
                spec->start_inp_area = point;
            }
                break;
            case 'r': {
                Point *point = malloc(sizeof(Point));
                if(!get_canvas_point_from_string(optarg, point))
                    return false;
                spec->end_inp_area = point;
            }
                break;
            case 'd':{
                Point *point = malloc(sizeof(Point));
                if(!get_canvas_point_from_string(optarg, point))
                    return false;
                spec->dest_point = point;
            }
            break;
            case '?':
                continue;
        }
    }
    return true;
}


bool get_color_replacement_args(int argc, char **argv, ColorReplaceSpec* spec) {
    static struct option long_opt[] = {
            {"old_color",         required_argument, NULL, 'o'},
            {"new_color",      required_argument, NULL, 'n'},
            {0,0,0,0}
    };
    int opt;
    while((opt = getopt_long(argc, argv, "o:n:", long_opt, NULL)) != -1){
        switch(opt){
            case 'o': {
                Rgb* color = malloc(sizeof(Rgb));
                if(!get_color_from_string(optarg, color))
                    return false;
                spec->old_color = color;
            }
                break;
            case 'n':{
                Rgb* color = malloc(sizeof(Rgb));
                if(!get_color_from_string(optarg, color))
                    return false;
                spec->new_color = color;
            }
                break;
            case '?':
                continue;
        }
    }
    return true;
}

bool get_border_split_args(int argc, char **argv, BorderSplitSpec* spec) {
    static struct option long_opt[] = {
            {"number_x",         required_argument, NULL, 'x'},
            {"number_y",      required_argument, NULL, 'y'},
            {"thickness",   required_argument, NULL, 't'},
            {"color", required_argument, NULL, 'c'},
            {0,0,0,0}
    };
    int opt;
    while((opt = getopt_long(argc, argv, "l:r:d:", long_opt, NULL)) != -1){
        switch(opt){
            case 'x':{
                int a;
                if(!get_split_counts(optarg, &a))
                    return false;
                spec->x_frags = a;
            }
                break;
            case 'y': {
                int a;
                if(!get_split_counts(optarg, &a))
                    return false;
                spec->y_frags = a;
            }
                break;
            case 't':{
                int a;
                if(!get_thickness(optarg, &a))
                    return false;
                spec->thickness = a;
            }
                break;
            case 'c':{
                Rgb* color = malloc(sizeof(Rgb));
                if(!get_color_from_string(optarg, color))
                    return false;
                spec->color = color;
            }
                break;
            case '?':
                continue;
        }
    }
    return true;
}

bool get_input_file_name_and_has_iFlag(int argc, char **argv, char *file_name) {
    static struct option long_opt[] = {
            {"input", required_argument, NULL, 'i'},
            {0,       0, 0,                    0}
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "i:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'i':
                strcpy(file_name, optarg);
                return true;
            case '?':
                continue;
        }
    }
    strcpy(file_name, argv[argc - 1]);
    return false;
}

bool get_output_file_name_and_has_it(int argc, char **argv, char *file_name) {
    static struct option long_opt[] = {
            {"output", required_argument, NULL, 'o'},
            {0,        0, 0,                    0}
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "o:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'o':
                strcpy(file_name, optarg);
                return true;
            case '?':
                continue;
        }
    }
    return false;
}