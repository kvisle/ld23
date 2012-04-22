#include "door.h"
#include "game.h"
#include "resourcemanager.h"
#include "sound.h"

door::door(game *g, int x, int y, int z, int anim)
    : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("door.json"));
    setAnimation(anim);
    opensound = g->rm->getSound("opendoor.wav");
}

void
door::unLock(drawable *d)
{
    if ( animation != 0 && animation != 3 )
        return;

    if ( animation == 0 && g->gs.keys )
    {
        setAnimation(1);
        opensound->play();
        g->gs.keys--;
    }

    if ( animation == 3 && g->gs.blackkey )
    {
        setAnimation(1);
        opensound->play();
    }
}

