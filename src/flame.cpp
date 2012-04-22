#include "flame.h"
#include "sound.h"
#include "game.h"
#include "resourcemanager.h"

flame::flame(game *g, int x, int y, int z)
     : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("flame.json"));
    setAnimation(3);

    firesound = g->rm->getSound("fire.wav");

}

void
flame::start(int x, int y, int z, int flip)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->flip_x = flip;
    setAnimation(0);

    firesound->play();
}

void
flame::stop()
{
    setAnimation(2);
}
