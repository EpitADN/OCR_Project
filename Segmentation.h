//
// Created by adrien.duot on 10/25/18.
//

#ifndef IMAGE_PROCESS_SEGMENTATION_H
#define IMAGE_PROCESS_SEGMENTATION_H

#include <err.h>
#include <stdlib.h>
#include "SDL/SDL.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_video.h"


int** creationarrays(SDL_Surface* image_surface);

void Histogrammification(int** arrays ,int width , int height , int* histogramme1, int* histogramme2);

void listification (int** arrays , int* hiligne ,int width , int height ,int* sizeofline, int*** listoflignes);

void addtolist(int** arrays , int height, int start , int end , int*** listoflignes , int nbofligne);

void test(int* sizeofline, int*** listoflignes);

void printarray (int** arrays ,int width , int height);

void free_matrice(int** arrays ,int width );

void free_listofmatrice(int*** arrays ,int* sizeofline ,int width );

void printlist(int* list, int size );

void choosefrom_histo(int* histogramme , int size , int* start, int* end);


#endif //IMAGE_PROCESS_SEGMENTATION_H
