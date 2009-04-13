#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "constants.h"
#include "bird.h"
#include "timer.h"
#include "functions.h"
#include "globals.h"

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //The bird that will be used
    Bird bird;

    //The frame rate regulator
    Timer fps;

    //Timer to keep track of time before the bird flies off
    Timer fly_away_timer;

    int start_time = 0;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Sets the clips
    set_clips();

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the dot
            bird.handle_event();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Start the timer and store the time that the bird started flying
        if(fly_away_timer.is_started()==false)
        {
            fly_away_timer.start();
            start_time = fly_away_timer.get_ticks();
        }

        //Set the flag to fly away when it's time
        if( fly_away_timer.get_ticks() - start_time > FLY_AWAY_TIME )
        {
            fly_away_flag = true;
        }

        //Move the bird
        bird.move();

        //Fill the screen with a background color
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x64, 0x00 ) );

        //Show the dot on the screen
        bird.show();

        //Apply the images to the screen
        apply_surface( 0, 200, message, screen );

        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    //Clean up
    clean_up();

    return 0;
}
