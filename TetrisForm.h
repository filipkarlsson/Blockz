#ifndef TETRISFORM_H
#define TETRISFORM_H
#include <SDL/SDL.h>

class TetrisForm
{
    public:
        TetrisForm(int x, int y, bool falling, char type);
        virtual ~TetrisForm();

        void turn();

        void move_left();
        void move_right();
        void handle_input();
        void move();

        void print();
        void draw();

    protected:
    private:
        int id;
        char type;
        bool blocks[4][4];
        SDL_Rect rects[4];
        int rotation;
        int xpos, ypos, xspeed, yspeed;

};

#endif // TETRISFORM_H
