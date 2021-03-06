#include "TetrisForm.h"
#include <SDL/SDL.h>
#include <iostream>
#include <cmath>
#include "var.h"
#include "func.h"
TetrisForm::TetrisForm(int x, int y, bool falling, char typ)
{
    //ctor
    xpos = x;
    ypos = y;
    type = typ;
    if(falling)
    {
    yspeed = NORMAL_SPEED;
    }
    else
    {
    yspeed = 0;
    }
    rotation = 1;

    id = all_blocks.size();

    in_game = true;
    below = false;

    ground = false;

}
TetrisForm::TetrisForm(int x, int y, bool falling, char typ, bool ground_type)
{
    //ctor
    xpos = x;
    ypos = y;
    type = typ;
    if(falling)
    {
    yspeed = NORMAL_SPEED;
    }
    else
    {
    yspeed = 0;
    }
    rotation = 1;

    id = all_blocks.size();

    in_game = true;
    below = false;

    if(ground_type) ground = true;
    else ground = false;

}

TetrisForm::~TetrisForm()
{
    //dtor
}


void TetrisForm::turn()
{
    rotation += 1;

    if (rotation == 5)
    {
        rotation = 1;
    }
return;
}

void TetrisForm::move_left()
{
    xpos += BLOCK_SIZE;

    return;

}
void TetrisForm::move_right()
{
    xpos -=  BLOCK_SIZE;

    return;
}

void TetrisForm::handle_input()
{
    if(yspeed>0)
    {
        bool free_to_move_left  = true;
        bool free_to_move_right  = true;
        bool free_to_move = true;

        for(unsigned int i=0; i < all_blocks.size(); i++)
            {
                for(int a=0; a<=3; a++)
                {
                    for(int b=0; b<=3; b++)
                    {
                        if((rects[a].w == BLOCK_SIZE) and (all_blocks[i].rects[b].w == BLOCK_SIZE)){ //bug 1

                            if((free_move_left(rects[a], all_blocks[i].rects[b]) == false) and (id != all_blocks[i].id))
                            {
                                free_to_move_left = false;
                                //std::cout <<"x: "<< rects[a].h << " w:" << rects[a].w<<std::endl;

                            }
                            if((free_move_right(rects[a], all_blocks[i].rects[b]) == false) and (id != all_blocks[i].id))
                            {
                                free_to_move_right = false;

                            }
                            if((col_y(rects[a], all_blocks[i].rects[b]) == 1) and (id != all_blocks[i].id))
                            {
                                free_to_move = false;

                            }
                        }
                    }
                }
            }

    if((event.type == SDL_KEYDOWN) and (free_to_move_left))
	{
		switch( event.key.keysym.sym )
        {
            case SDLK_LEFT: xpos -= BLOCK_SIZE; break;
           default: break;
        }
	}

	if((event.type == SDL_KEYDOWN) and (free_to_move_right))
	{
		switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: xpos += BLOCK_SIZE; break;
           default: break;
        }
	}

	if((event.type == SDL_KEYDOWN) and (free_to_move))
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: TetrisForm::turn(); break;
            case SDLK_DOWN: yspeed = HIGH_SPEED; break;
           default: break;
        }
    }

	if((event.type == SDL_KEYUP) and (free_to_move))
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_DOWN: yspeed = NORMAL_SPEED; break;
           default: break;
        }
    }
	}
return;
}

void TetrisForm::move()
{

    if(yspeed>0)
    {
        bool new_block = false;
         for(unsigned int i=0; i < all_blocks.size(); i++)
            {
                for(int a=0; a<=3; a++)
                {
                    for(int b=0; b<=3; b++)
                    {
                        if((col_y(rects[a], all_blocks[i].rects[b]) == 1) and (id != all_blocks[i].id) and all_blocks[i].in_game)
                        {
                            if((rects[a].w == BLOCK_SIZE) and (all_blocks[i].rects[b].w == BLOCK_SIZE)){ //bug 1
                                //std::cout << "id: " << id << "  col with id: "<< all_blocks[i].id << " a:" <<a<<" b:"<<b<<" i:"<<i <<std::endl;
                                //std::cout << "active block: (" << xpos << ", " << ypos<< ")  rect: (" << rects[a].x << ", " << rects[a].y<<") W:"<< rects[a].w<<" collides with: (" << all_blocks[i].rects[b].x<<", "<<all_blocks[i].rects[b].y <<") "<<std::endl;

                                new_block=true;
                                yspeed = 0;



                            }


                        }

                        if(ypos>SCREEN_HEIGHT){

                                below=true;
                        }


                    }
                }

            }

/*if((ypos > SCREEN_HEIGHT) and in_game)
{
    new_block = true;
    in_game = false;

}*/
if(new_block and in_game){

    TetrisForm temp(round(random_pos(), BLOCK_SIZE), 0, true, random_block());
    all_blocks.push_back(temp);

}
else if (below and in_game) {
    in_game = false;
    TetrisForm temp(round(random_pos(), BLOCK_SIZE), 0, true, random_block());
    all_blocks.push_back(temp);

    }

    }


    ypos += yspeed;

    if(yspeed == 0)
    {
        ypos = round(ypos, BLOCK_SIZE);

    }

}



void TetrisForm::draw()
{
   //Reset all blocks
   int x, i = 0;
   while(x < 4)
   {
       i = 0;
       while(i<4)
       {
           blocks[x][i] = false;
           i++;
       }
       x++;
   }
//set blocks after type ('O', 'I', 'S', 'Z', 'L', 'J', 'T')
    if(type=='O')
    {
        blocks[2][1] = true;
        blocks[1][1] = true;
        blocks[1][2] = true;
        blocks[2][2] = true;

    }

    else if(type == 'I')
    {
        if( (rotation == 1) or (rotation == 3) )
        {
            blocks[0][1] = true;
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
        }

       else if( (rotation == 2) or (rotation == 4) )
        {
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
            blocks[2][3] = true;
        }


    }

    else if(type == 'S')
    {
        if( (rotation == 1) or (rotation == 3) )
        {
            blocks[1][2] = true;
            blocks[2][2] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
        }

       else if( (rotation == 2) or (rotation == 4) )
        {
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
            blocks[3][2] = true;
        }


    }

    else if(type == 'Z')
    {
        if( (rotation == 1) or (rotation == 3) )
        {
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
            blocks[3][2] = true;
        }

       else if( (rotation == 2) or (rotation == 4) )
        {
            blocks[3][0] = true;
            blocks[3][1] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;

        }
    }

    else if(type == 'L')
    {
        if(rotation == 1 )
        {
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[1][2] = true;
            blocks[3][1] = true;
        }

       else if(rotation == 2)
        {
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
            blocks[3][2] = true;
        }

        else if(rotation == 3)
        {
            blocks[3][0] = true;
            blocks[3][1] = true;
            blocks[2][1] = true;
            blocks[1][1] = true;
        }
        else if(rotation == 4)
        {
            blocks[1][0] = true;
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
        }

    }

    else if(type == 'J')
    {
        if(rotation == 1 )
        {
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
            blocks[3][2] = true;
        }

       else if(rotation == 2)
        {
            blocks[2][0] = true;
            blocks[3][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
        }

        else if(rotation == 3)
        {
            blocks[1][0] = true;
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
        }
        else if(rotation == 4)
        {
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
            blocks[1][2] = true;
        }

    }

    else if(type == 'T')
    {
        if(rotation == 1 )
        {
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
            blocks[3][1] = true;
        }

       else if(rotation == 2)
        {
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
            blocks[2][2] = true;
        }

        else if(rotation == 3)
        {
            blocks[2][0] = true;
            blocks[1][1] = true;
            blocks[2][1] = true;
            blocks[3][1] = true;
        }
        else if(rotation == 4)
        {
            blocks[1][1] = true;
            blocks[2][0] = true;
            blocks[2][1] = true;
            blocks[2][2] = true;
        }

    }


    //Lägg till alla bitar

// Set sdl_rect after blocks

//(2,1) är alltid aktiv
//rects[3] nästa BLOCK_SIZE
if(blocks[0][0])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-(2 * BLOCK_SIZE);
rects[0].y = ypos-BLOCK_SIZE;
blocks[0][0] = false;
}
else if(blocks[0][1])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-(2 * BLOCK_SIZE);
rects[0].y = ypos;
blocks[0][1] = false;
}
else if(blocks[0][2])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-(2 * BLOCK_SIZE);
rects[0].y = ypos+BLOCK_SIZE;
blocks[0][2] = false;
}
else if(blocks[0][3])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-(2 * BLOCK_SIZE);
rects[0].y = ypos+(2 * BLOCK_SIZE);
blocks[0][3] = false;
}

else if(blocks[1][0])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-BLOCK_SIZE;
rects[0].y = ypos-BLOCK_SIZE;
blocks[1][0] = false;
}
else if(blocks[1][1])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-BLOCK_SIZE;
rects[0].y = ypos;
blocks[1][1] = false;
}
else if(blocks[1][2])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-BLOCK_SIZE;
rects[0].y = ypos+BLOCK_SIZE;
blocks[1][2] = false;
}
else if(blocks[1][3])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos-BLOCK_SIZE;
rects[0].y = ypos+(2 * BLOCK_SIZE);
blocks[1][3] = false;
}

else if(blocks[2][0])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos;
rects[0].y = ypos-BLOCK_SIZE;
blocks[2][0] = false;
}
else if(blocks[2][1])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos;
rects[0].y = ypos;
blocks[2][1]=false;
}
else if(blocks[2][2])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos;
rects[0].y = ypos+BLOCK_SIZE;
blocks[2][2] = false;
}
else if(blocks[2][3])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos;
rects[0].y = ypos+ (2 * BLOCK_SIZE);
blocks[2][3] = false;
}

else if(blocks[3][0])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos+BLOCK_SIZE;
rects[0].y = ypos-BLOCK_SIZE;
blocks[3][0] = false;
}
else if(blocks[3][1])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos+BLOCK_SIZE;
rects[0].y = ypos;
blocks[3][1] = false;
}
else if(blocks[3][2])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos+BLOCK_SIZE;
rects[0].y = ypos+BLOCK_SIZE;
blocks[3][2] = false;
}
else if(blocks[3][3])
{
rects[0].h  = BLOCK_SIZE;
rects[0].w  = BLOCK_SIZE;
rects[0].x = xpos+BLOCK_SIZE;
rects[0].y = ypos+ (2 * BLOCK_SIZE);
blocks[3][3] = false;
}


//rects[1] nästa 15
if(blocks[0][0])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos - (2 * BLOCK_SIZE);
rects[1].y = ypos-BLOCK_SIZE;
blocks[0][0] = false;
}
else if(blocks[0][1])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos - (2 * BLOCK_SIZE);
rects[1].y = ypos;
blocks[0][1] = false;
}
else if(blocks[0][2])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-(2 * BLOCK_SIZE);
rects[1].y = ypos+BLOCK_SIZE;
blocks[0][2] = false;
}
else if(blocks[0][3])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-(2 * BLOCK_SIZE);
rects[1].y = ypos+(2 * BLOCK_SIZE);
blocks[0][3] = false;
}

else if(blocks[1][0])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-BLOCK_SIZE;
rects[1].y = ypos-BLOCK_SIZE;
blocks[1][0] = false;
}
else if(blocks[1][1])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-BLOCK_SIZE;
rects[1].y = ypos;
blocks[1][1] = false;
}
else if(blocks[1][2])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-BLOCK_SIZE;
rects[1].y = ypos+BLOCK_SIZE;
blocks[1][2] = false;
}
else if(blocks[1][3])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos-BLOCK_SIZE;
rects[1].y = ypos+(2 * BLOCK_SIZE);
blocks[1][3] = false;
}

else if(blocks[2][0])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos;
rects[1].y = ypos-BLOCK_SIZE;
blocks[2][0] = false;
}
else if(blocks[2][1])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos;
rects[1].y = ypos;
blocks[2][1]=false;
}
else if(blocks[2][2])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos;
rects[1].y = ypos+BLOCK_SIZE;
blocks[2][2] = false;
}
else if(blocks[2][3])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos;
rects[1].y = ypos+(2 * BLOCK_SIZE);
blocks[2][3] = false;
}

else if(blocks[3][0])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos+BLOCK_SIZE;
rects[1].y = ypos-BLOCK_SIZE;
blocks[3][0] = false;
}
else if(blocks[3][1])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos+BLOCK_SIZE;
rects[1].y = ypos;
blocks[3][1] = false;
}
else if(blocks[3][2])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos+BLOCK_SIZE;
rects[1].y = ypos+BLOCK_SIZE;
blocks[3][2] = false;
}
else if(blocks[3][3])
{
rects[1].h  = BLOCK_SIZE;
rects[1].w  = BLOCK_SIZE;
rects[1].x = xpos+BLOCK_SIZE;
rects[1].y = ypos+(2 * BLOCK_SIZE);
blocks[3][3] = false;
}


//rects[2] nästa 15
if(blocks[0][0])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-(2 * BLOCK_SIZE);
rects[2].y = ypos-BLOCK_SIZE;
blocks[0][0] = false;
}
else if(blocks[0][1])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-(2 * BLOCK_SIZE);
rects[2].y = ypos;
blocks[0][1] = false;
}
else if(blocks[0][2])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-(2 * BLOCK_SIZE);
rects[2].y = ypos+BLOCK_SIZE;
blocks[0][2] = false;
}
else if(blocks[0][3])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-(2 * BLOCK_SIZE);
rects[2].y = ypos+(2 * BLOCK_SIZE);
blocks[0][3] = false;
}

else if(blocks[1][0])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-BLOCK_SIZE;
rects[2].y = ypos-BLOCK_SIZE;
blocks[1][0] = false;
}
else if(blocks[1][1])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-BLOCK_SIZE;
rects[2].y = ypos;
blocks[1][1] = false;
}
else if(blocks[1][2])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-BLOCK_SIZE;
rects[2].y = ypos+BLOCK_SIZE;
blocks[1][2] = false;
}
else if(blocks[1][3])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos-BLOCK_SIZE;
rects[2].y = ypos+(2 * BLOCK_SIZE);
blocks[1][3] = false;
}


else if(blocks[2][0])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos;
rects[2].y = ypos-BLOCK_SIZE;
blocks[2][0] = false;
}
else if(blocks[2][1])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos;
rects[2].y = ypos;
blocks[2][1]=false;
}
else if(blocks[2][2])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos;
rects[2].y = ypos+BLOCK_SIZE;
blocks[2][2] = false;
}
else if(blocks[2][3])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos;
rects[2].y = ypos+(2 * BLOCK_SIZE);
blocks[2][3] = false;
}

else if(blocks[3][0])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos+BLOCK_SIZE;
rects[2].y = ypos-BLOCK_SIZE;
blocks[3][0] = false;
}
else if(blocks[3][1])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos+BLOCK_SIZE;
rects[2].y = ypos;
blocks[3][1] = false;
}
else if(blocks[3][2])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos+BLOCK_SIZE;
rects[2].y = ypos+BLOCK_SIZE;
blocks[3][2] = false;
}
else if(blocks[3][3])
{
rects[2].h  = BLOCK_SIZE;
rects[2].w  = BLOCK_SIZE;
rects[2].x = xpos+BLOCK_SIZE;
rects[2].y = ypos+ (2 * BLOCK_SIZE);
blocks[3][3] = false;
}

//rects[3] nästa BLOCK_SIZE
if(blocks[0][0])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-(2 * BLOCK_SIZE);
rects[3].y = ypos-BLOCK_SIZE;
blocks[0][0] = false;
}
else if(blocks[0][1])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-(2 * BLOCK_SIZE);
rects[3].y = ypos;
blocks[0][1] = false;
}
else if(blocks[0][2])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-(2 * BLOCK_SIZE);
rects[3].y = ypos+BLOCK_SIZE;
blocks[0][2] = false;
}
else if(blocks[0][3])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos- (2 * BLOCK_SIZE);
rects[3].y = ypos+ (2 * BLOCK_SIZE);
blocks[0][3] = false;
}

else if(blocks[1][0])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-BLOCK_SIZE;
rects[3].y = ypos-BLOCK_SIZE;
blocks[1][0] = false;
}
else if(blocks[1][1])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-BLOCK_SIZE;
rects[3].y = ypos;
blocks[1][1] = false;
}
else if(blocks[1][2])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-BLOCK_SIZE;
rects[3].y = ypos+BLOCK_SIZE;
blocks[1][2] = false;
}
else if(blocks[1][3])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos-BLOCK_SIZE;
rects[3].y = ypos+(2 * BLOCK_SIZE);
blocks[1][3] = false;
}

else if(blocks[2][0])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos;
rects[3].y = ypos-BLOCK_SIZE;
blocks[2][0] = false;
}
else if(blocks[2][1])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos;
rects[3].y = ypos;
blocks[2][1]=false;
}
else if(blocks[2][2])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos;
rects[3].y = ypos+BLOCK_SIZE;
blocks[2][2] = false;
}
else if(blocks[2][3])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos;
rects[3].y = ypos + (2 * BLOCK_SIZE);
blocks[2][3] = false;

}

else if(blocks[3][0])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos+BLOCK_SIZE;
rects[3].y = ypos-BLOCK_SIZE;
blocks[3][0] = false;

}
else if(blocks[3][1])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos+BLOCK_SIZE;
rects[3].y = ypos;
blocks[3][1] = false;

}
else if(blocks[3][2])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos+BLOCK_SIZE;
rects[3].y = ypos+BLOCK_SIZE;
blocks[3][2] = false;

}
else if(blocks[3][3])
{
rects[3].h  = BLOCK_SIZE;
rects[3].w  = BLOCK_SIZE;
rects[3].x = xpos+BLOCK_SIZE;
rects[3].y = ypos+ (2 * BLOCK_SIZE);
blocks[3][3] = false;

}

//draw tetris block to scrren
SDL_Surface* block_p;
if(!ground)
{
if(type =='I') block_p = block_pic[TURQUOISE];
else if(type=='O') block_p = block_pic[RED];
else if(type=='S') block_p = block_pic[VIOLET];
else if(type=='L') block_p = block_pic[GREEN];
else if(type=='Z') block_p = block_pic[UBUNTU];
else if(type=='T') block_p = block_pic[YELLOW];
else if(type=='J') block_p = block_pic[PINK];
}
else block_p = block_pic[GROUND];

apply_surface( rects[0].x , rects[0].y, block_p, screen, NULL );
apply_surface( rects[1].x , rects[1].y, block_p, screen, NULL );
apply_surface( rects[2].x , rects[2].y, block_p, screen, NULL );
apply_surface( rects[3].x , rects[3].y, block_p, screen, NULL );
}



void TetrisForm::print()
{
    std::cout << "(" << xpos << ", " << ypos << ") " << type <<":" << rotation << std::endl;
}
