#ifndef __OSD_H__
#define __OSD_H__

#include "drawable.h"
class game;

class osd : public drawable {
    public:
        osd(game *g);
        ~osd();

        virtual void render();

        void drawKeys();
};

#endif
