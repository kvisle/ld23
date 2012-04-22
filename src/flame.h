#ifndef __FLAME_H__
#define __FLAME_H__

#include "sprite.h"

class game;
class sound;

class flame : public sprite {
    public:
        flame(game *g, int x, int y, int z);
        void start(int x, int y, int z, int flip);
        void stop();

        sound * firesound;
};

#endif /* __FLAME_H__ */
