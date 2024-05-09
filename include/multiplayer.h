#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "player.h"

class Map;
class Multiplayer
{
public:
    Player1D Players;

    ~Multiplayer();
    Multiplayer(Player1D players);
    void updatePlayers(Map *map);
};

#endif