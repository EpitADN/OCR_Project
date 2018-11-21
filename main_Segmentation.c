#include <stdio.h>
#include "Load_Image.h"
#include "Segmentation.h"

int main() {


    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;



    init_sdl();

    image_surface = load_image(".alphabet.bmp");

    screen_surface = display_image(image_surface);


    wait_for_keypressed();
    wait_for_keypressed();

    Grissification(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();


    Binarization(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();


    int width = image_surface->w;
    int height = image_surface->h;
    int** matrice = creationarrays(image_surface);
    printarray(matrice, width , height);

    int* histo1 = calloc(width, sizeof(int));
    int* histo2 = calloc(height, sizeof(int));

    Histogrammification(matrice , width, height, histo1, histo2);

    //int* start ;
    //int* end ;
    //start = -1;
    //choosefrom_histo(histo1 , width, start, end);
    //printf("%d %d" , start, end);

    printlist(histo1, width);
    printlist(histo2, height);


    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
    free_matrice(matrice , width);

     //show_image("../image4.bmp");
    return 0;
}
