#include "bosscreature.h"
#include "game.h"
#include "sound.h"
#include "resourcemanager.h"


bosscreature::bosscreature(game *g, int x, int y, int z)
            : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("bosscreature.json"));
    setAnimation(0);
    sincespawn = 0;

    hitsound = g->rm->getSound("hitsound.wav");
}

void
bosscreature::spawnAt(int pos)
{
    if ( animation != 0 )
        return;

    switch(pos) {
        case 1: x = 83*8; break;
        case 2: x = 88*8; break;
        case 3: x = 90*8; break;
        case 4: x = 95*8; break;
    }
    y = 119*8;

    setAnimation(1);
    sincespawn = 0;
}

void
bosscreature::update()
{
    if ( animation == 2 )
        sincespawn++;

    if ( sincespawn > 500 )
    {
        setAnimation(4);
        sincespawn = 0;
    }

    if ( isdead )
    {
        if ( ++isdead > 120 )
        {
            isdead = 0;
            setAnimation(0);
        }
    }
}

void
bosscreature::damage(drawable *d)
{
    setAnimation(3);
    isdead = 1;
    g->gs.bosshp--;

    hitsound->play();
}

void
bosscreature::render()
{
    if ( !isdead || isdead % 4 / 2 == 0 )
        sprite::render();
}


