#include "base_structs.h"
#include "parser/parser.h"
#include "consoleLogs/help.h"
#include "consoleLogs/info.h"

int main(int argc, char* argv[]) {
    printf("Course work for option 5.2, created by Artem Metelskii\n");

    enum FuncType fType = get_func_type(argc, argv);
    int arg_num = 1; //там всегда есть название программы

    char *input_file_name = malloc(120 * sizeof(char));
    if (input_file_name != NULL) {
        input_file_name[0] = '\0';
    }
    if (get_input_file_name_and_has_iFlag(argc, argv, input_file_name))
        arg_num += 2;//+1 ещё за имя ключа -i или --input
    else
        arg_num++;//+1 за само название файла

    char *output_file_name = malloc(120 * sizeof(char));
    if (output_file_name != NULL) {
        output_file_name[0] = '\0';
    }
    if (get_output_file_name_and_has_it(argc, argv, output_file_name))
        arg_num += 2; //за название файла + ключ
    else
        output_file_name = "out.bmp";


    printf("input file name - %s\noutput file name - %s\n", input_file_name, output_file_name);
    switch (fType) {
        case emptyFunc:
            printf("Error: No such function\n");
            return 40;
        case errorFunc:
            printf("Error: error when parsing function type\n");
            return 40;
        case extraFunc:
            printf("Error: possible to use only one function at a time\n");
            return 41;
        case mirrorFunc: {
            MirrorSpec *spec = malloc(sizeof(MirrorSpec));
            if(!get_mirror_args(argc, argv, spec)){
                printf("Error: parsing arguments for mirror function, non correct format\n");
                return 42;
            }
            arg_num += 7;

            printf("MirrorSpec: start_area=(%d, %d), end_area=(%d, %d), axis='%c'\n",
                   spec->start_area->x,
                   spec->start_area->y,
                   spec->end_area->x,
                   spec->end_area->y,
                   spec->axis
            );
        }
            break;
        case copyFunc: {
            CopySpec *spec = malloc(sizeof(CopySpec));
            if(!get_copy_args(argc, argv, spec)){
                printf("Error: parsing arguments for copy function, non correct format\n");
                return 42;
            }
            arg_num += 7;

            printf("CopySpec: start_imp_area=(%d, %d), end_imp_area=(%d, %d), dest_point=(%d, %d)\n",
                   spec->start_inp_area->x,
                   spec->start_inp_area->y,
                   spec->end_inp_area->x,
                   spec->end_inp_area->y,
                   spec->dest_point->x,
                   spec->dest_point->y
            );
        }
            break;
        case colorReplaceFunc:{
            ColorReplaceSpec *spec = malloc(sizeof(ColorReplaceSpec));

            if(!get_color_replacement_args(argc, argv, spec)){
                printf("Error: parsing arguments for replace color function, non correct format\n");
                return 42;
            }
            arg_num += 5;

            printf("ColorReplaceSpec: old_color=(R:%d, G:%d, B:%d), new_color=(R:%d, G:%d, B:%d)\n",
                   spec->old_color->r,
                   spec->old_color->g,
                   spec->old_color->b,
                   spec->new_color->r,
                   spec->new_color->g,
                   spec->new_color->b
            );
        }
            break;
        case splitFunc:{
            BorderSplitSpec *spec = malloc(sizeof(BorderSplitSpec));
            if(!get_border_split_args(argc, argv, spec)){
                printf("Error: parsing arguments for split function, non correct format\n");
                return 42;
            }
            arg_num += 9;

            printf("BorderSplitSpec: y_frags=%d, x_frags=%d, thickness=%d, color=(R:%d, G:%d, B:%d)\n",
                   spec->y_frags,
                   spec->x_frags,
                   spec->thickness,
                   spec->color->r,
                   spec->color->g,
                   spec->color->b
            );
        }
            break;
        case helpFunc:
            print_help();
            return 1;
        case infoFunc:
            return 1;
    }


    printf("\t\t argc - %d and arguments_num - %d\n\n", argc, arg_num);



}