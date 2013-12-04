#include <SDL2/SDL.h>
#include <vector>
#include "var.h"
#include "TetrisForm.h"

SDL_Surface* screen;
SDL_Surface* block_pic[8];
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 16;
const int FRAMES_PER_SECOND = 60;

SDL_Event event;

const int BLOCK_SIZE = 30;

extern const int GREEN = 0;
extern const int PINK = 1;
extern const int UBUNTU = 2;
extern const int VIOLET = 3;
extern const int YELLOW = 4;
extern const int TURQUOISE = 5;
extern const int RED = 6;

std::vector<TetrisForm> all_blocks;
