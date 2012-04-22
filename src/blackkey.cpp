#include "blackkey.h"
#include "game.h"
#include "resourcemanager.h"
#include "sound.h"

blackkey::blackkey(game *g, int x, int y, int z)
   : item(g, x, y, z)
{
    setAnimation(3);

    getsound = g->rm->getSound("gotkey.wav");
}

void
blackkey::playGot()
{
    getsound->play();
}
