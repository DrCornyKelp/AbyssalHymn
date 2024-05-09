#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "player.h"

class Map;
class Multiplayer
{
public:
    Player1D Players;
    Player *MAIN;

    ~Multiplayer();
    Multiplayer(Player1D players);
    void update(Map *map);
    void draw();
};

#endif