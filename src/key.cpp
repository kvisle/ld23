#include "key.h"
#include "game.h"
#include "resourcemanager.h"
#include "sound.h"

key::key(game *g, int x, int y, int z)
   : item(g, x, y, z)
{
    setAnimation(0);

    getsound = g->rm->getSound("gotkey.wav");
}

void
key::playGot()
{
    getsound->play();
}
