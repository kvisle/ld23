#include "background.h"

#include "game.h"
#include "renderer.h"
#include "image.h"

background::background(game *g, int x, int y, int z)
          : sprite(g, x, y, z, "gfx.png")
{
}

void
background::render()
{
    g->r->addQuad(tex->getTexture(), 1.0, NULL,
                  x, y, 160, 144,
                  0.375, 0.1875, 0.625, 0.5625,
                  1.0f, 1.0f, 1.0f, 1.0f,
                  0, 0);
}

int
background::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    return 0;
}

