#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <player.h>

class Map;
class Multiplayer
{
public:
    Player1D Players;
    Player *MAIN;

    int PlayerCount = 0;

    ~Multiplayer();
    Multiplayer(Player1D players);
    
    // Player Count Control
    void addPlayer();
    void changeMain(int index);
    void singlePlayer();

    void update(Map *map);
    void drawPlayers();
    void drawHuds();
};

#endif