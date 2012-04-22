#include "game.h"
#include "font.h"
#include "winscreen.h"
#include "renderer.h"
#include "image.h"

win::win(game *g)
      : drawable(g, 0, 0, 0, "gfx.png")
{
    blinky = 0;
}

void
win::render()
{
    g->f->drawString("\\9bbc0fff\\congratulations\n\nyou have completed\ntiny quest.a entry\nfor ludum dare #23\n\nthis game was made\nin 48 hours.\n\n  thank you for\n playing my game.\n\n\ntwitter.com/kvisle", 8, 8, NULL);
}

void
win::update()
{
    blinky++;
}
