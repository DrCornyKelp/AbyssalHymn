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
#include "decoration_static.h"
// #include "event_trigger.h"
#include "hud.h"
#include "audio.h"

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
    Audio::playBGM("res/Audio/ComfortChain.wav");

    // Player + Hud
    Player *player0 = new Player();
    player0->initPlayer(game->getRenderer());
    Hud *hud0 = new Hud(game->getRenderer(), player0);

    // Block
    Block *allBlock[4];
    allBlock[0] = new Block(770, 330, 240, 64, false);
    allBlock[1] = new Block(755, 480, 210, 64);
    // Boundary
    allBlock[2] = new Block(-40, 800, 80, 1600);
    // Gorund
    allBlock[3] = new Block(640, 64, 1280, 128); 

    for (Block *block : allBlock)
        block->initBlock(game->getRenderer(), "res/WhiteSpace.png");

    // Event
    // EventTrigger *allEvent[1];
    // allEvent[0] = new EventTrigger(100, 100, 100, 100);
    // allEvent[0]->setEvent([](Player *player) {
    //     std::cout << "yee \n";
    // });

    // BG
    // Sprite *bg = new Sprite(756, 360, 1, "res/Background/Mountain.png");
    // bg->setTexture(bg->loadTexture(game->getRenderer(), bg->getSpritePath()));

    // DECORATION
    DecorationStatic *staticBack[5];
    staticBack[0] = new DecorationStatic(game->getRenderer(), "res/DayNight/Day.png", 0, 0, game->getWIDTH(), game->getHEIGHT(), true);
    staticBack[1] = new DecorationStatic(game->getRenderer(), "res/DayNight/Night.png", 0, 0, game->getWIDTH(), game->getHEIGHT(), true);
    staticBack[1]->setAlpha(0);
    staticBack[2] = new DecorationStatic(game->getRenderer(), "res/Background/MountainDay.png", 0, 0, game->getWIDTH(), game->getHEIGHT(), true);
    staticBack[3] = new DecorationStatic(game->getRenderer(), "res/Background/MountainNight.png", 0, 0, game->getWIDTH(), game->getHEIGHT(), true);
    staticBack[3]->setAlpha(0);
    staticBack[4] = new DecorationStatic(game->getRenderer(), "res/Decoration/House1.png", 550, 510, 1000, 770, false);

    DecorationDynamic *dynamicBack[1];
    dynamicBack[0] = new DecorationDynamic(game->getRenderer(), "res/NakuSheet/NakuLeft.png", 870, 164, 32, 32, 30, 2, 4, false);
    dynamicBack[0]->setAlpha(200);
    // dynamicBack[1] = new DecorationDynamic(game->getRenderer(), "res/Fire.png", 540, 240, 74, 154, 10, 8, 1, false);
    // dynamicBack[1] = new DecorationDynamic(game->getRenderer(), "res/Sun.png", 1100, -70, 64, 64, 30, 2, 4, true);

    DecorationStatic *staticFront[1];
    staticFront[0] = new DecorationStatic(game->getRenderer(), "res/BlockTile/Grass.png", 630, 80, 1300, 196, false);

    // Game loop
    float time = 0;
    float time_max = 600;
    short dayForward = 1;

    // I have no fucking clue why i need this delay
    SDL_Delay(1000);

    bool pause;
    while (!quit)
    {
        // EXPERIMENTATION
        if (time > time_max) dayForward = -1;
        if (time < 0) dayForward = 1;
        time += dayForward;

        staticBack[1]->setAlpha(time / time_max * 250);
        staticBack[3]->setAlpha(time / time_max * 250);

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

        // Menu handler

        // ====Pausing====
        if (pause) continue;

        // Logging Player (i want my log in her)
        // std::cout << player0->getX() << " " << player0->getY() << "\n";

        // Update
        SDL_SetRenderDrawColor(game->getRenderer(), 0, 150, 200, 255);
        SDL_RenderClear(game->getRenderer());

        // Draw Background
        // SDL_Rect bgDestRect = {player0->getX() * 0.04 - 300, 0, game->getWIDTH() * 1.3, game->getHEIGHT() * 1.2};
        // SDL_RenderCopy(game->getRenderer(), bg->getTexture(), NULL, &bgDestRect);

        // Draw Decoration (back)
        for (DecorationStatic *decor : staticBack)
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        for (DecorationDynamic *decor : dynamicBack) 
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());

        // Draw block
        // for (Block *block : allBlock)
        //     block->renderBlock(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        
        // Update player
        player0->playerUpdate(game->getRenderer(), allBlock);

        // Draw Decoration (front)
        for (DecorationStatic *decor : staticFront)
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
