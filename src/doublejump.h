#ifndef __DOUBLEJUMP_H__
#define __DOUBLEJUMP_H__

#include "item.h"

class game;
class sound;

class doublejump : public item {
    public:
        doublejump(game *g, int x, int y, int z);

        virtual void playGot();

        sound *getsound;
};
#endif /* __DOUBLEJUMP_H__ */
