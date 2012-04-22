#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include "drawable.h"

class game;

class splash : public drawable {
    public:
        splash(game *g);
        virtual void update();
        virtual void render();

        int blinky;
};

#endif /* __SPLASHSCREEN_H__ */
