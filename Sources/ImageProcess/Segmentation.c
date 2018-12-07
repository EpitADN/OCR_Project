//
// Created by adrien.duot on 10/25/18.
//

#include "Segmentation.h"
#include "Load_Image.h"
#include <stdlib.h>
#include <stdint.h>


int** creationarrays(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    int** matrix = malloc(sizeof(int *) * height);
    for (int l = 0; l < height; l++)
        matrix[l] = malloc(sizeof(int) * width);

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
    return matrix;
}

void Histogrammification(int** arrays ,int width , int height , int* histogramme1){

    for (int i = 0;i<height;++i) {
        for(int j = 0;j< width ; ++j){
            if (arrays[i][j] >= 0.5) {
                histogramme1[i] += 1;
            }
        }
    }
}

void Listification (int** arrays , int* hicolonne ,int width , int height , listofmatrix* list )
{
    double average = 0;
    for (int k = 0; k < height; ++k) {
        average += (double)hicolonne[k];
    }
    average /= height ;
    average = 1.1 * average;


    int start = 0;
    listofmatrix* currentmatrix =list;
    int colors = hicolonne[0] <= average;
    int current_colors;

    for (int i = 0; i < height; ++i)
    {
        current_colors = hicolonne[i] <= average;

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
    listofmatrix* new = NULL;
    new = malloc(sizeof(listofmatrix));

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

void characterisation(listofmatrix* Lines , listofmatrix* Chars) //pour les caractères heigth -1 space et width = -1 \n
{
    listofmatrix* currentchara= Chars;
    while (Lines)
    {
        for (int j = 0; j < Lines ->width; ++j) {
            for (int i = 0; i < Lines->height; ++i) {
                if (Lines->matrix[i][j] == 0) {

                    coordonate *temp;
                    temp = propagation(Lines->matrix, Lines->height, Lines->width, i, j);

                    currentchara->next = copying(*Lines, temp);
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
            //currentchara->next = sautdeligne();
            //currentchara = currentchara->next;
        }
        Lines = Lines->next;
    }
}

coordonate* propagation(int ** arrays , int heigth , int width , int x , int y )
{
    coordonate* bordure = NULL;
    bordure = malloc(sizeof(coordonate));

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


    listofmatrix* new = NULL;
    new = malloc(sizeof(listofmatrix));

    new->next = NULL;
    new->height = borne->down - borne->up   ;
    new->width = borne->rigth - borne->left  ;

    new->matrix = malloc( (size_t)new->height *sizeof(int *) );
    for (int l = 0; l < new->height; ++l)
        new->matrix[l] =  malloc( (size_t)new->width * sizeof(int));

    for(int x =borne->up ; x < borne->down  ;++x) {
        for (int y = borne->left; y < borne->rigth  ; ++y) {
            if (arrays.matrix[x][y] != 2 )
            {
                new->matrix[x - borne->up][y - borne->left] = 1;
            }
            else
                new->matrix[x - borne->up][y - borne->left] = 0;
        }

    }
    free(borne);
    return new;
}

void* space()
{

    listofmatrix* new = NULL;
    new = malloc(sizeof(listofmatrix));

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

void* sautdeligne()
{

    listofmatrix* new = malloc(sizeof(listofmatrix));

    new->next = NULL;
    new->height = -1  ;
    new->width = -1  ;

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

void printlistdouble(double* list, int size, int width )
{
    double sum = 0;
    for (int i = 0; i < size; ++i) {

        sum += list[i];
        if (i %width == 0)
            printf("\n");
        printf("%d" , (int)list[i]);
    }

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

float lerp(float s, float e, float t){
    return s+(e-s)*t;
}
float blerp(float c00, float c10, float c01, float c11, float tx, float ty){
    return lerp(lerp(c00, c10, tx), lerp(c01, c11, tx), ty);
}


#define getByte(value, n) (value >> (n*8) & 0xFF)

void scale(listofmatrix *src, T_TrainingChar *dst, int newx, int newy){
    int newWidth = newx;
    int newHeight= newy;
    dst->values = malloc(24*24 * sizeof(double));

    for(int x= 0; x < newHeight; x++) {
        for (int y = 0; y < newWidth; ++y) {


            float gx = x  * (src->height - 1)/( (float) (newHeight));
            float gy = y  * (src->width - 1)/ (float) (newWidth);
            int gxi = (int) gx;
            int gyi = (int) gy;
            uint32_t result = 0;
            uint32_t c00 = ( src->matrix[gxi][gyi]== 1) ? 16777215 :0 ;
            uint32_t c10 = ((Uint32) src->matrix[gxi + 1][gyi] ==1) ? 16777215 :0 ;
            uint32_t c01 = ((Uint32) src->matrix[gxi][gyi + 1] ==1) ? 16777215 :0 ;
            uint32_t c11 = ((Uint32) src->matrix[gxi+1][gyi+1] ==1) ? 16777215 :0 ;
            uint8_t i;
            for (i = 0; i < 3; i++) {
                //result |=((uint8_t*)&result)[i] = blerp( ((uint8_t*)&c00)[i], ((uint8_t*)&c10)[i], ((uint8_t*)&c01)[i], ((uint8_t*)&c11)[i], gxi - gx, gyi - gy); // this is shady
                result |= (uint8_t) blerp(getByte(c00, i), getByte(c10, i), getByte(c01, i), getByte(c11, i), gx - gxi, gy - gyi) << (8 * i);
                //result |= (uint8_t) blerp(c00,c10,c01,c11, gx - gxi, gy - gyi) ;

            }
            //result = ((c00 + c10 + c01 + c11) == 1) ? 0 :1;
            dst->values[x * newHeight + y] = (result > 0) ? 0 : 1;
        }
    }
}

/*
void scale(listofmatrix *src, T_TrainingChar *dst, float scalex, float scaley){

    int** matrix = src->matrix;
    int newWidth = (int)(src->width*scalex);
    int newHeight= (int)(src->height*scaley);

    dst->values = malloc(newHeight * newHeight * sizeof(double));

    int x, y;
    for(x= 0, y=0; y < newHeight; x++){
        if(x > newWidth){
            x = 0; y++;
        }
        float gx = x / (float)(newWidth) * (src->width-1);
        float gy = y / (float)(newHeight) * (src->height-1);
        int gxi = (int)gx;
        int gyi = (int)gy;
        uint32_t result=0;
        uint32_t c00 = (Uint32) src->matrix[gxi][gyi];
        uint32_t c10 = (Uint32) src->matrix[gxi+1][gyi];
        uint32_t c01 = (Uint32) src->matrix[gxi][gyi+1];
        uint32_t c11 = (Uint32) src->matrix[gxi+1][gyi+1];
        uint8_t i;
        for(i = 0; i < 3; i++){
            //((uint8_t*)&result)[i] = blerp( ((uint8_t*)&c00)[i], ((uint8_t*)&c10)[i], ((uint8_t*)&c01)[i], ((uint8_t*)&c11)[i], gxi - gx, gyi - gy); // this is shady
            result |= (uint8_t)blerp(getByte(c00, i), getByte(c10, i), getByte(c01, i), getByte(c11, i), gx - gxi, gy -gyi) << (8*i);
        }
        dst->values[x * newHeight + y] = result;



    }
}*/