#include <cstdio>
#include "player.h"
#include "game.h"
#include "resourcemanager.h"
#include "input.h"
#include "sound.h"
#include "bits.h"
#include "checkpoint.h"
#define ANIMATION_IDLE 0
#define ANIMATION_WALK 1
#define ANIMATION_FALL 2

player::player(game *g, int x, int y, int z)
      : sprite(g, x, y, z, "gfx.png")
{
    loadJson(std::string("player.json"));
    g->in->subscribe(this);
    jumpsound = g->rm->getSound("jump.wav");
    hurtsound = g->rm->getSound("hurt.wav");
    respawnsound = g->rm->getSound("respawn.wav");

    walking = 0;
    falling = 0;
    jumping = 0;
    jump_progress = 0;
    dead = 0;
    damagewait = 0;
    knockback = 0;
    doublejumped = 0;
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

    if ( damagewait > 0 )
        damagewait--;

    if ( knockback )
        knockback = knockMove();

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
player::knockMove()
{
    if ( knockback == 0 || knockback > 10 )
        return 0;

    int gx = ( knockdir ) ? 1 : -1;
    int gy = -1;

    int ret = !attemptMove(&gx, &gy, 0);

    knockback++;

    if ( ret == 0 )
        knockback = 0;

    return knockback;
}

int
player::moveGravity()
{
    if ( jumping )
        return 0;

    int gy = 3, gx = 0;
    int ret = !attemptMove(&gx, &gy, 0);

    if ( !ret )
        doublejumped = 0;

    return ret;
}

int
player::moveLeftRight()
{
    if ( knockback )
        return 0;

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
    if ( knockback )
        return 0;

//    if ( falling )
//        return 0;

    if ( !g->in->keys[' '] )
        return 0;

//    puts("You're pressing space");


    if ( jump_start && ( ( !falling && !jumping ) || ( !doublejumped && g->gs.doublejump ) ) )
    {
        if ( jumping || falling )
        {
            doublejumped++;
            falling = 0;
        }

        jump_progress = 0;
        jump_start = 0;
        jumpsound->play();
    }

    if ( jump_progress >= 20 )
    {
        return 0;
    }

    if ( falling )
        return 0;


    int gx = 0;
    int gy = -2;

    jump_progress++;

    int ret = !attemptMove(&gx, &gy, 0);

    if ( ret == 0 )
        jump_progress = 26;

    return ret;
}

void
player::knockbackInit()
{
    jumping = 0;
    knockback = 1;
    knockdir = flip_x;
}

void
player::render()
{
    if ( !dead && damagewait / 4 % 2 == 0 )
        sprite::render();
}

void
player::input(union ninput in)
{
    switch(in.type)
    {
    case NINPUT_KEYDOWN:
        if ( dead && in.key.sym == ' ' ) { respawn(); }
        else if ( in.key.sym == ' ' )
        {
            jump_start = 1;
        }
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
player::respawn()
{
    dead = 0;
    g->gs.playeralive = 1;
    x = g->gs.activecp->x;
    y = g->gs.activecp->y;
    g->gs.hp = 5;
    g->c.snapAt(x+8, y);
    respawnsound->play();
}

void
player::damage(drawable *d)
{
    if ( damagewait )
        return;

    if ( --g->gs.hp == 0 )
        return kill();

    knockbackInit();
    damagewait = 64;
    puts("I'm damaged.");
    hurtsound->play();
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
        g->gs.doublejump = 1;
        break;
    case 2:
        puts("Got gun");
        break;
    case 3:
        g->gs.blackkey = 1;
        break;
    }
    d->remove();
}

void
player::unLock(drawable *d)
{
    d->unLock(this);
}
