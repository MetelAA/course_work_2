#include "image_mirror_func.h"

Error mirror_area(char *input_file_name, char *output_file_name, MirrorSpec *mirror_spec) {
    Rgb **canvas;
    BitmapFileHeader *fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error read_image_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);
    if (read_image_error.hasError)
        return read_image_error;

    mirror_spec->start_area->x = check_val_range(mirror_spec->start_area->x, infoHeader->width);
    mirror_spec->start_area->y = check_val_range(mirror_spec->start_area->y, infoHeader->height);
    mirror_spec->end_area->x = check_val_range(mirror_spec->end_area->x, infoHeader->width);
    mirror_spec->end_area->y = check_val_range(mirror_spec->end_area->y, infoHeader->height);

    Point left_up = {mirror_spec->start_area->x, infoHeader->height - mirror_spec->start_area->y - 1};
    Point right_down = {mirror_spec->end_area->x, infoHeader->height - mirror_spec->end_area->y - 1};

    right_down.x--;
    right_down.y++;

    Rgb **canvas_copy = NULL;
    Error alloc_mem_error = copy_canvas(canvas, &canvas_copy, infoHeader->height, infoHeader->width);
    if (alloc_mem_error.hasError)
        return alloc_mem_error;

    if (mirror_spec->axis == 'x') {
        for (int y = right_down.y; y <= left_up.y; ++y) {
            for (int x = left_up.x; x <= right_down.x; ++x) {
                canvas_copy[y][right_down.x - x + left_up.x] = canvas[y][x+1];
            }
        }
    } else {
        for (int x = left_up.x; x <= right_down.x; ++x) {
            for (int y = right_down.y; y <= left_up.y; ++y) {
                canvas_copy[left_up.y - y + right_down.y][x] = canvas[y-1][x];
            }
        }
    }

    Error write_file_error = write_img(output_file_name, fileHeader, infoHeader, canvas_copy);
    if (write_file_error.hasError)
        return write_file_error;
    return (Error) {false, ""};
}