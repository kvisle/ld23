#include "door.h"

door::door(game *g, int x, int y, int z)
    : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("door.json"));
    setAnimation(0);
}

void
door::unLock(drawable *d)
{
    if ( animation != 0 )
        return;

    setAnimation(1);
}

