#ifndef __CHECKPOINT_H__
#define __CHECKPOINT_H__

#include "sprite.h"

class game;
class sound;

class checkpoint : public sprite {
    public:
        checkpoint(game *g, int x, int y, int z);

        virtual void render();
        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);

        sound *activatesound;

};

#endif /* __CHECKPOINT_H__ */
