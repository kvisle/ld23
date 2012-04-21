#include "game.h"
#include "renderer.h"
#include "image.h"
#include "overlay.h"

overlay::overlay(game *g)
       : drawable(g, 0, 0, 0, "gfx.png")
{

}

void
overlay::render()
{
    int x, y;

    for ( x = 0; x < 160; x += 4)
    {
        for ( y = 0; y < 144; y += 4)
        {
            g->r->addQuad(tex->getTexture(), 1.0, NULL,
                          x, y, 4, 4,
                          0.9375, 0.125, 0.0625, 0.0625,
                          1.0, 1.0, 1.0, 1.0,
                          0.0, 0.0);
        }
    }
}
