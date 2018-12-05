#include <stdio.h>
#include "Load_Image.h"
#include "Segmentation.h"

int main() {


    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;



    init_sdl();

    image_surface = load_image("../image.bmp");

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

    /*
    while (list)
    {
        printarray(list->matrix , list->width , list->height);
        printf("\n");

        list = list->next;
    }
    */

    /*
    chara= chara->next;

    while (chara->next)
    {
        printarray(chara->matrix , chara->width , chara->height);
        printf("\n");
        chara = chara->next;
    }
    */



    free_matrice(matrice , height);
    free_listofmatrice(list);
    free_listofmatrice(chara);

    

    /*
    it is pour toi tONy 
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    init_sdl();

    image_surface = load_image("image.bmp");
    int width = image_surface->w; // number of pixel in a ligne
    int height = image_surface->h; // number of pixel in a collone 
    int** matrice = creationarrays(image_surface);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    free_matrice(matrice , height);
    */






    
    return 0;
}
