#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "player.h"

class Map;
class Multiplayer
{
public:
    Player1D Players;
    Player *MAIN;

    int PlayerCount = 0;

    ~Multiplayer();
    Multiplayer(Player1D players);
    void changeMain(int index);
    void update(Map *map);
    void draw();
};

#endif