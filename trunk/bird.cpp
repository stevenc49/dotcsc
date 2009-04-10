//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "constants.h"
#include "bird.h"
#include "functions.h"
#include "globals.h"

Bird::Bird()
{
    bird_status = ALIVE;

    //Initialize the offsets
    bird.x = 0;
    bird.y = 0;

    //Set the bird's dimensions
    bird.w = BIRD_WIDTH;
    bird.h = BIRD_HEIGHT;

    //Initialize the velocity
    xVel = BIRD_WIDTH / 2;
    yVel = BIRD_HEIGHT / 2;

    frame = 0;
}

void Bird::handle_event()
{
    //The mouse offsets
    int x = 0, y = 0;

    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //Get the mouse offsets
        x = event.button.x;
        y = event.button.y;

        //If the mouse is over the bird
        if( ( x > bird.x ) && ( x < bird.x + bird.w ) && ( y > bird.y ) && ( y < bird.y + bird.h ) )
        {
            //Change status to SHOT
            bird_status = SHOT;

            xVel = 0;
            yVel = 0;

            //Reset the bgcolor, show the animation of the bird getting shot
            //and update the screen
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x64, 0x00 ) );
            show();
            SDL_Flip( screen );

            //Wait 2 seconds so user sees the animation of the bird getting shot
            SDL_Delay( 1200 );

            //Change status to SHOT
            bird_status = FALLING;

            yVel += BIRD_HEIGHT;
        }
    }
}

void Bird::move()
{
    if( bird_status == ALIVE)
    {
        //Move the bird left or right
        bird.x += xVel;

        //If thebird went too far to the left or right
        if( ( bird.x < 0 ) || ( bird.x + BIRD_WIDTH > FLYABLE_AREA_X ) )
        {
            //move back
            bird.x -= xVel;

            //reverse direction
            xVel = -xVel;
        }

        //Move the bird up or down
        bird.y += yVel;

        //if the bird is not allowed to fly away
        if( fly_away_flag == false )
        {
            //If the bird went too far up or down
            if( ( bird.y < 0 ) || ( bird.y + BIRD_HEIGHT > FLYABLE_AREA_Y ) )
            {
                //move back
                bird.y -= yVel;

                //reverse direction
                yVel = -yVel;
            }
        }
    }
    else if( bird_status == FALLING )
    {
        //Move the bird up or down
        bird.y += yVel;
    }
}

void Bird::show()
{
    if(bird_status == ALIVE)
    {
        //Move to the next frame in the animation
        frame++;

        //Loop the animation
        if(frame >= 3)
        {
            frame = 0;
        }

        //Choose which surface to show depending on the bird's direction
        if(xVel>0)
            apply_surface( bird.x, bird.y, sprite_sheet, screen, &flying_clip[ frame ] );
        else
            apply_surface( bird.x, bird.y, reversed_sprite_sheet, screen, &flying_clip[ frame ] );
    }
    else if(bird_status == SHOT)
    {
        apply_surface( bird.x, bird.y, sprite_sheet, screen, &shot_clip );;
    }
    else if(bird_status == FALLING)
    {
        apply_surface( bird.x, bird.y, sprite_sheet, screen, &falling_clip );;
    }
}

