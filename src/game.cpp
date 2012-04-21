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

    assets.push_back(new tilemap(this, "tilemap.png", "gfx.png", "gfxts1.json"));
    assets.push_back(new player(this, 28*8, 30*8, 0));
    assets.push_back(new key(this, 32*8, 30*8, 0));
    assets.push_back(new door(this, 151*8, 30*8, 0));

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

    for (uint32_t i=0; i < assets.size(); i++)
    {
        assets[i]->render();
    }
    o->render();
    ov->render();
    r->swap();
}

int
game::update()
{
    updateno++;

#ifdef TARGET_SDL
    if ( updateno % 60 == 0 )
    {
        char caption[128];
        sprintf(caption, "Assets: %lu", assets.size());
        SDL_WM_SetCaption(caption, NULL);
    }
#endif

//    std::vector<drawable*>::iterator it;

//    for (it = assets.begin() ; it != assets.end(); it++)
    for (uint32_t i=0; i < assets.size(); i++)
    {
        if ( assets[i]->removeme )
        {
            assets.erase(assets.begin() + i);
            i--;
            continue;
        }
        assets[i]->update();
    }


    this->setReload(0);

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

    if ( ret & BIT_DAMAGE && bits & BIT_KILLABLE )
        me->damage();

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
