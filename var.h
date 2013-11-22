#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED
#include <vector>
#include <SDL/SDL.h>
#include "TetrisForm.h"
extern const int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP;

extern SDL_Event event;
extern SDL_Surface* screen;

extern const int BLOCK_SIZE;


extern std::vector<TetrisForm> all_blocks;
/*extern TTF_Font *font;
extern SDL_Color textColor;*/



#endif // VAR_H_INCLUDED
