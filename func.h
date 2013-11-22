#ifndef FUNC_H
#define FUNC_H
#include <SDL/SDL.h>
char random_block();
bool init();
bool check_collision( SDL_Rect A, SDL_Rect B );
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b);
#endif // FUNC_H
