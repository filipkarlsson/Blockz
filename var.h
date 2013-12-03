#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED
#include <vector>
#include <SDL/SDL.h>
#include "TetrisForm.h"
extern const int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, FRAMES_PER_SECOND;

extern SDL_Event event;
extern SDL_Surface* screen;

extern SDL_Surface* block_2;

extern const int BLOCK_SIZE;


extern std::vector<TetrisForm> all_blocks;
/*extern TTF_Font *font;
extern SDL_Color textColor;*/



#endif // VAR_H_INCLUDED
