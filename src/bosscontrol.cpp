#include <cstdio>
#include <stdlib.h>
#include "bosscontrol.h"
#include "flame.h"
#include "bosscreature.h"
#include "game.h"

bosscontrol::bosscontrol(game *g)
           : sprite(g, 86*8, 114*8, 0, "gfx.png")
{
    flame1 = new flame(g, 81*8, 116*8, 0);
    flame2 = new flame(g, 88*8, 116*8, 0);
    flame3 = new flame(g, 95*8, 116*8, 0);

    bc = new bosscreature(g, x, y, z);

    state = 0;
}

bosscontrol::~bosscontrol()
{
    delete(flame1);
    delete(flame2);
    delete(flame3);
}

void
bosscontrol::render()
{
    flame1->render();
    flame2->render();
    flame3->render();

    bc->render();
}

void
bosscontrol::update()
{
    state++;

    if ( g->gs.bosshp ) {
        if ( state % 300 == 0 ) {
            flame1->start(81*8, 116*8, 0, 1);
            flame3->stop();
        }
        if ( (state+100) % 300 == 0 ) {
            flame2->start(88*8, 116*8, 0, 1);
            flame1->stop();
        }
        if ( (state+200) % 300 == 0 ) {
            flame3->start(95*8, 116*8, 0, 0);
            flame2->stop();
        }
    }
    else {
        flame1->stop();
        flame2->stop();
        flame3->stop();
    }

    bc->update();

    if ( state % 200 && g->gs.bosshp ) {
        bc->spawnAt((rand() % 4) + 1);
    }

//    puts("In the bossroom nao!");
}

int
bosscontrol::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    int ret = 0;

    ret |= flame1->collidesWith(x, y, w, h, other, bits);
    ret |= flame2->collidesWith(x, y, w, h, other, bits);
    ret |= flame3->collidesWith(x, y, w, h, other, bits);

    ret |= bc->collidesWith(x, y, w, h, other, bits);

    return ret;
}

