#include <cstdio>
#include "gamestate.h"

gamestate::gamestate(int lives)
{
    playeralive = 1;
    playerlives = lives;
    keys = 0;
    gotGun = 0;
    ammo = 0;
    hp = 5;
    activecp = NULL;
}
