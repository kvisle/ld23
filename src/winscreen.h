#ifndef __WINSCREEN_H__
#define __WINSCREEN_H__

#include "drawable.h"

class game;

class win : public drawable {
    public:
        win(game *g);
        virtual void update();
        virtual void render();

        int blinky;
};

#endif /* __WINSCREEN_H__ */
