#include "base_structs.h"
#include "parser/parser.h"
#include "consoleLogs/help.h"
#include "consoleLogs/info.h"
#include "image_funcs/image_mirror_func.h"
#include "image_funcs/image_copy_func.h"
#include "image_funcs/image_color_replace_func.h"
#include "image_funcs/image_split_func.h"
#include "image_funcs/image_border_with_extension.h"
#include "image_funcs/encircle_white_area.h"

char** copyArgv(char **argv, int argc){
    char** copy = malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; ++i) {
        copy[i] = malloc((strlen(argv[i])+ 1) * sizeof(char));
        strcpy(copy[i], argv[i]);
    }
    return copy;
}

int main(int argc, char* argv[]) {
    printf("Course work for option 5.2, created by Artem Metelskii\n");

    char** argv_copy = copyArgv(argv, argc);
    enum FuncType fType = emptyFunc;
    Error get_funtType_error = get_func_type(argc, argv_copy, &fType);

    if(get_funtType_error.hasError){
        fprintf(stderr, "Error: error when getting function type, %s\n", get_funtType_error.msg);
        return 40;
    }

    int arg_num = 1; //там всегда есть название программы

    char *input_file_name = malloc(120 * sizeof(char));
    if (input_file_name != NULL) {
        input_file_name[0] = '\0';
    }
    argv_copy = copyArgv(argv, argc);
    if (get_input_file_name_and_has_iFlag(argc, argv_copy, input_file_name))
        arg_num += 2;//+1 ещё за имя ключа -i или --input
    else
        arg_num++;//+1 за само название файла

    char *output_file_name = malloc(120 * sizeof(char));
    if (output_file_name != NULL) {
        output_file_name[0] = '\0';
    }
    argv_copy = copyArgv(argv, argc);
    if (get_output_file_name_and_has_it(argc, argv_copy, output_file_name))
        arg_num += 2; //за название файла + ключ
    else
        output_file_name = "out.bmp";

    switch (fType) {
        case emptyFunc:
            fprintf(stderr, "Error: No such function\n");
            return 40;
        case errorFunc:
            fprintf(stderr, "Error: error when parsing function type\n");
            return 40;
        case extraFunc:
            fprintf(stderr, "Error: possible to use only one function at a time\n");
            return 41;
        case whiteAreaBorderFunc: {
            WhiteAreaBorder *spec = malloc(sizeof(WhiteAreaBorder));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_white_area_border_argsError(argc, argv_copy, spec);
            if (parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for whiteAreaBorderFunc function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num+=3;

            if(arg_num != argc){
                fprintf(stderr, "Error, the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = encircle_white_area(input_file_name, output_file_name, spec);
            if (func_error.hasError){
                fprintf(stderr, "Error: when the execution of the draw outimage border function, %s\n", func_error.msg);
                return 43;
            }
        }
            break;
        case outimageBorderFunc: {
            OutimageBorderSpec *spec = malloc(sizeof(OutimageBorderSpec));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_outimage_border_args(argc, argv_copy, spec);
            if (parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for outimageBorderFunc function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num+=5;

            if(arg_num != argc){
                fprintf(stderr, "Error, the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = draw_border_with_img_extension(input_file_name, output_file_name, spec);
            if (func_error.hasError){
                fprintf(stderr, "Error: when the execution of the draw outimage border function, %s\n", func_error.msg);
                return 43;
            }
        }
            break;
        case mirrorFunc: { //
            MirrorSpec *spec = malloc(sizeof(MirrorSpec));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_mirror_args(argc, argv_copy, spec);
            if(parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for mirror function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num += 7;

            if(arg_num != argc){
                fprintf(stderr, "Error, the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = mirror_area(input_file_name, output_file_name, spec);
            if(func_error.hasError){
                fprintf(stderr, "Error: when the execution of the mirror function, %s\n", func_error.msg);
                return 43;
            }
        }
            break;
        case copyFunc: {
            CopySpec *spec = malloc(sizeof(CopySpec));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_copy_args(argc, argv_copy, spec);
            if(parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for copy function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num += 7;

            if(arg_num != argc){
                fprintf(stderr, "the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = copy_area(input_file_name, output_file_name, spec);
            if(func_error.hasError){
                fprintf(stderr, "Error: when the execution of the copy function, %s\n", func_error.msg);
                return 44;
            }
        }
            break;
        case colorReplaceFunc:{
            ColorReplaceSpec *spec = malloc(sizeof(ColorReplaceSpec));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_color_replacement_args(argc, argv_copy, spec);
            if(parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for replace color function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num += 5;

            if(arg_num != argc){
                fprintf(stderr, "Error, the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = replace_color(input_file_name, output_file_name, spec);
            if(func_error.hasError){
                fprintf(stderr, "Error: when the execution of the replace color function, %s\n", func_error.msg);
                return 45;
            }
        }
            break;
        case splitFunc:{
            BorderSplitSpec *spec = malloc(sizeof(BorderSplitSpec));
            argv_copy = copyArgv(argv, argc);
            Error parse_error = get_border_split_args(argc, argv_copy, spec);
            if(parse_error.hasError){
                fprintf(stderr, "Error: when parsing arguments for split function, %s\n", parse_error.msg);
                return 42;
            }
            arg_num += 9;

            if(arg_num != argc){
                fprintf(stderr, "Error, the name of the input or output file is not specified\n");
                return 46;
            }

            Error func_error = split_image(input_file_name, output_file_name, spec);
            if(func_error.hasError){
                fprintf(stderr, "Error: when the execution of the replace color function, %s\n", func_error.msg);
                return 45;
            }
        }
            break;
        case helpFunc:
            if(argc != arg_num){
                fprintf(stderr, "Error: extra arguments");
            }
            print_help();
            break;
        case infoFunc:{
            arg_num += 1;
            if(argc != arg_num){
                fprintf(stderr, "Error: extra arguments");
            }

            Error info_error = print_info(input_file_name);
            if (info_error.hasError){
                fprintf(stderr, "Error: when the execution of the info function, %s\n", info_error.msg);
                return 48;
            }
        }
            break;
    }
    return 0;
}