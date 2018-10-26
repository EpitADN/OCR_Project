//
// Created by adrien.duot on 10/25/18.
//

#ifndef IMAGE_PROCESS_LOAD_IMAGE_H
#define IMAGE_PROCESS_LOAD_IMAGE_H

#include <err.h>
#include <stdlib.h>
#include "SDL/SDL.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_video.h"


void init_sdl();

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

void wait_for_keypressed();

void SDL_FreeSurface(SDL_Surface *surface);


Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y);

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

void update_surface(SDL_Surface* screen, SDL_Surface* image);


void Grissification(SDL_Surface* image_surface);

void Binarization(SDL_Surface* image_surface);

void show_image(char* path );


#endif //IMAGE_PROCESS_LOAD_IMAGE_H