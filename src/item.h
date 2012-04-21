#ifndef __ITEM_H__
#define __ITEM_H__

#include "sprite.h"

class game;

class item : public sprite {
    public:
        item(game *g, int x, int y, int z);

        virtual int identify();

};

#endif /* __ITEM_H__ */
