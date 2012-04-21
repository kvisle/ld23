#ifndef __DOOR_H__
#define __DOOR_H__

#include "sprite.h"

class door : public sprite {
    public:
        door(game *g, int x, int y, int z);

        virtual void unLock(drawable *d);
};

#endif /* __DOOR_H__ */
