#include "image_color_replace_func.h"


Error replace_color(char* input_file_name, char* output_file_name, ColorReplaceSpec *replace_spec){
    Rgb** canvas;
    BitmapFileHeader* fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader* infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error read_image_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);
    if (read_image_error.hasError)
        return read_image_error;

    for (int i = 0; i < infoHeader->height; ++i) {
        for (int j = 0; j < infoHeader->width; ++j) {
            if (canvas[i][j].b == replace_spec->old_color->b &&
                canvas[i][j].g == replace_spec->old_color->g &&
                canvas[i][j].r == replace_spec->old_color->r) {
                canvas[i][j] = (*replace_spec->new_color);
            }
        }
    }

    Error write_file_error = write_img(output_file_name, fileHeader, infoHeader, canvas);
    if (write_file_error.hasError)
        return write_file_error;
    return (Error){false, ""};
}