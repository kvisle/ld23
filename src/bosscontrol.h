#ifndef __BOSSCONTROL_H__
#define __BOSSCONTROL_H__

#include "sprite.h"

class game;

class flame;
class bosscreature;

class bosscontrol : public sprite {
    public:
        bosscontrol(game *g);
        ~bosscontrol();

        virtual void render();
        virtual void update();
        int collidesWith(float x, float y, float w, float h, drawable *other, int bits);

        flame * flame1;
        flame * flame2;
        flame * flame3;

        bosscreature * bc;

        int state;
};

#endif /* __BOSSCONTROL_H__ */
