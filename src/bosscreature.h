#ifndef __BOSSCREATURE_H__
#define __BOSSCREATURE_H__

#include "sprite.h"

class sound;

class bosscreature : public sprite {
    public:
        bosscreature(game *g, int x, int y, int z);

        virtual void update();
        virtual void damage(drawable *d);
        virtual void render();

        void spawnAt(int pos);

        int sincespawn;

        int isdead;
        sound * hitsound;
};

#endif /* __BOSSCREATURE_H__ */
