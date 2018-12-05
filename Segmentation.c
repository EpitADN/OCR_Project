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

    int** matrix = malloc(sizeof(int *) * height);
    for (int l = 0; l < height; l++)
        matrix[l] = malloc(sizeof(int) * width);

    for(unsigned int x =0; x < height;++x)
    {
        for(unsigned int y=0; y < width;++y)
        {
            Uint32 pixel = get_pixel(image_surface, y, x);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            matrix[x][y] = r/255;
        }
    }
    return matrix;
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

void listification (int** arrays , int* hiligne ,int width , int height , listofmatrix* list )
{

    double average = 0;
    for (int k = 0; k < width; ++k) {
        average += hiligne[k];
    }
    average /= width ;
    average = 1.25 * average;


    int start = 0;
    listofmatrix* currentmatrix =list;
    int colors = hiligne[0] <= average ;
    for (int i = 0; i < height; ++i)
    {
        int current_colors = hiligne[i] <= average;

        if ( colors != current_colors  )
        {

            if (current_colors == 0){//case black


                currentmatrix->next =  addtolist(arrays, width, start ,  i - 1);
                currentmatrix = currentmatrix->next;
            }
            start = i;
            colors = current_colors;
        }

    }

}

listofmatrix* addtolist(int** arrays , int width, int start , int end )
{
    listofmatrix* new = malloc(sizeof(listofmatrix));

    new->next = NULL;
    new->height = end - start;
    new->width = width;

    new->matrix = calloc(end - start ,sizeof(int *) );
    for (int l = 0; l < end - start; ++l)
        new->matrix[l] =  calloc( width , sizeof(int));

    for(int x =start ; x < end ;++x) {
        for (int y = 0; y < width; ++y) {

            new->matrix[x - start][y] = arrays[x][y];
        }

    }
    //printarray(new->matrix, new->width , new ->height);
    return new;
}

void characterisation(listofmatrix* list , listofmatrix* chara) //pour les caractères heigth -1 space et width = -1 \n
{
    listofmatrix* currentchara= chara;
    while (list)
    {
        //int spac = 0;
        for (int j = 0; j < list ->width; ++j)
        {
             for (int i = 0; i < list->height; ++i)
             {
                if (list->matrix[i][j] == 0)
                {

                    coordonate* temp;
                    temp = propagation(list->matrix , list->height , list->width , i,j );

                    //printarray(list->matrix,list->width, list->height);
                    currentchara->next = copying(*list , temp);

                    j = temp->rigth;
                    i = 0;
                    //spac = 0;

                    currentchara = currentchara->next;
                }
                /*spac+=1;
                if (spac >= 65)
                {
                    currentchara->next = space();
                    currentchara = currentchara->next;
                    spac = 0;
                }*/
             }
        }
        printf("\n");
        list = list->next;
    }
}

coordonate* propagation(int ** arrays , int heigth , int width , int x , int y )
{
    coordonate* bordure = malloc(sizeof(coordonate));

    bordure->down= x;
    bordure->up = x;
    bordure->left = y;
    bordure->rigth = y;
    arrays[x][y] = 2;
    if (x + 1 < heigth && arrays[x + 1][y] == 0)
    {
        coordonate* temp ;
        temp = propagation(arrays , heigth , width , x+1 , y);
        if (temp->up < bordure ->up)
            bordure ->up =temp->up ;
        if (temp->rigth > bordure ->rigth)
            bordure ->rigth =temp->rigth ;
        if (temp->left < bordure ->left)
            bordure ->left =temp->left ;
        if (temp->down > bordure ->down)
            bordure ->down =temp->down ;
        free(temp);
    }
    if (y + 1 < width && arrays[x][y + 1] == 0)
    {
        coordonate* temp ;
        temp = propagation(arrays , heigth , width , x , y + 1);
        if (temp->up < bordure ->up)
            bordure ->up =temp->up ;
        if (temp->rigth > bordure ->rigth)
            bordure ->rigth =temp->rigth ;
        if (temp->left < bordure ->left)
            bordure ->left =temp->left ;
        if (temp->down > bordure ->down)
            bordure ->down =temp->down ;
        free(temp);

    }
    if (x - 1 > 0 && arrays[x - 1][y] == 0)
    {
        coordonate* temp;
        temp = propagation(arrays , heigth , width , x-1 , y);
        if (temp->up < bordure ->up)
            bordure ->up =temp->up ;
        if (temp->rigth > bordure ->rigth)
            bordure ->rigth =temp->rigth ;
        if (temp->left < bordure ->left)
            bordure ->left =temp->left ;
        if (temp->down > bordure ->down)
            bordure ->down =temp->down ;
        free(temp);

    }
    if (y - 1 > 0 && arrays[x ][y - 1] == 0)
    {
        coordonate* temp;
        temp = propagation(arrays , heigth , width , x , y - 1);
        if (temp->up < bordure ->up)
            bordure ->up =temp->up ;
        if (temp->rigth > bordure ->rigth)
            bordure ->rigth =temp->rigth ;
        if (temp->left < bordure ->left)
            bordure ->left =temp->left ;
        if (temp->down > bordure ->down)
            bordure ->down =temp->down ;
        free(temp);

    }
    return bordure;
}

void* copying(listofmatrix arrays , coordonate* borne )
{

    listofmatrix* new = malloc(sizeof(listofmatrix));

    new->next = NULL;
    new->height = borne->down - borne->up   ;
    new->width = borne->rigth - borne->left  ;

    new->matrix = calloc( (size_t)new->height ,sizeof(int *) );
    for (int l = 0; l < new->height; ++l)
        new->matrix[l] =  calloc( (size_t)new->width , sizeof(int));

    for(int x =borne->up ; x < borne->down  ;++x) {
        for (int y = borne->left; y < borne->rigth  ; ++y) {
            if (arrays.matrix[x][y] != 2 )
            {
                new->matrix[x - borne->up][y - borne->left] = 1;
            }
            else
                new->matrix[x - borne->up][y - borne->left] = 0;
            //printf("\n");
        }

    }
    free(borne);
    return new;
}

void* space()
{

    listofmatrix* new = malloc(sizeof(listofmatrix));

    new->next = NULL;
    new->height = 24  ;
    new->width = 24  ;

    new->matrix = calloc( (size_t)new->height ,sizeof(int *) );
    for (int l = 0; l < new->height; ++l)
        new->matrix[l] =  calloc( (size_t)new->width , sizeof(int));

    for(int x =0 ; x < 24 ;++x) {
        for (int y = 0; y < 24; ++y) {

            new->matrix[x][y] = 1;
        }

    }
    return new;
}


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



void free_matrice(int** arrays ,int heigth )
{

    for (int l = 0; l < heigth; l++)
        free(arrays[l]);
    free(arrays);
}

void free_listofmatrice(listofmatrix* list )
{
    while (list) {
        listofmatrix *temp = list->next;
        free_matrice(list->matrix, list->height);
        free(list);
        list = temp;
    }
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
