#ifndef BLOCK_H
#define BLOCK_H


class Block
{
    public:
        Block();
        virtual ~Block();
    protected:
    private:
        int x_pos;
        int y_pos;
        int x_speed;
        int y_speed;
        static const int width = 15;
        static const int height  = 15;

};

#endif // BLOCK_H
