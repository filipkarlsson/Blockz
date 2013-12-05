#ifndef FUNC_H
#define FUNC_H
#include <SDL/SDL.h>
char random_block();
bool load_files();
bool init();
bool check_collision( SDL_Rect A, SDL_Rect B );
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
int SDL_CollideBoundingBox(SDL_Rect a , SDL_Rect b);
int col_x(SDL_Rect a , SDL_Rect b);
int col_y(SDL_Rect a , SDL_Rect b);
int coll_left(SDL_Rect a , SDL_Rect b);
int coll_right(SDL_Rect a , SDL_Rect b);
bool free_move_right(SDL_Rect a, SDL_Rect b);
bool free_move_left(SDL_Rect a, SDL_Rect b);
//int random_pos(int random);
int round(int x, int f);
#endif // FUNC_H
