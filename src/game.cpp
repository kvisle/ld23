#include <iostream>
#include <cstdio>

#ifdef TARGET_SDL
#include <SDL.h>
#endif

#include "renderer.h"
#include "audio.h"
#include "resourcemanager.h"
#include "game.h"
#include "image.h"
#include "drawable.h"
#include "tileset.h"
#include "tilemap.h"
#include "resource.h"
#include "font.h"
#include "sprite.h"
#include "input.h"

#include "gamestate.h"
#include "bits.h"
#include "osd.h"
#include "overlay.h"
#include "player.h"
#include "key.h"
#include "door.h"
#include "blob.h"
#include "minidragon.h"
#include "flame.h"
#include "checkpoint.h"
#include "background.h"
#include "doublejump.h"
#include "blackkey.h"
#include "bosscontrol.h"
#include "splashscreen.h"
#include "winscreen.h"

game::game() : c(160, 144, 160, 144), gs(5)
{
    updateno = 0;
    boxDraw = 0;

    in = new input();
    r = new renderer(160, 144);
    rm = new resourcemanager(this);
    a = new audio();
    f = new font(rm->getImage("charmap2.png"), this, 8, 8);
    ov = new overlay(this);
    o = new osd(this);
    spl = new splash(this);
    w = new win(this);

    assets.push_back(new background(this, 0, 0, 0));
    assets.push_back(new tilemap(this, "tilemap.png", "gfx.png", "gfxts1.json"));

// Checkpoints: 31x30, 116x28, 184x31, 168x59

    assets.push_back(new checkpoint(this, 31*8, 30*8, 0));
    assets.push_back(new checkpoint(this, 116*8, 28*8, 0));
    assets.push_back(new checkpoint(this, 184*8, 31*8, 0));
    assets.push_back(new checkpoint(this, 168*8, 59*8, 0));
    assets.push_back(new checkpoint(this, 90*8, 84*8, 0));


    assets.push_back(new player(this, 28*8, 30*8, 0));
//    assets.push_back(new player(this, 89*8, 84*8, 0));

    assets.push_back(new doublejump(this, 194*8, 86*8, 0));
    assets.push_back(new key(this, 129*8, 32*8, 0));
    assets.push_back(new key(this, 153*8, 50*8, 0));
    assets.push_back(new key(this, 82*8, 68*8, 0));
    assets.push_back(new blackkey(this, 113*8, 50*8, 0));

    assets.push_back(new door(this, 156*8, 30*8, 0, 0));
    assets.push_back(new door(this, 182*8, 66*8, 0, 0));
    assets.push_back(new door(this, 176*8, 84*8, 0, 0));
    assets.push_back(new door(this, 86*8, 83*8, 0, 3));

    assets.push_back(new blob(this, 52*8, 31*8, 0));
    assets.push_back(new blob(this, 67*8, 28*8, 0));
    assets.push_back(new blob(this, 75*8, 30*8, 0));
    assets.push_back(new blob(this, 125*8, 32*8, 0));
    assets.push_back(new blob(this, 136*8, 32*8, 0));
    assets.push_back(new minidragon(this, 153*8, 31*8, 0));
    assets.push_back(new minidragon(this, 104*8, 49*8, 0));
    assets.push_back(new minidragon(this, 142*8, 49*8, 0));
    assets.push_back(new minidragon(this, 86*8, 67*8, 0));
    assets.push_back(new bosscontrol(this));


    SDL_WM_SetCaption("Tiny Quest (LD#23, Compo version)", NULL);

    std::cout << "Made game" << std::endl;
}

game::~game()
{
    delete(rm);
    delete(r);
    delete(f);
    delete(in);
    delete(a);
    delete(ov);
}

void
game::render()
{
    r->clear();

    switch(gs.state)
    {
    case 0:
        spl->render();
        break;
    case 1:
        for (uint32_t i=0; i < assets.size(); i++)
        {
            assets[i]->render();
        }
        o->render();
        break;
    case 2:
        w->render();
        break;
    }

    ov->render();
    r->swap();
}

int
game::update()
{
    updateno++;

#ifdef TARGET_SDL
/*    if ( updateno % 60 == 0 )
    {
        char caption[128];
        sprintf(caption, "Assets: %lu", assets.size());
        SDL_WM_SetCaption(caption, NULL);
    }*/
#endif

    switch(gs.state) {
    case 0:
        spl->update();
        break;
    case 1:
        for (uint32_t i=0; i < assets.size(); i++)
        {
            if ( assets[i]->removeme )
            {
                assets.erase(assets.begin() + i);
                i--;
                continue;
            }
            if ( assets[i]->inFrame() )
                assets[i]->update();
        }
        this->setReload(0);
        break;
    case 2:
        break;
    }    

    return 0;
}

int
game::collides(float x, float y, float w, float h, sprite * me, int bits)
{
    int ret = 0;
    for (uint32_t i=0; i < assets.size(); i++)
    {
        if ( assets[i] == me )
            continue;

        ret |= assets[i]->collidesWith(x, y, w, h, me, bits);

    }

    if ( ret & BIT_KILL && bits & BIT_KILLABLE )
        me->kill();

//    if ( ret & BIT_DAMAGE && bits & BIT_KILLABLE )
//        me->damage();

    return ret;
}

void
game::setReload( int val )
{
    this->reload = val;
}

int
game::getReload()
{
    return reload;
}

int
game::drawBoxes()
{
    return this->boxDraw;
}
