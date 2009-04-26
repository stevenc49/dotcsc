#ifndef GLOBALS_H
#define GLOBALS_H

//The header
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "timer.h"
#include <string>


using namespace std;

//The surfaces
extern SDL_Surface *sprite_sheet;
extern SDL_Surface *reversed_sprite_sheet;
extern SDL_Surface *screen;
extern SDL_Surface *message;

//The event structure
extern SDL_Event event;

//The font
extern TTF_Font *font;

//The color of the font
extern SDL_Color textColor;

//Stores the clips
extern SDL_Rect flying_clip[ 3 ];
extern SDL_Rect shot_clip;
extern SDL_Rect falling_clip;

//If true, bird can fly off the screen
extern bool fly_away_flag;

//Flip flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

#endif
