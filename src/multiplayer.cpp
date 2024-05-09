#include <map.h>

Multiplayer::~Multiplayer()
{
    for (Player *player : Players) delete player;
    Players = {};
};
Multiplayer::Multiplayer(Player1D players) :
    Players(players), MAIN(Players[0])
{}

void Multiplayer::update(Map *map)
{
    for (Player *player : Players)
        player->playerUpdate(map);

    MAIN->camera.playerCameraProperty(map->MapInput);
}