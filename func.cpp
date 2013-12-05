#include <ctime>
#include <cstdlib>
#include <SDL/SDL.h>
#include <string>
#include "var.h"



bool init()
{
   //Initialize all SDL subsystems
   if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
   {
       return false;
   }

   //Set up the screen
   screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);

   //If there was an error in setting up the screen
   if( screen == NULL )
   {
       return false;
   }

/*if( TTF_Init() == -1 )
{
return false;
}
*/

   //Set the window caption
   SDL_WM_SetCaption( "BOB", NULL );

   //If everything initialized fine
   return true;
}

//returns a random char representing one of seven teris blocks
char random_block()
{
   srand(time(NULL));

   char letter;
    int random;
    random = rand() % 7;

    if(random == 0)
    {
        letter = 'I';
    }

    else if (random == 1)
    {
        letter = 'O';
    }

    else if (random == 2)
    {
        letter = 'S';
    }

    else if (random == 3)
    {
        letter = 'Z';
    }

    else if (random == 4)
    {
        letter = 'L';
    }

    else if (random == 5)
    {
        letter = 'J';
    }

    else if (random == 6)
    {
        letter = 'T';
    }

    return letter;
}

SDL_Surface *load_image( std::string filename )
{
   //The image that's loaded
   SDL_Surface* loadedImage = NULL;

   //The optimized surface that will be used
   SDL_Surface* optimizedImage = NULL;

   //Load the image
   loadedImage = SDL_LoadBMP( filename.c_str() );

   //If the image loaded
   if( loadedImage != NULL )
   {
       //Create an optimized surface
       optimizedImage = SDL_DisplayFormat( loadedImage );

       //Free the old surface
       SDL_FreeSurface( loadedImage );

       //If the surface was optimized
       if( optimizedImage != NULL )
       {
           //Color key surface
           SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 200, 0, 200 ) );
       }
   }

   //Return the optimized surface
   return optimizedImage;
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
   //Holds offsets
   SDL_Rect offset;

   //Get offsets
   offset.x = x;
   offset.y = y;

   //Blit
   SDL_BlitSurface( source, clip, destination, &offset );
}

int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;	//just checking if their
	if(b.x > a.x + a.w)	return 0;	//bounding boxes even touch

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	return 1;				//bounding boxes intersect
}

int coll_left(SDL_Rect a , SDL_Rect b)
{
    if(b.x + b.w < a.x +1 )	return 0;	//just checking if their
	if(b.x+1 > a.x + a.w)	return 0;	//bounding boxes even touch
	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;
	return 1;				//bounding boxes intersect
}


int coll_right(SDL_Rect a , SDL_Rect b)
{
	//if((b.x + b.w <= a.x + 1) and (b.x + b.w + 1 > a.x - BLOCK_SIZE))	return 0;	//just checking if their
	if(b.x - b.w < a.x)	return 0;	//just checking if their
	if(b.x > a.x + a.w)	return 0;	//bounding boxes even touch

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;
	return 1;					//bounding boxes intersect
}

int col_y(SDL_Rect a , SDL_Rect b)
{
    //bounding boxes even touch

	if(b.y + b.h < a.y)	return 0;
	if(b.y > a.y + a.h)	return 0;

	if(b.x + b.w < a.x+1)	return 0;	//just checking if their
	if(b.x +1 > a.x + a.w)	return 0;

	return 1;				//bounding boxes intersect
}

int col_x(SDL_Rect a , SDL_Rect b)
{
	if(b.x + b.w < a.x)	return 0;	//just checking if their
	if(b.x > a.x + a.w)	return 0;	//bounding boxes even touch

	return 1;				//bounding boxes intersect
}

bool free_move_right(SDL_Rect a, SDL_Rect b)
{

    if((a.x + a.w == b.x) and (a.y + a.h - 11 > b.y) and (a.y < b.y + b.h - 5)) return false;
    return true;

}

bool free_move_left(SDL_Rect a, SDL_Rect b)
{
     if((a.x == b.x + b.w) and (a.y + a.h - 11 > b.y) and (a.y < b.y + b.h - 5)) return false;
    return true;
}


void load_files()
{

block_pic[0] = SDL_LoadBMP("Spirit_green-block-2.1.bmp");
block_pic[1] = SDL_LoadBMP("Spirit_pink-block-2.1.bmp");
block_pic[2] = SDL_LoadBMP("Spirit_ubuntu-block-2.1.bmp");
block_pic[3] = SDL_LoadBMP("Spirit_violet-block-2.1.bmp");
block_pic[4] = SDL_LoadBMP("Spirit_yellow-block-2.1.bmp");
block_pic[5] = SDL_LoadBMP("Spirit_turquoise-block-2.1.bmp");
block_pic[6] = SDL_LoadBMP("Spirit_red-block-2.1.bmp");

}



void clean()
{
}

/*int random_pos(int random)
{
srand(time(NULL));
random = rand() % random;


return random;
}
*/
int round(int x, int f)
{
    int p = x/f;

    return p * f;
}






