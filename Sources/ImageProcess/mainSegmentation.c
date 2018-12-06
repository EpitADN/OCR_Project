#include <stdio.h>

#include "Load_Image.h"
#include "Segmentation.h"
#include "Toolbox_SDL.h"


int main() {


    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;



    init_sdl();

    image_surface = load_image("Images/Examples/image.bmp");

    screen_surface = display_image(image_surface);


    wait_for_keypressed();

    Grissification(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();


    Binarization(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();
/* 
load image
==============================================================
segmentation
*/
    int width = image_surface->w; // number of pixel in a ligne
    int height = image_surface->h; // number of pixel in a collone 
    int** matrice = creationarrays(image_surface);
    //printarray(matrice, 190 , 190);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    //we can free the sdl
    int* hicollone = calloc(height, sizeof(int));
    int* hiligne = calloc(width, sizeof(int));

    Histogrammification(matrice , width, height, hicollone, hiligne);

    listofmatrix* list = malloc( sizeof(listofmatrix));
    listification(matrice , hicollone ,width ,height ,list);

    free(hicollone);
    free(hiligne);

    //list = list->next;
    listofmatrix* chara = malloc(sizeof(listofmatrix));
    characterisation(list , chara);
    chara = chara->next;


    /*
    while (list)
    {
        printarray(list->matrix , list->width , list->height);
        printf("\n");

        list = list->next;
    }
    */

    chara= chara->next;
    chara= chara->next;
    chara= chara->next;
    chara= chara->next;
    chara= chara->next;
    chara= chara->next;
    chara= chara->next;
    listofmatrix* current = chara;
    //while (current)
    {
        printarray(current->matrix , current->width , current->height);
        printf("\n");
        current = current->next;
    }


    T_TrainingChar* temp = malloc(sizeof(T_TrainingChar));
    temp->values =malloc(24 * 24 * sizeof(double));
    scale(chara, temp, 24,24);
    printlistdouble(temp->values , 24*24, 24);

    free_matrice(matrice , height);
    free_listofmatrice(list);
    free_listofmatrice(chara);

    
    return 0;
}
