#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

class checkpoint;

class gamestate {
    public:
        gamestate(int lives);

        int playeralive;
        int playerlives;
        int hp;
        int keys;
        int gotGun;
        int ammo;
        checkpoint *activecp;
        int doublejump;
        int blackkey;
};

#endif /* __GAMESTATE_H__ */
