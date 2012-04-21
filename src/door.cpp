#include "door.h"
#include "game.h"
#include "resourcemanager.h"
#include "sound.h"

door::door(game *g, int x, int y, int z)
    : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("door.json"));
    setAnimation(0);
    opensound = g->rm->getSound("opendoor.wav");
}

void
door::unLock(drawable *d)
{
    if ( animation != 0 )
        return;

    setAnimation(1);
    opensound->play();
}

