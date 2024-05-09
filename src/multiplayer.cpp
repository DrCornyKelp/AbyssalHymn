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
    for (Player *player : Players) player->MULTI = this;
}

void Multiplayer::update(Map *map)
{
    for (Player *player : Players) player->playerUpdate(map);
    MAIN->camera.playerCameraProperty(map->MapInput);

    std::cout << Players[0]->getY() << " " << Players[1]->getY() << "\n";
}

void Multiplayer::draw()
{
    for (Player *player : Players) player->draw_prop.playerDrawSprite();
}