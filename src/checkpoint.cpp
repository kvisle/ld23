#include "checkpoint.h"

#include "game.h"
#include "renderer.h"
#include "image.h"
#include "bits.h"
#include "resourcemanager.h"
#include "sound.h"

checkpoint::checkpoint(game *g, int x, int y, int z)
          : sprite(g, x, y, z, "gfx.png")
{
    activatesound = g->rm->getSound("activatecpsound.wav");
}

void
checkpoint::render()
{
    float tx = ( g->gs.activecp == this ) ? 0.3125 : 0.25;

    g->r->addQuad(tex->getTexture(), 1.0, &(g->c),
                  x, y, 16, 16,
                  tx, 0.34375, 0.0625, 0.0625,
                  1.0f, 1.0f, 1.0f, 1.0f,
                  0, 0);

}

int
checkpoint::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    if ( x+w < this->x )
        return 0;

    if ( x > this->x+16 )
        return 0;

    if ( y+h < this->y )
        return 0;

    if ( y > this->y+16 )
        return 0;    

    if ( g->gs.activecp == this )
        return 0;

    if ( bits & BIT_SETCHECKPOINT )
    {
        g->gs.activecp = this;
        activatesound->play();
    }

    return 0;
}

