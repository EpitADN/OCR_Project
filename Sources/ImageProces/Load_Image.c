//
// Created by adrien.duot on 10/25/18.
//

#include "Load_Image.h"



void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}


SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}


SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
             img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}


Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
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

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
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




