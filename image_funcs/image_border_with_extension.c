#include "image_border_with_extension.h"

Error draw_border_with_img_extension(char *input_file_name, char *output_file_name, OutimageBorderSpec *spec) {
    Rgb **canvas;
    BitmapFileHeader *fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error read_file_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);

    if (read_file_error.hasError)
        return read_file_error;

    int new_width = infoHeader->width + spec->thickness * 2;
    int new_height = infoHeader->height + spec->thickness * 2;

    Rgb **new_canvas = malloc(sizeof(Rgb *) * new_height);
    for (int i = 0; i < new_height; ++i) {
        Rgb *row = malloc(sizeof(Rgb) * new_width);
        if (row == NULL)
            return (Error) {true, "error when allocating memory for new canvas"};
        new_canvas[i] = row;
        for (int j = 0; j < new_width; ++j) {
            if (i > spec->thickness && i < new_height - spec->thickness && j > spec->thickness &&
                j < new_width - spec->thickness) {
                new_canvas[i][j] = canvas[i - spec->thickness][j - spec->thickness];
            }else
                new_canvas[i][j] = (*spec->color);
        }
    }

    infoHeader->width = new_width;
    infoHeader->height = new_height;
    int row_size = new_width * sizeof(Rgb) + get_padding(new_width);
    infoHeader->imageSize = row_size * new_height;
    fileHeader->filesize = sizeof(fileHeader) + sizeof(infoHeader) + infoHeader->imageSize;

    Error write_error = write_img(output_file_name, fileHeader, infoHeader, new_canvas);
    if(write_error.hasError)
        return write_error;
    return (Error){false, ""};
}