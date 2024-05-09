#include <map.h>

Multiplayer::~Multiplayer()
{
    for (Player *player : Players) delete player;
    Players = {};
};
Multiplayer::Multiplayer(Player1D players) : Players(players)
{}

void Multiplayer::updatePlayers(Map *map)
{
    for (Player *player : Players)
        player->playerUpdate(map);
}