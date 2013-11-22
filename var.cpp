#include <SDL2/SDL.h>
#include <vector>
#include "var.h"
#include "TetrisForm.h"

SDL_Surface* screen;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 16;

SDL_Event event;

const int BLOCK_SIZE = 30;


std::vector<TetrisForm> all_blocks;
