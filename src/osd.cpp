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
    g->r->addOpQuad(NULL, 0, 0, 160, 8, 0.05859375, 0.21875, 0.05859375, 1.0);

    g->r->addQuad(tex->getTexture(), NULL,
                   0, 0, 8, 8,
                   0.0625, 0.1875, 0.03125, 0.0315);



    drawKeys();

    if ( !g->gs.playeralive )
    {
        g->f->drawString("\\0f380fff\\you are dead", 33, 33, NULL);
        g->f->drawString("\\9bbc0fff\\you are dead", 32, 32, NULL);
    }
}

void
osd::drawKeys()
{
    char keybuffer[10];

    sprintf(keybuffer, "\\9bbc0fff\\%02d", g->gs.keys);
    g->f->drawString(keybuffer, 8, 0, NULL);
}
