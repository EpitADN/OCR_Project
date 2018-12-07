#include <stdio.h>

#include "Load_Image.h"
#include "Segmentation.h"
#include "mainSegmentation.h"


char* mainsegmen(char * path ,T_Network* Network,char* Targets ) {


    SDL_Surface* image_surface = NULL;
    SDL_Surface* screen_surface = NULL;

    init_sdl();

    image_surface = load_image(path);

    //screen_surface = display_image(image_surface);


    //wait_for_keypressed();

    Grissification(image_surface);
    //update_surface(screen_surface,image_surface);
    //wait_for_keypressed();


    Binarization(image_surface);
    //update_surface(screen_surface,image_surface);
    //wait_for_keypressed();


/* 
load image
==============================================================
segmentation
*/

    // Retrieving Infos
    size_t width = (size_t)image_surface->w; // number of pixel in a ligne
    size_t height = (size_t)image_surface->h; // number of pixel in a collone
    int** matrice = creationarrays(image_surface);
    //printarray(matrice, 190 , 190);


    // Freeing SDL
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);


    // Allocating memory

    int* hicolonne = NULL;
    hicolonne = calloc(height, sizeof(int));
    if (hicolonne == NULL)
        err(1,"Calloc hicolonne");


    // Segmenting Image
    Histogrammification(matrice , width, height, hicolonne);

    // Allocating memory for lines list
    listofmatrix* Lines = NULL;
    Lines = malloc(sizeof(listofmatrix));
    if (Lines == NULL)
        err(1,"Calloc lines");

    // Creating Lists
    Listification(matrice , hicolonne ,width ,height , Lines);
    free(hicolonne);

    // Printing Lines
    /*while (list)
    {
        printarray(list->matrix , list->width , list->height);
        printf("\n");

        list = list->next;
    }*/


    // Past guard notes
    Lines = Lines->next;

    // Allocating memory for Char array
    listofmatrix* Chars = NULL;
    Chars = malloc(sizeof(listofmatrix));
    if (Chars == NULL)
        err(1,"Calloc Chars");

    // Processing
    characterisation(Lines , Chars);




    /*
    listofmatrix* current = Chars->next;
    while (current)
    {
        printarray(current->matrix , current->width , current->height);
        printf("\n");
        current = current->next;
    }
    */


    //scale(Chars, temp,(float) newx / Chars->height, (float)newy / Chars->width);



    free_matrice(matrice , height);
    free_listofmatrice(Lines);
    free_listofmatrice(Chars);

    //
    T_TrainingChar* temp = NULL;
    listofmatrix* current = Chars->next;
    size_t nbletter = 0;
    while (current)
    {
        nbletter+=1;
        current = current->next;
    }
    current = Chars->next;

    char* texte = NULL;
    texte = malloc((nbletter+1) * sizeof(char));
    int i= 0;
    while (current)
    {
        //allocationg
        temp = malloc(sizeof(T_TrainingChar));

        //fonction call
        scale(Chars, temp,28, 28);
        texte[i] = DryRun(Network , Targets, temp);

        //incrementation
        current = current->next;
        i+=1;

        //needed free
        free(temp->values);
        free(temp);
    }


    
    return texte;
}
