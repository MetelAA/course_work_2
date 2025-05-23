#include "image_split_func.h"

Error split_image(char *input_file_name, char *output_file_name, BorderSplitSpec *split_spec) {
    Rgb **canvas;
    BitmapFileHeader *fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error read_image_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);
    if (read_image_error.hasError)
        return read_image_error;

    int dx = (infoHeader->width / split_spec->x_frags) + (infoHeader->width % split_spec->x_frags != 0 ? 1 : 0);
    int dy = (infoHeader->height / split_spec->y_frags) + (infoHeader->height % split_spec->y_frags != 0 ? 1 : 0);

    for (int i = dx; i < infoHeader->width; i += dx) {
        for (int j = 0; j < infoHeader->height; ++j) {
            int start_x = i - split_spec->thickness / 2;
            int end_x = (i + split_spec->thickness / 2) + (split_spec->thickness % 2 == 1 ? 0: -1);
            start_x = check_val_range(start_x, infoHeader->width);
            end_x = check_val_range(end_x, infoHeader->width);

            for (int k = start_x; k <= end_x ; ++k) {
                canvas[j][k] = (*split_spec->color);
            }
        }
    }

    for (int i = dy; i < infoHeader->height; i+=dy) {
        int start_y = i - split_spec->thickness / 2;
        int end_y = (i + split_spec->thickness / 2) + (split_spec->thickness % 2 == 1 ? 0 : -1);
        start_y = check_val_range(start_y, infoHeader->height);
        end_y = check_val_range(end_y, infoHeader->height);
        for (int k = start_y; k <= end_y; ++k) {
            for (int j = 0; j < infoHeader->width; ++j) {
                canvas[k][j] = (*split_spec->color);
            }
        }
    }

    Error write_file_error = write_img(output_file_name, fileHeader, infoHeader, canvas);
    if (write_file_error.hasError)
        return write_file_error;
    return (Error) {false, ""};
}