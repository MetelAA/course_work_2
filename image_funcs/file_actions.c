#include "file_actions.h"

int get_padding(unsigned int width){
    int bytes_per_row = width * 3;
    return (4 - (bytes_per_row % 4)) % 4;
}

Error read_img(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader, Rgb*** canvas){
    Error get_headers_error = read_file_headers(file_name, fHeader, iHeader);
    if(get_headers_error.hasError)
        return get_headers_error;
    FILE *f = fopen(file_name, "rb");

    if(!f){
        return (Error){true, "couldn't open the file for read"};
    }

    fseek(f, (long) fHeader->pixelArrOffset, SEEK_SET);
    int padding = get_padding((long) iHeader->width);

    (*canvas) = malloc(iHeader->height * sizeof(Rgb*));

    if(!(*canvas))
        return (Error){true, "error when alloc mem to pixels arr"};

    for (int i = 0; i < iHeader->height; ++i) {
        (*canvas)[i] = malloc(iHeader->width * sizeof(Rgb*));

        if (!(*canvas)[i])
            return (Error){true, "error when alloc mem to pixels row"};
    }

    for (int i = 0; i < iHeader->height; ++i) {
        for (int j = 0; j < iHeader->width; ++j) {
            fread(&(*canvas)[i][j], sizeof(Rgb), 1, f);
        }
        fseek(f, padding, SEEK_CUR);
    }
    fclose(f);
    return (Error){false, ""};
}

Error write_img(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader, Rgb** canvas){
    FILE* f = fopen(file_name, "wb");

    if(!f){
        return (Error){true, "couldn't open the file for write"};
    }

    fwrite(fHeader, sizeof(BitmapFileHeader), 1, f);
    fwrite(iHeader, sizeof(BitmapInfoHeader), 1, f);

    fseek(f, (long) fHeader->pixelArrOffset, SEEK_SET);

    int padding = get_padding((long) iHeader->width);

    for(int y = 0; y < iHeader->height; y++){
        for(int x = 0; x < iHeader->width; x++)
            fwrite(&canvas[y][x], sizeof(Rgb), 1, f);

        unsigned char padded_px = 0;
        for(int i = 0; i < padding; i++)
            fwrite(&padded_px, sizeof(unsigned char), 1, f);
    }

    fclose(f);
    return (Error){false, ""};
}

Error read_file_headers(char* file_name, BitmapFileHeader* fHeader, BitmapInfoHeader* iHeader){
    FILE *f = fopen(file_name, "rb");

    if(!f){
        return (Error){true, "couldn't open the file for read"};
    }

    fread(fHeader, 1, sizeof(BitmapFileHeader), f);
    fread(iHeader, 1, sizeof(BitmapInfoHeader), f);

    if(fHeader->signature != 0x4D42){
        return (Error){true, "file is not a bmp"};
    }

    if(iHeader->bitsPerPixel != 24){
        return (Error) {true, "images with not 24 bits per px not supported"};
    }

    if(iHeader->compression != 0){
        fprintf(stderr, "images with compression not supported\n");
        return (Error){true, ""};
    }
    return (Error){false, ""};
}

int check_val_range(int v, int maxZ) {
    if (v >= maxZ)
        return maxZ-1;
    else if (v < 0)
        return 0;
    return v;
}

Error copy_canvas(Rgb** original, Rgb*** copy, unsigned int height, unsigned int width){
    (*copy) = (Rgb**)malloc(height * sizeof(Rgb*));
    if (!(*copy))
        return (Error){true, "error when alloc mem to canvas copy"};
    for (unsigned int i = 0; i < height; i++) {
        (*copy)[i] = (Rgb*)malloc(width * sizeof(Rgb));
        if (!(*copy)[i])
            return (Error){true, "error when alloc mem to canvas copy"};
        memcpy((*copy)[i], original[i], width * sizeof(Rgb));
    }
    return (Error){false, ""};
}