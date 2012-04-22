#ifndef __BLACKKEY_H__
#define __BLACKKEY_H__

#include "item.h"

class game;
class sound;

class blackkey : public item {
    public:
        blackkey(game *g, int x, int y, int z);

        virtual void playGot();

        sound *getsound;
};
#endif /* __BLACKKEY_H__ */
