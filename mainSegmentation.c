#include <stdio.h>
#include "Load_Image.h"
#include "Segmentation.h"

int main() {


    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;



    init_sdl();

    image_surface = load_image("image.bmp");

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
    printarray(matrice, 190 , 190);
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    //we can free the sdl

    int* hicollone = calloc(height, sizeof(int));
    int* hiligne = calloc(width, sizeof(int));

    Histogrammification(matrice , width, height, hicollone, hiligne);

    
    printf("\n");
    printf("\n");
    printlist(hicollone, height); // histo des collones 
    //printf("\n");
    //printf("\n");
   
    printlist(hiligne, width);//histo des lignes 
    printf("\n");
    printf("\n");
    
    int*** listoflignes = calloc(1, sizeof(int **));
    int* sizeofline = calloc(1, sizeof(int));

    listification(matrice , hicollone ,width ,height ,sizeofline, listoflignes);
    //test(sizeofline, listoflignes);
    //printarray(matrice, 190 , 190);
    //printarray(listoflignes[0] , 190 , 10);


    //free_listofmatrice(listoflignes, sizeofline , width);
    free_matrice(matrice , height);

     //show_image("../image4.bmp");

    /* */
    return 0;
}
