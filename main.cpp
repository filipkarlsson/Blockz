#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include "var.h"
#include "TetrisForm.h"
#include "func.h"
#include "timer.h"

int main ( int argc, char** argv )
{
load_files();
init();

TetrisForm tet(round(SCREEN_WIDTH/2, BLOCK_SIZE) ,SCREEN_HEIGHT - BLOCK_SIZE, false, 'I');

all_blocks.push_back(tet);

//The frame rate regulator
Timer fps;

    // program main loop
    bool done = false;
    while (!done)
    {
        fps.start(); //Start fps timer
        // message processing loop

        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;


                    if(event.key.keysym.sym == SDLK_SPACE)
                    {
                        TetrisForm temp(round(SCREEN_WIDTH/2, BLOCK_SIZE), 0, true, random_block());

                        all_blocks.push_back(temp);
                    }
                    break;
                }
            } // end switch


        //handle input for tetris blocks
        for(unsigned int i=0; i < all_blocks.size(); i++)
        {
        all_blocks[i].handle_input();
        }

//all_blocks[0].handle_input();


        } // end of message processing

        //move tetris blocks down

        for(unsigned int i=0; i < all_blocks.size(); i++)
        {
        all_blocks[i].move();
        }
        //all_blocks[0].move();

        // DRAWING STARTS HERE
        //all_blocks[index].print();
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 250, 250, 250));

        //draw tetrs blocks to screen

        for(unsigned int i=0; i < all_blocks.size(); i++)
        {
        all_blocks[i].draw();
        }


        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        // finally, update the screen :)
        SDL_Flip(screen);

    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
