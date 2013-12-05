#ifndef TETRISFORM_H
#define TETRISFORM_H
#include <SDL/SDL.h>

class TetrisForm
{
    public:
        TetrisForm(int x, int y, bool falling, char type);
        TetrisForm(int x, int y, bool falling, char typ, bool ground_type);
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
        bool in_game;
        bool below;
        bool ground;

};

#endif // TETRISFORM_H
