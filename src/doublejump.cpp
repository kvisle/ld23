#include "doublejump.h"
#include "game.h"
#include "resourcemanager.h"
#include "sound.h"

doublejump::doublejump(game *g, int x, int y, int z)
   : item(g, x, y, z)
{
    setAnimation(1);

    getsound = g->rm->getSound("gotdoublejump.wav");
}

void
doublejump::playGot()
{
    getsound->play();
}
