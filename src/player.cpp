#include <cstdio>
#include "player.h"
#include "game.h"
#include "input.h"
#include "bits.h"

#define ANIMATION_IDLE 0
#define ANIMATION_WALK 1
#define ANIMATION_FALL 2

player::player(game *g, int x, int y, int z)
      : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("player.json"));
    g->in->subscribe(this);

    walking = 0;
    falling = 0;
    jumping = 0;
    jump_progress = 0;
    dead = 0;
}

player::~player()
{
    g->in->unsubscribe(this);
}

void
player::update()
{
    if ( dead )
        return;

    falling = moveGravity();
    walking = moveLeftRight();
    jumping = moveJump();

    if      ( falling ) setAnimation(ANIMATION_FALL);
    else if ( jumping ) setAnimation(ANIMATION_FALL);
    else if ( walking ) setAnimation(ANIMATION_WALK);
    else                setAnimation(ANIMATION_IDLE);

    g->c.snapAt(x+8, y);
//    g->c.keepInFrame(this, 48, 16);
}

int
player::moveGravity()
{
    if ( jumping )
        return 0;

    int gy = 3, gx = 0;
    return !attemptMove(&gx, &gy, 0);
}

int
player::moveLeftRight()
{
    int gx = 0, gy = 0;
    if ( g->in->keys['a'] || g->in->keys['A'] )
    {
        gx -= 1;
    }
    if ( g->in->keys['d'] || g->in->keys['D'] )
    {
        gx += 1;
    }
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

    return !attemptMove(&gx, &gy, 0);
}

int
player::moveJump()
{
    if ( falling )
        return 0;

    if ( !g->in->keys[' '] )
        return 0;

    if ( !jumping && jump_start )
    {
        jump_progress = 0;
        jump_start = 0;
    }

    if ( jump_progress >= 20 )
    {
        return 0;
    }

    int gx = 0;
    int gy = -2;

    jump_progress++;

    int ret = !attemptMove(&gx, &gy, 0);

    if ( ret == 0 )
        jump_progress = 21;

    return ret;
}

void
player::render()
{
    if ( !dead )
        sprite::render();
}

void
player::input(union ninput in)
{
    switch(in.type)
    {
    case NINPUT_KEYDOWN:
        if ( in.key.sym == ' ' ) { jump_start = 1; }
        break;
    case NINPUT_KEYUP:
        break;
    }
}

void
player::kill()
{
    dead = 1;
    g->gs.playeralive = 0;
    puts("I died.");
}

void
player::damage()
{
    puts("I'm damaged.");
}

void
player::pickUp(drawable *d)
{
    if ( d->removeme )
        return;

    switch(d->identify()) {
    case 0:
        g->gs.keys++;
        break;
    case 1:
        puts("Got jetpack");
        break;
    case 2:
        puts("Got gun");
        break;
    }
    d->remove();
}

void
player::unLock(drawable *d)
{
    if ( g->gs.keys == 0 )
        return;

    d->unLock(this);
    g->gs.keys--;
}
