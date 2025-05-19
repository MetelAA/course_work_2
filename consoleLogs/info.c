#include "info.h"

void print_info(BitmapInfoHeader bmih, BitmapFileHeader bmfh){
    printf("File header info:\n");
    printf("signature:          \t%x (%hu)\n", bmfh.signature, bmfh.signature);
    printf("filesize:           \t%x (%u)\n", bmfh.filesize, bmfh.filesize);
    printf("reserved1:          \t%x (%hu)\n", bmfh.reserved1, bmfh.reserved1);
    printf("reserved2:          \t%x (%hu)\n", bmfh.reserved2, bmfh.reserved2);
    printf("pixelArrOffset:     \t%x (%u)\n", bmfh.pixelArrOffset, bmfh.pixelArrOffset);
    printf("Bitmap header info:\n");
    printf("headerSize:         \t%x (%u)\n", bmih.headerSize, bmih.headerSize);
    printf("width:              \t%x (%u)\n", bmih.width, bmih.width);
    printf("height:             \t%x (%u)\n", bmih.height, bmih.height);
    printf("planes:             \t%x (%hu)\n", bmih.planes, bmih.planes);
    printf("bitsPerPixel:       \t%x (%hu)\n", bmih.bitsPerPixel, bmih.bitsPerPixel);
    printf("compression:        \t%x (%u)\n", bmih.compression, bmih.compression);
    printf("imageSize:          \t%x (%u)\n", bmih.imageSize, bmih.imageSize);
    printf("xpixelsPerMeter:    \t%x (%u)\n", bmih.xPixelsPerMeter, bmih.xPixelsPerMeter);
    printf("ypixelsPerMeter:    \t%x (%u)\n", bmih.yPixelsPerMeter, bmih.yPixelsPerMeter);
    printf("colorsInColorTable: \t%x (%u)\n", bmih.colorsInColorTable, bmih.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", bmih.importantColorCount, bmih.importantColorCount);
}
