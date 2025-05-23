#ifndef CW2_FILE_ACTIONS_H
#define CW2_FILE_ACTIONS_H
#include "../base_structs.h"

Error read_img(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader, Rgb*** canvas);
Error write_img(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader, Rgb** canvas);
Error read_file_headers(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader);;
int check_val_range(int v, int maxZ);
Error copy_canvas(Rgb** original, Rgb*** copy, unsigned int height, unsigned int width);
int get_padding(unsigned int width);

#endif
