#ifndef __KEY_H__
#define __KEY_H__

#include "item.h"

class game;
class sound;

class key : public item {
    public:
        key(game *g, int x, int y, int z);

        virtual void playGot();

        sound *getsound;
};
#endif /* __KEY_H__ */
