#include <map.h>

Multiplayer::~Multiplayer()
{
    for (Player *player : Players) delete player;
    Players = {};
};
Multiplayer::Multiplayer(Player1D players) :
    Players(players), MAIN(Players[0])
{ 
    Players[0]->MAIN = 1;
    for (int i = 0; i < Players.size(); i++)
    {
        Players[i]->INDEX = i;
        Players[i]->MULTI = this;
    }
}

void Multiplayer::update(Map *map)
{
    for (Player *player : Players) player->playerUpdate(map);
    MAIN->camera.playerCameraProperty(map->MapInput);
}

void Multiplayer::draw()
{
    for (Player *player : Players) player->draw_prop.playerDrawSprite();
}