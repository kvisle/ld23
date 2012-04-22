#include <cstdio>
#include "minidragon.h"
#include "sound.h"
#include "game.h"
#include "resourcemanager.h"
#include "flame.h"

minidragon::minidragon(game *g, int x, int y, int z)
    : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("minidragon1.json"));
    setAnimation(0);

    isdead = 0;
    falling = 0;
    walk_dir = 2;
    walking = 1;
    untilfire = 40 + (rand() % 40);
    fire = 0;
    killminidragon = g->rm->getSound("killminidragon.wav");
    firesound = g->rm->getSound("fire.wav");
    myflame = new flame(g, x, y, z);
}

minidragon::~minidragon()
{
    delete(myflame);
}

void
minidragon::update()
{
    myflame->update();

    if ( isdead )
    {
        if ( isdead++ > 40 )
            remove();

        return;
    }

    if ( fire ) {
        if ( ++fire == 40 ) {
            stopflame();
        }
        else if ( fire == 60 ) {
            fire = 0;
            walking = 1;
            untilfire = 40 + (rand()%40);
        }
        return;
    }


    if ( --untilfire == 0 )
    {
        setAnimation(2);
        fire = 1;
        startflame();
    }
    else if ( untilfire < 20 )
    {
        walking = 0;
        setAnimation(1);
    }

    falling = moveGravity();
    walking = moveLeftRight();
}

void
minidragon::startflame()
{
    int xp = flip_x ? x - 34 : x + qw + 2;

    myflame->start(xp, y+5, z, flip_x);
}

void
minidragon::stopflame()
{
    myflame->stop();
}


int
minidragon::moveGravity()
{
    int gy = 3, gx = 0;
    return !attemptMove(&gx, &gy, 0);
}

int
minidragon::moveLeftRight()
{
    if ( !walking )
        return 0;
    int gx = 0, gy = 0;

    gx = ( walk_dir == 1 ) ? 1 : -1;

    if ( gx < 0 )
    {
        flip_x = 1;
    }
    else if ( gx > 0 )
    {
        flip_x = 0;
    }
    if ( gx == 0 )
        return 0;

    if ( !attemptMove(&gx, &gy, 0) == 0 )
    {
        walk_dir = ( walk_dir == 1 ) ? 2 : 1;
    }

    return 1;
}

void
minidragon::render()
{
    if ( isdead / 4 % 2 == 0 )
    {
        myflame->render();
        sprite::render();
    }
}

void
minidragon::damage(drawable *d)
{
    setAnimation(3);
    isdead = 1;
    killminidragon->play();
}


int
minidragon::collidesWith(float x, float y, float w, float h, drawable *other, int bits)
{
    int ret = 0;

    ret |= myflame->collidesWith(x, y, w, h, other, bits);
    ret |= sprite::collidesWith(x, y, w, h, other, bits);

    return ret;
}
