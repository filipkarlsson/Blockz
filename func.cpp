#include <ctime>
#include <cstdlib>
#include <SDL/SDL.h>
#include <string>
#include "var.h"

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


bool check_collision( SDL_Rect A, SDL_Rect B )
{
   //The sides of the rectangles
   int leftA, leftB;
   int rightA, rightB;
   int topA, topB;
   int bottomA, bottomB;

   //Calculate the sides of rect A
   leftA = A.x;
   rightA = A.x + A.w;
   topA = A.y;
   bottomA = A.y + A.h;

   //Calculate the sides of rect B
   leftB = B.x;
   rightB = B.x + B.w;
   topB = B.y;
   bottomB = B.y + B.h;

   //If any of the sides from A are outside of B
   if( bottomA <= topB )
   {
       return false;
   }

   if( topA >= bottomB )
   {
       return false;
   }

   if( rightA <= leftB )
   {
       return false;
   }

   if( leftA >= rightB )
   {
       return false;
   }

   //If none of the sides from A are outside B
   return true;
}


bool init()
{
   //Initialize all SDL subsystems
   if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
   {
       return false;
   }

   //Set up the screen
   screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

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

void load_files()
{
/*menyBild = load_image("meny.bmp");
mark = load_image("mark.bmp");
stjarna = load_image("star.bmp");
kanon = load_image("kanon.bmp");
skott = load_image("shot.bmp");
start = load_image("start.bmp");
font = TTF_OpenFont( "trado.ttf", 28 );*/
}



void clean()
{
}





