#ifndef __DOOR_H__
#define __DOOR_H__

#include "sprite.h"

class sound;

class door : public sprite {
    public:
        door(game *g, int x, int y, int z, int anim);

        virtual void unLock(drawable *d);
        sound *opensound;
};

#endif /* __DOOR_H__ */
