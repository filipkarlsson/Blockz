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

int main ( int argc, char** argv )
{

    TetrisForm temp(100, 100, true, random_block());
    all_blocks.push_back(temp);

    TetrisForm temp1(100, 400, false, random_block());
    all_blocks.push_back(temp1);

//TetrisForm test(100, 0, 'J');
    init();
    // initialize SDL video



    // program main loop
    bool done = false;
    while (!done)
    {
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
                        TetrisForm temp(100, 100, true, random_block());
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
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        //draw tetrs blocks to screen

        for(unsigned int i=0; i < all_blocks.size(); i++)
        {
        all_blocks[i].draw();
        }

        // finally, update the screen :)
        SDL_Flip(screen);

    } // end main loop

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
