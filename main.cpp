#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <chrono>

#include "game.h"
#include "player.h"
#include "block.h"
#include "decoration_dynamic.h"
#include "decoration.h"
// #include "event_trigger.h"
#include "hud.h"
#include "audio.h"
#include "stage1.h"
#include "npc_dialogue.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    bool quit = false;
    SDL_Event event;

    // Game
    Game *game = new Game();
    game->drawIcon();

    // Audio
    int test = Mix_Init(0); // Initialize audio in wav format
                            // somehow other formats don't work but here's the code:
                            // wav = 0, flac = 1, mp3 = 8
    Audio::playBGM("res/Audio/MidnightTripLofi.wav");

    // Player + Hud
    Player *player0 = new Player();
    player0->initPlayer(game->getRenderer());
    Hud *hud0 = new Hud(game->getRenderer(), player0);

    // Stage 1
    Stage1 *stage1 = new Stage1();
    stage1->initBlocks(game->getRenderer());

    // Event
    // EventTrigger *allEvent[1];
    // allEvent[0] = new EventTrigger(100, 100, 100, 100);
    // allEvent[0]->setEvent([](Player *player) {
    //     std::cout << "yee \n";
    // });

    std::cout << "before decor \n";

    // DECORATION
    std::vector<Decoration*> staticBack;
    staticBack.push_back(new Decoration("res/DayNight/Day.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    staticBack.push_back(new Decoration("res/DayNight/Night.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    staticBack.push_back(new Decoration("res/Background/MountainDay.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    staticBack.push_back(new Decoration("res/Background/MountainNight.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    staticBack.push_back(new Decoration("res/Decoration/House1.png", 0, 0, 1000, 770));
    staticBack.push_back(new Decoration("res/Decoration/House1Dark.png", 0, 0, 1000, 770));

    // =====================================================
    // std::vector<DecorationDynamic*> dynamicBack;
    // dynamicBack.push_back(new DecorationDynamic(game->getRenderer(), "res/Fire.png", 1100, 342, 74, 154, 10, 8, 1, false));
    // =====================================================
    // Map Decoration
    std::vector<Decoration*> staticFront;
    staticFront.push_back(new Decoration("res/BlockTile/Grass1.png", 1, 1, 1, 1));
    staticFront.push_back(new Decoration("res/BlockTile/Grass2.png", 1, 1, 1, 1));
    staticFront.push_back(new Decoration("res/BlockTile/Tree1.png", 1, 1, 1, 1));
    staticFront.push_back(new Decoration("res/BlockTile/Bridge1.png", 1, 1, 1, 1));
    staticFront.push_back(new Decoration("res/BlockTile/Grass3.png", 1, 1, 1, 1));

    for (Decoration *sBack : staticBack)
        sBack->initDecoration(game->getRenderer());

    for (Decoration *sFront : staticFront)
        sFront->initDecoration(game->getRenderer());

    // NPCS DIALOGUE
    std::vector<NpcDialogue *> npcs;
    npcs.push_back(new NpcDialogue("res/NpcDialogue/Npc2/Squid.png", "res/NpcDialogue/Npc2/DemoNakuBubble1.png",
                                    920, 190, 128, 128, 200, 200, 480, 225, 32, 32, 4, 25, 0, 0, 230));
    
    for (NpcDialogue *npc : npcs)
        npc->initNpc(game->getRenderer());

    // Game loop
    float time = 0;
    float time_max = 600;
    short dayForward = 1;

    // I have no fucking clue why i need this delay
    SDL_Delay(1000);

    staticBack[0]->setAbs(true);
    staticBack[1]->setAbs(true);
    staticBack[2]->setAbs(true);
    staticBack[3]->setAbs(true);

    bool pause;
    while (!quit)
    {
        // EXPERIMENTATION
        if (time > time_max) dayForward = -1;
        if (time < 0) dayForward = 1;
        time += dayForward;

        staticBack[1]->setAlpha(time / time_max * 250);
        staticBack[3]->setAlpha(time / time_max * 250);
        staticBack[5]->setAlpha(time / time_max * 150);

        // SDL and shit
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_p:
                    pause = !pause;
                    std::cout << (pause ? "Continue" : "Pause") << std::endl;
                        break;
                    default:
                        break;
                case SDLK_ESCAPE:
                    quit = true;
            }
        }

        // ====Pausing====
        if (pause) continue;

        // Logging Player (i want my log in her)
        // std::cout << player0->getX() << " " << player0->getY() << "\n";

        // Update
        SDL_SetRenderDrawColor(game->getRenderer(), 0, 150, 200, 255);
        SDL_RenderClear(game->getRenderer());

        // Draw Decoration (back)
        for (Decoration *decor : staticBack)
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        // for (DecorationDynamic *decor : dynamicBack) 
        //     decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        // Npc Dialogue logic and shit idc
        for (NpcDialogue *npc : npcs)
            npc->drawNpc(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        // Update player
        player0->playerUpdate(game->getRenderer(), stage1->getBlockVec());

        // Draw block
        for (Block *block : stage1->getBlockVec())
            block->renderBlock(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        // Draw Decoration (front)
        for (Decoration *decor : staticFront)
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        // Draw Hud
        hud0->draw(game->getRenderer());

        // SDL and shit
        SDL_RenderPresent(game->getRenderer());
        game->frameHandler(game->getDELAYTIME());
    }

    SDL_DestroyRenderer(game->getRenderer());
    SDL_DestroyWindow(game->getWindow());
    SDL_Quit();

    return EXIT_SUCCESS;
}
