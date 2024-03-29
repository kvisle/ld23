#ifndef __GAME_H__
#define __GAME_H__

#include <vector>

#include "camera.h"
#include "gamestate.h"

class renderer;
class resourcemanager;
class image;
class drawable;
class font;
class input;
class osd;
class audio;
class overlay;
class splash;
class win;


class game {
    public:
        game();
        ~game();

        void render();
        int update();

        int collides(float x, float y, float w, float h, sprite *me, int bits);
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
        gamestate gs;
        splash * spl;
        win * w;

        int reload;

    private:
        std::vector<drawable*> assets;
        int updateno;
        int boxDraw;

        osd *o;
};

#endif /* __GAME_H__ */
