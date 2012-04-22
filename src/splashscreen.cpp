#include "game.h"
#include "font.h"
#include "splashscreen.h"
#include "renderer.h"
#include "image.h"

splash::splash(game *g)
      : drawable(g, 0, 0, 0, "gfx.png")
{
    blinky = 0;
}

void
splash::render()
{
    g->r->addQuad(tex->getTexture(), 1.0, NULL,
                  16, 8, 128, 64,
                  0.5, 0.75, 0.5, 0.25,
                  1.0f, 1.0f, 1.0f, 1.0f,
                  0, 0);

    if ( ( blinky / 20 ) % 2 == 0 )
    {
        g->f->drawString("\\9bbc0fff\\press enter to\n\n start the game", 16, 72, NULL);
    }

    g->f->drawString("\\9bbc0fff\\ ludum dare # 23\n   april 2012\ntrygve vea/kvisle", 8, 112, NULL);
}

void
splash::update()
{
    blinky++;
}
