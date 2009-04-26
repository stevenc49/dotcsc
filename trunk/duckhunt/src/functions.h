#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//File Loader
SDL_Surface *load_image( std::string filename );

//Surface blitter
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

//Initialization
bool init();

//File loading
bool load_files();

//Clean up
void clean_up();

//Specifies where clips are located on the sprite sheet
void set_clips();

//Functions to flip images
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
SDL_Surface *flip_surface( SDL_Surface *surface, int flags );

#endif
