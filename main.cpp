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
    Audio::playBGM("res/Audio/KoiIsLoveLofi.wav");

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

    // BACK DECROATION
    std::vector<Decoration*> decor_back;
    // decor_back.push_back(new Decoration("res/DayNight/Day.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    // decor_back.push_back(new Decoration("res/DayNight/Night.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    decor_back.push_back(new Decoration("res/Background/MountainDay.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    // decor_back.push_back(new Decoration("res/Background/MountainNight.png", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    // decor_back.push_back(new Decoration("res/Background/River.jpg", 0, 0, game->getWIDTH(), game->getHEIGHT()));
    decor_back.push_back(new Decoration("res/Decoration/House1.png", 0, 128, 1000, 770));
    // decor_back.push_back(new Decoration("res/Decoration/House1Dark.png", 0, 128, 1000, 770));
    decor_back.push_back(new Decoration("res/Fire.png", 890, 190, 74, 154, 74, 154, 8, 10));

    for (Decoration *sBack : decor_back)
        sBack->initDecoration(game->getRenderer());

    // NPCS DIALOGUE
    std::vector<NpcDialogue *> npcs;
    npcs.push_back(new NpcDialogue("res/NpcDialogue/Npc2/Squid.png", "res/NpcDialogue/Npc2/SquidJumpTutorial.png",
        920, 190, 128, 128, 200, 200, 300, 138, 32, 32, 4, 25, 0, 0, 230));
    
    for (NpcDialogue *npc : npcs)
        npc->initNpc(game->getRenderer());

    // Game loop
    float time = 0;
    float time_max = 100;
    short dayForward = 1;

    // I have no fucking clue why i need this delay
    SDL_Delay(1000);

    decor_back[0]->setAbs(true);
    // decor_back[1]->setAbs(true);
    // decor_back[2]->setAbs(true);
    // decor_back[3]->setAbs(true);

    bool pause;
    while (!quit)
    {

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

        // EXPERIMENTATION
        if (time > time_max) dayForward = -1;
        if (time < 0) dayForward = 1;
        time += dayForward;

        // decor_back[1]->setAlpha(time / time_max * 250);
        // decor_back[3]->setAlpha(time / time_max * 250);
        // decor_back[5]->setAlpha(time / time_max * 150);

        // Update
        SDL_SetRenderDrawColor(game->getRenderer(), 0, 150, 200, 255);
        SDL_RenderClear(game->getRenderer());

        // Draw Decoration (back)
        for (Decoration *decor : decor_back)
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        // Npc Dialogue logic and shit idc
        for (NpcDialogue *npc : npcs)
            npc->drawNpc(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        // Update block
        for (Block *block : stage1->getBlockVec())
        {    
            if (block->getMoving()) block->setVelY(dayForward);

            block->updateBlock(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        }

        for (int i = 0; i < 200; i++)
        {
            SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
            int drawX = player0->getFocusX() ? i * 64 + player0->getOffsetX() - player0->getX() : i * 64;
            int drawY = player0->getFocusY() ? i * 64 + player0->getOffsetY() - player0->getY() : i * 64;

            SDL_RenderDrawLine(game->getRenderer(), 0, 720 - drawY, Game::WIDTH, 720 - drawY);  
            SDL_RenderDrawLine(game->getRenderer(), drawX, 0, drawX, Game::HEIGHT);
        }

        // Update player
        player0->playerUpdate(game->getRenderer(), stage1->getBlockVec());

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
