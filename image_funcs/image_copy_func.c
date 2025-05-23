#include "image_copy_func.h"




Error copy_area(char *input_file_name, char *output_file_name, CopySpec *copy_spec) {
    Rgb **canvas = NULL;
    BitmapFileHeader *fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error read_image_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);
    if (read_image_error.hasError)
        return read_image_error;

    copy_spec->start_inp_area->x = check_val_range(copy_spec->start_inp_area->x, infoHeader->width);
    copy_spec->start_inp_area->y = check_val_range(copy_spec->start_inp_area->y, infoHeader->height);
    copy_spec->end_inp_area->x = check_val_range(copy_spec->end_inp_area->x, infoHeader->width);
    copy_spec->end_inp_area->y = check_val_range(copy_spec->end_inp_area->y, infoHeader->height);
    copy_spec->dest_point->x = check_val_range(copy_spec->dest_point->x, infoHeader->width);
    copy_spec->dest_point->y = check_val_range(copy_spec->dest_point->y, infoHeader->height);

    Point start_inp = {copy_spec->start_inp_area->x, infoHeader->height - copy_spec->start_inp_area->y - 1};
    Point end_inp = {copy_spec->end_inp_area->x - 1, infoHeader->height - copy_spec->end_inp_area->y};
    Point start_dest = {copy_spec->dest_point->x, infoHeader->height - copy_spec->dest_point->y - 1};

    Rgb **canvas_copy = NULL;
    Error alloc_mem_error = copy_canvas(canvas, &canvas_copy, infoHeader->height, infoHeader->width);
    if (alloc_mem_error.hasError)
        return alloc_mem_error;

    for (int i = start_inp.y; i >= end_inp.y; --i) {
        for (int j = start_inp.x; j <= end_inp.x; ++j) {
            if((start_dest.y - start_inp.y + i) < infoHeader->height && (start_dest.x + j - start_inp.x) < infoHeader->width)
                canvas_copy[start_dest.y - start_inp.y + i][start_dest.x + j - start_inp.x] = canvas[i][j];
        }
    }

    Error write_file_error = write_img(output_file_name, fileHeader, infoHeader, canvas_copy);
    if (write_file_error.hasError)
        return write_file_error;
    return (Error) {false, ""};
}//--right_down 80.231 --input ../inp.bmp --output ./output.bmp --copy --left_up 65.156 --dest_left_up 402.304