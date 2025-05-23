#include "encircle_white_area.h"

bool check_val(int z, int maxZ){
    if (z >= maxZ || z < 0)
        return false;
    return true;
}

bool check_color(Rgb check, Rgb color){
    if (check.r == color.r && check.b == color.b && check.g == color.g)
        return true;
    return false;
}

Error encircle_white_area(char* input_file_name, char* output_file_name, WhiteAreaBorder* spec){
    Rgb** canvas;
    BitmapFileHeader *fileHeader = malloc(sizeof(BitmapFileHeader));
    BitmapInfoHeader *infoHeader = malloc(sizeof(BitmapInfoHeader));

    Error file_read_error = read_img(input_file_name, fileHeader, infoHeader, &canvas);

    if (file_read_error.hasError)
        return file_read_error;

    for (int i = 0; i < infoHeader->height; ++i) {
        for (int j = 0; j < infoHeader->width; ++j) {
            if(check_color(canvas[i][j], (Rgb){255, 255, 255})){
                for (int k = -1; k <= 1; ++k) {
                    for (int l = -1; l <= 1; ++l) {
                        if (k == 0 && l == 0) continue;
                        int y = i + k;
                        int x = j + l;
                        if(check_val(y, infoHeader->height) && check_val(x, infoHeader->width) && !check_color(canvas[y][x], (Rgb){255, 255, 255})){
                            canvas[y][x] = (*spec->color);
                        }
                    }
                }
            }
        }
    }

    Error write_file_error = write_img(output_file_name, fileHeader, infoHeader, canvas);
    if (write_file_error.hasError)
        return write_file_error;
    return (Error){false, ""};
}