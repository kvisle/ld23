#include "image.h"
#include "game.h"
#include "renderer.h"
#include "font.h"
#include "osd.h"

osd::osd(game *g)
   : drawable(g, 0, 0, 0, "gfx.png")
{

}

osd::~osd() { }

void
osd::render()
{
    char number[10];
    g->r->addOpQuad(NULL, 0, 0, 160, 9, 0.05859375, 0.21875, 0.05859375, 1.0);

    g->r->addQuad(tex->getTexture(), NULL,
                   0, 0, 8, 8,
                   0.0625, 0.1875, 0.03125, 0.0315);


    g->r->addQuad(tex->getTexture(), NULL,
                   32, 0, 8, 8,
                   0.09375, 0.1875, 0.03125, 0.0315);


    sprintf(number, "\\9bbc0fff\\%02d", g->gs.keys);
    g->f->drawString(number, 8, 0, NULL);

    sprintf(number, "\\9bbc0fff\\%02d", g->gs.hp);
    g->f->drawString(number, 40, 0, NULL);


    if ( !g->gs.playeralive )
    {
        g->f->drawString("\\0f380fff\\you are dead", 33, 33, NULL);
        g->f->drawString("\\9bbc0fff\\you are dead", 32, 32, NULL);
    }
}
