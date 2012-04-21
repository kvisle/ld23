#include "item.h"
#include "bits.h"

item::item(game *g, int x, int y, int z)
      : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("item.json"));
}

int
item::identify()
{
    return animation;
}
