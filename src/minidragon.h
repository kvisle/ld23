#ifndef __MINIDRAGON_H__
#define __MINIDRAGON_H__

#include "sprite.h"

class sound;
class flame;

class minidragon : public sprite {
    public:
        minidragon(game *g, int x, int y, int z);
        ~minidragon();

        virtual void update();
        virtual void render();

        virtual void damage(drawable *d);

        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);


        int moveGravity();
        int moveLeftRight();

        int isdead;
        int falling;
        int walk_dir;
        int walking;

        int untilfire;
        int fire;        

        void startflame();
        void stopflame();

        sound * killminidragon;
        sound * firesound;

        flame * myflame;

};

#endif /* __MINIDRAGON_H__ */
