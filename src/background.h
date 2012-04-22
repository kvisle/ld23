#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "sprite.h"

class game;

class background : public sprite {
    public:
        background(game *g, int x, int y, int z);

        virtual void render();
        virtual int collidesWith(float x, float y, float w, float h, drawable *other, int bits);

};

#endif /* __BACKGROUND_H__ */
