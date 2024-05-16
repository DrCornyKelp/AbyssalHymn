#include <map.h>

Multiplayer::~Multiplayer()
{
    for (Player *player : Players) delete player;
};
Multiplayer::Multiplayer(Player1D players) :
    Players(players), MAIN(Players[0])
{ 
    // Set Player Count
    PlayerCount = Players.size();
    // Set Players Index
    for (int i = 0; i < PlayerCount; i++)
    {
        Players[i]->INDEX = i;
        Players[i]->MULTI = this;
        Players[i]->INPUT.setTemplate(i);
    }
    // Set Main Player
    MAIN->MAIN = 1;

    // ================== TESTING ==================
    if (PlayerCount < 2) MAIN->INPUT.setTemplate(-1);
}

void Multiplayer::addPlayer()
{
    Players.push_back(new Player());
    Players.back()->INDEX = PlayerCount;
    Players.back()->MULTI = this;
    Players.back()->INPUT.setTemplate(PlayerCount);
    // Set Player Initial Postion
    Players.back()->setX(MAIN->getX());
    Players.back()->setY(MAIN->getY());
    
    // Increment player count
    PlayerCount++;

    // ================== TESTING ==================
    MAIN->INPUT.setTemplate(0);

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
    if (MAIN->godmode)
        MAIN->camera.resetCamera();
    else 
        MAIN->camera.playerCameraProperty();

    // ===================== TESTING =======================
    if (MAIN->INPUT.f1.press())
    {
        MAIN->INPUT.f1.hold = 1;

        addPlayer();
    }

    if (MAIN->INPUT.f4.press())
    {
        MAIN->INPUT.f4.hold = 1;

        for (Player *player : Players)
        if (!player->MAIN)
        {
            player->setX(MAIN->getX());
            player->setY(MAIN->getY());
        }
    }

    if (MAIN->INPUT.f5.press())
    {
        MAIN->INPUT.f5.hold = 1;

        // Hold Ctrl To convert script to current time
        MAIN->INPUT.executeScript("player_data/ExecuteScript.csv", MAIN->INPUT.lctrl.state);
    }

    std::ofstream outputFile("player_data/PlayerScript.csv");
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