#include "key.h"

key::key(game *g, int x, int y, int z)
   : item(g, x, y, z)
{
    setAnimation(0);
}
