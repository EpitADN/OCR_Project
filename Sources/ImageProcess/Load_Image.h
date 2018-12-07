//
// Created by adrien.duot on 10/25/18.
//

#ifndef IMAGE_PROCESS_LOAD_IMAGE_H
#define IMAGE_PROCESS_LOAD_IMAGE_H

#include <err.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "../Interface/Toolbox_SDL.h"

#include "SDL/SDL_image.h"
#include "SDL/SDL_video.h"

void Grissification(SDL_Surface* image_surface);

void Binarization(SDL_Surface* image_surface);

void show_image(char* path );


#endif //IMAGE_PROCESS_LOAD_IMAGE_H
