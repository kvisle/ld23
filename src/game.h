#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "camera.h"

class renderer;
class resourcemanager;
class image;
class drawable;
class font;
class input;
class osd;
class audio;
class overlay;

class game {
    public:
        game();
        ~game();

        void render();
        int update();

        int collides(float x, float y, float w, float h, drawable *me);
        void setReload(int val);
        int getReload();
        int drawBoxes();

        renderer *r;
        resourcemanager *rm;
        input *in;
        audio *a;

        camera c;
        font *f;
        overlay *ov;

        int reload;

    private:
        std::vector<drawable*> assets;
        int updateno;
        int boxDraw;

        osd *o;
};

#endif /* __GAME_H__ */
