#include "base_structs.h"
#include "parser/parser.h"
#include "consoleLogs/help.h"
#include "consoleLogs/info.h"
#include "parser/parser.h"

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
            get_mirror_args(argc, argv, spec);
        }
            break;
        case copyFunc: {
            CopySpec *spec = malloc(sizeof(CopySpec));
            get_copy_args(argc, argv, spec);

        }
            break;
        case colorReplaceFunc:{
            ColorReplaceSpec *spec = malloc(sizeof(ColorReplaceSpec));
            get_color_replacement_args(argc, argv, spec);
        }
            break;
        case splitFunc:{
            BorderSplitSpec *spec = malloc(sizeof(BorderSplitSpec));
            get_border_split_args(argc, argv, spec);
        }
            break;
        case helpFunc:
            print_help();
            return 1;
        case infoFunc:

            return 1;
    }


}