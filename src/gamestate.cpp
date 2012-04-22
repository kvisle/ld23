#include <cstdio>
#include "gamestate.h"

gamestate::gamestate(int lives)
{
    state = 0;
    playeralive = 1;
    playerlives = lives;
    keys = 0;
    gotGun = 0;
    ammo = 0;
    hp = 5;
    activecp = NULL;
    doublejump = 0;
    blackkey = 0;
    bosshp = 5;
}
