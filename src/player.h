#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sprite.h"
#include "input.h"

class player : public sprite {
    public:
        player(game *g, int x, int y, int z);
        ~player();

        virtual void update();
        virtual void render();
        virtual void input(union ninput in);

    private:
        int walking;
        int falling;
        int jump_start;
        int jumping;
        int jump_progress;

        int moveGravity();
        int moveLeftRight();
        int moveJump();
};

#endif /* __PLAYER_H__ */