//
// Created by adrien on 16/10/18.
//

#ifndef OCR_PROJECT_IMAGE_PROCESS_H
#define OCR_PROJECT_IMAGE_PROCESS_H
#include <stdio.h>
#include "stdlib.h"




typedef struct {
    int item1;
    int item2;
}Tuple;

typedef struct {
    int* item1;
    int* item2;
}TupleHi;

typedef struct {
    Tuple item1;
    Tuple item2;
}TupleOfTuple;



typedef struct {
    unsigned char Rouge;
    unsigned char Vert;
    unsigned char Bleu;
}Pixel;

typedef struct {
    int Size;
    int Width;
    int Height;
    int startimage;
}Header;

typedef struct {
    int Size;
    int Width;
    int Height;
    Pixel **Pixels;
    char Header;
}Bmp;



Bmp ColorsToPixel(char Color[], Header head);
Bmp gettingimage(FILE *path);
Bmp decolorize(Bmp *bmp);
TupleHi* histogrammification(double** arrays ,int height , int width);
double** resize (double** arrays , int width , int heigth);
Tuple* choosefrom_histo(int* histogramme , int size);


#endif //OCR_PROJECT_IMAGE_PROCESS_H
