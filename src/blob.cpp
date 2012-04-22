#include <cstdio>
#include "blob.h"
#include "sound.h"
#include "game.h"
#include "resourcemanager.h"


blob::blob(game *g, int x, int y, int z)
    : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("blob1.json"));
    setAnimation(0);

    isdead = 0;
    sincejump = 0;
    jumping = 0;
    jump_start = 0;
    jump_dir = 0;
    falling = 0;
    killblob = g->rm->getSound("killblob.wav");
    blobjump = g->rm->getSound("blobjump.wav");
}

void
blob::update()
{
    if ( isdead )
    {
        if ( isdead++ > 40 )
            remove();

        return;
    }

    jumping = moveJump();
    falling = moveGravity();

    if ( sincejump > 100 ) {
        setAnimation(1);
        jump();
    }
    else if ( sincejump > 80 ) {
        setAnimation(2);
        sincejump++;
    }
    else {
        if ( !falling && !jumping )
        {
            sincejump++;
            setAnimation(0);
        }
    }
}

int
blob::moveGravity()
{
    if ( jumping )
        return 0;

    int gy = 3, gx = 0;
    return !attemptMove(&gx, &gy, 0);
}


void
blob::jump()
{
    sincejump = 0;
    jump_start = 1;
}

int
blob::moveJump()
{
    if ( falling )
        return 0;

    if ( !jumping && jump_start )
    {
        jump_progress = 0;
        jump_start = 0;
        jump_dir = rand() % 2 ? -2 : 2;
        blobjump->play();
    }

    if ( jump_progress >= 10 )
    {
        return 0;
    }

    int gx = jump_dir;
    int gy = -2;

    jump_progress++;

    int ret = !attemptMove(&gx, &gy, 0);

    if ( ret == 0 )
    {
        jump_progress = 11;
        sincejump = 0;
    }

    return ret;
}



void
blob::render()
{
    if ( isdead / 4 % 2 == 0 )
        sprite::render();
}

void
blob::damage(drawable *d)
{
    setAnimation(3);
    isdead = 1;
    killblob->play();
}

