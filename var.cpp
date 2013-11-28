#include <SDL2/SDL.h>
#include <vector>
#include "var.h"
#include "TetrisForm.h"

SDL_Surface* screen;
const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 16;
const int FRAMES_PER_SECOND = 40;

SDL_Event event;

const int BLOCK_SIZE = 30;


std::vector<TetrisForm> all_blocks;
