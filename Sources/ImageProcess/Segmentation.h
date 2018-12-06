//
// Created by adrien.duot on 10/25/18.
//

#ifndef IMAGE_PROCESS_SEGMENTATION_H
#define IMAGE_PROCESS_SEGMENTATION_H

#include <err.h>
#include "TrainingResource.h"
#include <stdlib.h>
#include "SDL/SDL.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_video.h"

typedef struct Listofmatrixs
{
	int** matrix;
	int height;
	int width;
	void* next;
} listofmatrix;

typedef struct coor
{
    int up;
    int left;
    int rigth;
    int down;
}coordonate ;




int** creationarrays(SDL_Surface* image_surface);

void Histogrammification(int** arrays ,int width , int height , int* histogramme1, int* histogramme2);

void listification (int** arrays , int* hiligne ,int width , int height , listofmatrix* list );

listofmatrix* addtolist(int** arrays , int width, int start , int end ) ;


void printarray (int** arrays ,int width , int height);

void free_matrice(int** arrays ,int heigth );

void characterisation(listofmatrix* list , listofmatrix* chara);

coordonate* propagation(int ** arrays , int heigth , int width , int x , int y );

void* copying(listofmatrix arrays , coordonate* borne  );

void* space();

void* sautdeligne();



void scale(listofmatrix *src, T_TrainingChar *dst, int newx, int newy);
float blerp(float c00, float c10, float c01, float c11, float tx, float ty);
float lerp(float s, float e, float t);



void free_listofmatrice(listofmatrix* list );

void printlist(int* list, int size );
void printlistdouble(double* list, int size , int width);


void choosefrom_histo(int* histogramme , int size , int* start, int* end);




#endif //IMAGE_PROCESS_SEGMENTATION_H
