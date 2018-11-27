//
// Created by adrien.duot on 10/25/18.
//

#include "Segmentation.h"
#include "Load_Image.h"
#include <stdlib.h>



int** creationarrays(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    int** matrix = (int **)malloc(sizeof(int *) * height);
    for (int l = 0; l < height; l++)
        matrix[l] = (int *)malloc(sizeof(int) * width);

    for(int x =0; x < height;++x)
    {
        for(int y=0; y < width;++y)
        {
            Uint32 pixel = get_pixel(image_surface, y, x);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            matrix[x][y] = r/255;
        }
    }
    return  matrix;
}

void Histogrammification(int** arrays ,int width , int height , int* histogramme1, int* histogramme2){


    for (int i = 0;i<height;++i) {
        for(int j = 0;j< width ; ++j){
            if (arrays[i][j] >= 0.5) {
                histogramme1[i] += 1;
                histogramme2[j] += 1;
            }

        }
    }
}

void listification (int** arrays , int* hiligne ,int width , int height ,int* sizeofline, int*** listoflignes)
{
    printf("width = %d height = %d \n" , width , height);
    int average = 0;
    for (int k = 0; k < width; ++k) {
        average += hiligne[k];
    }
    average /= width ;
    average = 1.30* average;

    int nbofligne =0;
    int start = 0;

    int colors = hiligne[0] <= average;
    for (int i = 0; i < height; ++i)
    {
        int current_colors = hiligne[i] <= average;
        if ( colors != current_colors )
        {
            printf("start  = %d end = %d\n",start, i );
            addtolist(arrays, width, start ,  i - 1 , listoflignes , nbofligne +1);
            sizeofline = realloc(sizeofline , (nbofligne + 2 ) *sizeof(int) );
            sizeofline[nbofligne + 1 ] = i - 1 - start;
            //printarray(listoflignes[nbofligne] , 2 , height);
            //printf("\n");
            start = i;
            colors = current_colors;
            nbofligne += 1;
        }
            
    }
    //sizeofline[0] = nbofligne;
    //printf("%d\n",nbofligne );
    //for (int i = 0; i < nbofligne - 1; ++i)
    //{    
    //printarray(listoflignes[1] , 190, 10);
    //}
    
}

void addtolist(int** arrays , int width, int start , int end , int*** listoflignes , int nbofligne)
{
    printf(" nbof ligne = %d   \n",nbofligne );
    listoflignes = realloc(listoflignes , nbofligne * sizeof(int **));
    if (listoflignes == NULL)
    {
        printf("%s\n", " erreur realloc ");

    }
    listoflignes[nbofligne - 1] = calloc(end - start ,sizeof(int *) );
    for (int l = 0; l < end - start; ++l)
        listoflignes[nbofligne - 1][l] = /* malloc(sizeof(int) * end - start);*/ calloc( width , sizeof(int));

    for(int x =start ; x < end ;++x)
    //for(int y=start; y < end ;++y)
    {
        //printf("\\ %d \n", x );
        
        //for(int x =0 ; x < width ;++x)
        for(int y=0; y < width ;++y)
        {            
            //printf("%d",arrays[x][y] );
            //listoflignes[nbofligne -1 ][x][y - start] = 0;
            
            listoflignes[nbofligne -1 ][x - start][y] = arrays[x][y];
            //printf("%d",listoflignes[nbofligne -1 ][x][y - start] );
        }
    }
    
    if (nbofligne != 0)
        {
            printarray(listoflignes[nbofligne- 1] , 190, end - start  );
        }

    //printf("ligne %i has workaded %i \n",nbofligne -1 , listoflignes[nbofligne -1 ][0][0]  );

}



void test(int* sizeofline, int*** listoflignes)
{
    printarray(listoflignes[0], 190, sizeofline[1]);
}


/*
void choosefrom_histo(int* histogramme , int size , int* start, int* end) {
    int average = 0;
    for (int k = 0; k <size; ++k) {
        average += histogramme[k];
    }
    average /= size;

    for (int i = 0; i < size; i++) {
        if (histogramme[i] < average && &end == -1)
        {
            start& = i;
        }
        else if (histogramme[i] >= average)
        {
            end = i;
        }
    }

}

*/
void printarray (int** arrays ,int width , int height)
{
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            if (&arrays[i][j] != NULL)
                printf("%d", arrays[i][j]);
        }
        printf("\n");
    }
}

void printlist(int* list, int size )
{
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        printf("%d " , list[i]);
        sum += list[i];
    }
    printf("%d \n ", sum / size);
}



void free_matrice(int** arrays ,int width )
{

    for (int l = 0; l < width; l++)
        free(arrays[l]);
    free(arrays);
}

void free_listofmatrice(int*** arrays ,int* sizeofline ,int width )
{
    int nbofligne = sizeofline[0];
    for (int l = 0; l < nbofligne; l++)
        free_matrice(arrays[l] , width);
    free(arrays);
}
/*
double** resize (double** arrays , int width , int heigth)
{
    TupleHi* hitsos = histogrammification(arrays , width, heigth);
    Tuple* wid = choosefrom_histo(hitsos->item1 , width);
    int newwidth = (wid->item2- wid->item1);
    Tuple *hei = choosefrom_histo(hitsos->item2 , heigth);
    int newheigth = (hei->item2 - hei->item1);
    double ** newarrays = (double**)malloc(sizeof(double*) * newwidth );
    for (int i = 0; i <  newwidth; ++i)
    {
        newarrays[i] = (double*)malloc(sizeof(double) * newheigth );
    }

    for (int k = wid->item1; k < wid->item2; ++k) {
        for (int l = hei->item1; l < hei->item2; ++l) {
            newarrays[k - wid->item1 ][l - hei->item1] = arrays [k][l];
        }
    }
    free(arrays);
    return  newarrays;
} */
