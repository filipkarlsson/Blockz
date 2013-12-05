#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDED
#include <vector>
#include <SDL/SDL.h>
#include "TetrisForm.h"
extern const int SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, FRAMES_PER_SECOND;

extern SDL_Event event;
extern SDL_Surface* screen;

extern SDL_Surface* block_pic[8];

extern const int BLOCK_SIZE;

extern const int GREEN;
extern const int PINK;
extern const int UBUNTU;
extern const int VIOLET;
extern const int YELLOW;
extern const int TURQUOISE;
extern const int RED;
extern const int GROUND;

extern const int NORMAL_SPEED;
extern const int HIGH_SPEED;


extern std::vector<TetrisForm> all_blocks;
/*extern TTF_Font *font;
extern SDL_Color textColor;*/



#endif // VAR_H_INCLUDED
