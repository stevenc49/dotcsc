//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"

//The surfaces
SDL_Surface *sprite_sheet = NULL;
SDL_Surface *reversed_sprite_sheet = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };

//Clips from the sprites sheet
SDL_Rect flying_clip[ 3 ];
SDL_Rect shot_clip;
SDL_Rect falling_clip;

//If true, bird can fly off the screen
bool fly_away_flag;
