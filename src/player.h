#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sprite.h"
#include "input.h"

class sound;

class player : public sprite {
    public:
        player(game *g, int x, int y, int z);
        ~player();

        virtual void update();
        virtual void render();
        virtual void input(union ninput in);
        virtual void pickUp(drawable *d);
        virtual void unLock(drawable *d);

        virtual void damage(drawable *d);
        virtual void kill();

        void respawn();

    private:
        int walking;
        int falling;
        int jump_start;
        int jumping;
        int jump_progress;
        int dead;
        int knockback;
        int damagewait;
        int doublejumped;

        int moveGravity();
        int moveLeftRight();
        int moveJump();

        int knockMove();
        void knockbackInit();
        int knockdir;

        sound *jumpsound;
        sound *hurtsound;
        sound *respawnsound;
};

#endif /* __PLAYER_H__ */
