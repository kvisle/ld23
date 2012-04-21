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
    g->f->drawString("\\9bbc0fff\\fritz", 0, 0, NULL);
}
