#ifndef __BLOB_H__
#define __BLOB_H__

#include "sprite.h"

class sound;

class blob : public sprite {
    public:
        blob(game *g, int x, int y, int z);

        virtual void update();
        virtual void render();

        virtual void damage(drawable *d);

        void jump();
        int moveJump();
        int moveGravity();

        int isdead;
        int sincejump;
        int jumping;
        int jump_dir;
        int jump_start;
        int jump_progress;
        int falling;

        sound * killblob;
        sound * blobjump;

};

#endif /* __BLOB_H__ */
