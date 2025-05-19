#ifndef CW2_BASE_STRUCTS_H
#define CW2_BASE_STRUCTS_H

#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>



#pragma pack(push, 1)

typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct {
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

#pragma pack(pop)

typedef struct {
    unsigned int x, y;
} Point;

typedef struct {
    int y_frags;
    int x_frags;
    int thickness;
    Rgb *color;
} BorderSplitSpec;

typedef struct {
    Point *start_area;
    Point *end_area;
    char axis;
} MirrorSpec;

typedef struct {
    Point* start_inp_area;
    Point* end_inp_area;
    Point* dest_point;
} CopySpec;

typedef struct {
    Rgb* old_color;
    Rgb*  new_color;
} ColorReplaceSpec;

enum FuncType{
    emptyFunc,
    errorFunc,
    extraFunc,
    mirrorFunc,
    copyFunc,
    colorReplaceFunc,
    splitFunc,
    helpFunc,
    infoFunc
};

enum parsingArgsError{

};

#endif
