//
// Created by adrien.duot on 10/25/18.
//

#include "Load_Image.h"
#include "Toolbox_SDL.h"



Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}



void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}




void Grissification(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    for(int x =0; x < width;++x)
    {
        for(int y=0; y < height;++y)
        {
            //Get the pixel value.
            Uint32 pixel = get_pixel(image_surface, x, y);

            //Get the RGB values of the pixel.
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

            //Compute the weighted average of the RGB values:
            Uint8 average = 0.3 *r + 0.59*g + 0.11*b;

            //Update the RGB values by using this average (r = g = b = average).
            r = g = b = average;

            //Get the new pixel value from the new RGB values.
            pixel = SDL_MapRGB(image_surface->format, r, g, b);

            //Put the new pixel value on the surface.
            put_pixel(image_surface, x, y, pixel);
        }
    }
}

void Binarization(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    for(int x =0; x < width;++x)
    {
        for(int y=0; y < height;++y)
        {
            //Get the pixel value.
            Uint32 pixel = get_pixel(image_surface, x, y);

            //Get the RGB values of the pixel.
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

            //Compute the weighted average of the RGB values:
            Uint8 average = 0;

            if ( 0.3 *r + 0.59*g + 0.11*b >= 122)
            {
                average = 255 ;
            }



            //Update the RGB values by using this average (r = g = b = average).
            r = g = b = average;

            //Get the new pixel value from the new RGB values.
            pixel = SDL_MapRGB(image_surface->format, r, g, b);

            //Put the new pixel value on the surface.
            put_pixel(image_surface, x, y, pixel);
        }
    }
}

void show_image(char* path)
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    // TODO: Initialize the SDL
    init_sdl();

    image_surface = load_image(path);
    // TODO: Display the image.
    screen_surface = display_image(image_surface);

    // TODO: Wait for a key to be pressed.
    wait_for_keypressed();

    Grissification(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();
    Binarization(image_surface);
    update_surface(screen_surface,image_surface);
    wait_for_keypressed();
    // TODO: Free the image surface.

    SDL_FreeSurface(image_surface);
    // TODO: Free the screen surface.
    SDL_FreeSurface(screen_surface);
}




