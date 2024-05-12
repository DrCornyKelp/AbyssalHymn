#include <map.h>

Multiplayer::~Multiplayer()
{
    for (Player *player : Players) delete player;
    Players = {};
};
Multiplayer::Multiplayer(Player1D players) :
    Players(players), MAIN(Players[0])
{ 
    // Set Player Count
    PlayerCount = Players.size();
    // Set Main Player
    Players[0]->MAIN = 1;
    // Set Players Index
    for (int i = 0; i < PlayerCount; i++)
    {
        Players[i]->INDEX = i;
        Players[i]->MULTI = this;
        Players[i]->INPUT.setTemplate(i);
    }
}

void Multiplayer::changeMain(int index)
{
    for (Player *player : Players)
        player->MAIN = 0;

    Players[index]->MAIN = 1;
}

void Multiplayer::update(Map *map)
{
    for (Player *player : Players)
        player->playerUpdate(map);

    // Update the camera for only MAIN player
    MAIN->camera.playerCameraProperty(map->MapInput);

    // ===================== TESTING =======================
    if (MAIN->INPUT.f1.press())
    {
        MAIN->INPUT.f1.keyhold = 1;
        Players.push_back(new Player());
        Players.back()->setX(MAIN->getX());
        Players.back()->setY(MAIN->getY());

        Players.back()->MULTI = this;
        Players.back()->INPUT.setTemplate(PlayerCount);
        Players.back()->INDEX = PlayerCount;
        PlayerCount++;
    }

    if (MAIN->INPUT.f4.press())
    {
        MAIN->INPUT.f4.keyhold = 1;

        for (Player *player : Players)
        if (!player->MAIN)
        {
            player->setX(MAIN->getX());
            player->setY(MAIN->getY());
        }
    }

    if (MAIN->INPUT.f5.press())
    {
        MAIN->INPUT.f5.keyhold = 1;

        MAIN->INPUT.jump.script = {
            CFG->TIME + 50,
            CFG->TIME + 100,
            CFG->TIME + 150,
            CFG->TIME + 200,
        };
    }

    std::ofstream outputFile("PlayerScript.csv");
    outputFile << MAIN->INPUT.script_history_full;
}

void Multiplayer::drawPlayers()
{
    for (Player *player : Players)
        player->draw_prop.draw();
}

void Multiplayer::drawHuds()
{
    for (Player *player : Players)
        player->HUD.draw();
}