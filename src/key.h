#ifndef __KEY_H__
#define __KEY_H__

#include "item.h"

class game;

class key : public item {
    public:
        key(game *g, int x, int y, int z);
};
#endif /* __KEY_H__ */
