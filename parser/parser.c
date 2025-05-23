#include "parser.h"

enum FuncType func_status_is_empty(const enum FuncType *fType, enum FuncType setV);


Error get_func_type(int argc, char **argv, enum FuncType *fType) {
    (*fType) = emptyFunc;
    if (argc == 1) {
        (*fType) = helpFunc;
        return (Error) {false, ""};
    }

    int opt;
    optind = 1;
    opterr = 0;

    while ((opt = getopt_long(argc, argv, "h", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'w':
                (*fType) = func_status_is_empty(fType, whiteAreaBorderFunc);
                break;
            case 'z':
                (*fType) = func_status_is_empty(fType, outimageBorderFunc);
                break;


            case 'm':
                (*fType) = func_status_is_empty(fType, mirrorFunc);
                break;
            case 'p':
                (*fType) = func_status_is_empty(fType, copyFunc);
                break;
            case 'e':
                (*fType) = func_status_is_empty(fType, colorReplaceFunc);
                break;
            case 's':
                (*fType) = func_status_is_empty(fType, splitFunc);
                break;
            case 'f':
                (*fType) = func_status_is_empty(fType, infoFunc);
                break;
            case 'h':
                (*fType) = func_status_is_empty(fType, helpFunc);
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }
    return (Error) {false, ""};
}

enum FuncType func_status_is_empty(const enum FuncType *fType, enum FuncType setV) {
    if ((*fType) != emptyFunc)
        return extraFunc;
    return setV;
}

Error get_white_area_border_argsError(int argc, char **argv, WhiteAreaBorder *spec){
    int opt;
    optind = 1;
    int has_args[1] = {0}; //формата t, c
    while ((opt = getopt_long(argc, argv, "a:l:r:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'c': {
                Rgb* color = malloc(sizeof(Rgb));
                Error parse_error = get_color_from_string(optarg, color);
                if (parse_error.hasError)
                    return parse_error;
                spec->color = color;
                has_args[0] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }
    for (int i = 0; i < 1; ++i) {
        if(has_args[i] != 1)
            return (Error){true, "not enough arguments"};
    }

    return (Error) {false, ""};
}


Error get_outimage_border_args(int argc, char **argv, OutimageBorderSpec *spec){
    int opt;
    optind = 1;
    int has_args[2] = {0, 0}; //формата t, c
    while ((opt = getopt_long(argc, argv, "a:l:r:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 't': {
                int thickness;
                Error parse_error = get_thickness(optarg, &thickness);
                if (parse_error.hasError)
                    return parse_error;
                spec->thickness = thickness;
                has_args[0] = 1;
            }
                break;
            case 'c': {
                Rgb* color = malloc(sizeof(Rgb));
                Error parse_error = get_color_from_string(optarg, color);
                if (parse_error.hasError)
                    return parse_error;
                spec->color = color;
                has_args[1] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if(has_args[i] != 1)
            return (Error){true, "not enough arguments"};
    }


    return (Error) {false, ""};
}






Error get_mirror_args(int argc, char **argv, MirrorSpec *spec) {
    int opt;
    optind = 1;
    int has_args[3] = {0, 0, 0}; //формата a, l, r
    while ((opt = getopt_long(argc, argv, "a:l:r:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'a': {
                Error parse_error = check_axis(optarg);
                if (parse_error.hasError)
                    return parse_error;
                spec->axis = optarg[0];
                has_args[0] = 1;
            }
                break;
            case 'l': {
                Point *point = malloc(sizeof(Point));
                Error parse_error = get_canvas_point_from_string(optarg, point);
                if (parse_error.hasError)
                    return parse_error;
                spec->start_area = point;
                has_args[1] = 1;
            }
                break;
            case 'r': {
                Point *point = malloc(sizeof(Point));
                Error parse_error = get_canvas_point_from_string(optarg, point);
                if (parse_error.hasError)
                    return parse_error;
                spec->end_area = point;
                has_args[2] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if(has_args[i] != 1)
            return (Error){true, "not enough arguments"};
    }

    if(spec->start_area->x > spec->end_area->x)
        return (Error){true, "value of the x coordinate of the upper-left corner must be less than or equal to the value of the coordinates of the lower-right corner"};

    if(spec->start_area->y > spec->end_area->y)
        return (Error){true, "value of the y coordinate of the upper-left corner must be less than or equal to the value of the coordinates of the lower-right corner"};

    return (Error) {false, ""};
}

Error get_copy_args(int argc, char **argv, CopySpec *spec) {
    int opt;
    optind = 1;
    int has_args[3] = {0, 0, 0}; //формата l, r, d
    while ((opt = getopt_long(argc, argv, "l:r:d:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'l': {
                Point *point = malloc(sizeof(Point));
                Error parse_error = get_canvas_point_from_string(optarg, point);
                if (parse_error.hasError)
                    return parse_error;
                spec->start_inp_area = point;
                has_args[0] = 1;
            }
                break;
            case 'r': {
                Point *point = malloc(sizeof(Point));
                Error parse_error = get_canvas_point_from_string(optarg, point);
                if (parse_error.hasError)
                    return parse_error;
                spec->end_inp_area = point;
                has_args[1] = 1;
            }
                break;
            case 'd': {
                Point *point = malloc(sizeof(Point));
                Error parse_error = get_canvas_point_from_string(optarg, point);
                if (parse_error.hasError)
                    return parse_error;
                spec->dest_point = point;
                has_args[2] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }
    for (int i = 0; i < 3; ++i) {
        if(has_args[i] != 1)
            return (Error){true, "not enough arguments"};
    }

    if(spec->start_inp_area->x > spec->end_inp_area->x)
        return (Error){true, "value of the x coordinate of the upper-left corner must be less than or equal to the value of the coordinates of the lower-right corner"};

    if(spec->start_inp_area->y > spec->end_inp_area->y)
        return (Error){true, "value of the y coordinate of the upper-left corner must be less than or equal to the value of the coordinates of the lower-right corner"};

    return (Error) {false, ""};
}


Error get_color_replacement_args(int argc, char **argv, ColorReplaceSpec *spec) {
    int opt;
    optind = 1;
    int has_args[2] = {0, 0}; //формата _, n
    while ((opt = getopt_long(argc, argv, "_:n:", long_opt, NULL)) != -1) {
        switch (opt) {
            case '_': {
                Rgb *color = malloc(sizeof(Rgb));
                Error parse_error = get_color_from_string(optarg, color);
                if (parse_error.hasError)
                    return parse_error;
                spec->old_color = color;
                has_args[0] = 1;
            }
                break;
            case 'n': {
                Rgb *color = malloc(sizeof(Rgb));
                Error parse_error = get_color_from_string(optarg, color);
                if (parse_error.hasError)
                    return parse_error;
                spec->new_color = color;
                has_args[1] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if(has_args[i] != 1)
            return (Error) {true, "not enough arguments"};
    }
    return (Error) {false, ""};
}

Error get_border_split_args(int argc, char **argv, BorderSplitSpec *spec) {
    int opt;
    optind = 1;
    int has_args[4] = {0, 0, 0, 0}; //формата x, y, t, c
    while ((opt = getopt_long(argc, argv, "x:y:t:c:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'x': {
                int a;
                Error split_error = get_split_counts(optarg, &a);
                if (split_error.hasError)
                    return split_error;
                spec->x_frags = a;
                has_args[0] = 1;
            }
                break;
            case 'y': {
                int a;
                Error parse_error = get_split_counts(optarg, &a);
                if (parse_error.hasError)
                    return parse_error;
                spec->y_frags = a;
                has_args[1] = 1;
            }
                break;
            case 't': {
                int a;
                Error parse_error = get_thickness(optarg, &a);
                if (parse_error.hasError)
                    return parse_error;
                spec->thickness = a;
                has_args[2] = 1;
            }
                break;
            case 'c': {
                Rgb *color = malloc(sizeof(Rgb));
                Error parse_error = get_color_from_string(optarg, color);
                if (parse_error.hasError)
                    return parse_error;
                spec->color = color;
                has_args[3] = 1;
            }
                break;
            case '?':
                continue;
            default:
                continue;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (has_args[i] != 1)
            return (Error) {true, "not enough arguments"};
    }
    return (Error) {false, ""};
}

bool get_input_file_name_and_has_iFlag(int argc, char **argv, char *file_name) {
    int opt;
    optind = 1;
    while ((opt = getopt_long(argc, argv, "i:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'i':
                strcpy(file_name, optarg);
                return true;
            case '?':
                continue;
            default:
                continue;
        }
    }
    strcpy(file_name, argv[argc - 1]);
    return false;
}

bool get_output_file_name_and_has_it(int argc, char **argv, char *file_name) {
    int opt;
    optind = 1;
    while ((opt = getopt_long(argc, argv, "o:", long_opt, NULL)) != -1) {
        switch (opt) {
            case 'o':
                strcpy(file_name, optarg);
                return true;
            case '?':
                continue;
            default:
                continue;
        }
    }
    return false;
}