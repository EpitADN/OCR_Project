//
// Created by adrien.duot on 10/25/18.
//

#include "Segmentation.h"
#include "Load_Image.h"


int** creationarrays(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    int** matrix = (int **)malloc(sizeof(int *) * width);
    for (int l = 0; l < width; l++)
        matrix[l] = (int *)malloc(sizeof(int) * height);

    for(int x =0; x < width;++x)
    {
        for(int y=0; y < height;++y)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            matrix[x][y] = r/255;
        }
    }
    return  matrix;
}

void Histogrammification(int** arrays ,int width , int height , int* histogramme1, int* histogramme2){


    for (int i = 0;i<width;++i) {
        for(int j = 0;j< height ; ++j){
            if (arrays[i][j] >= 0.5) {
                histogramme1[i] += 1;
                histogramme2[j] += 1;
            }

        }
    }
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
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            printf("%d ", arrays[j][i]);
        }
        printf("\n");
    }
}

void printlist(int* list, int size )
{
    for (int i = 0; i < size; ++i) {
        printf("%d " , list[i]);
    }
    printf("\n");
}


void free_matrice(int** arrays ,int width )
{

    for (int l = 0; l < width; l++)
        free(arrays[l]);
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