#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <chrono>
#include <windows.h>
#include <iostream>
#include <vector>
#include <stdio.h>

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
    int test = Mix_Init(0); // Initialize audio in wav format
                            // somehow other formats don't work but here's the code:
                            // wav = 0, flac = 1, mp3 = 8

    bool quit = false;
    SDL_Event event;

    // Game
    Game *game = new Game();
    game->drawIcon();

    // Audio
    Audio::playBGM("res/Audio/Stage1.wav");

    // Player + Hud
    Player *player0 = new Player();
    player0->initPlayer(game->getRenderer());
    Hud *hud0 = new Hud(game->getRenderer(), player0);

    // Block
    Block *allBlock[4];
    allBlock[0] = new Block(100, 200);
    allBlock[1] = new Block(770, 340, 240, 64, false);
    allBlock[2] = new Block(770, 480, 240, 64);
    allBlock[3] = new Block(640, 64, 128000, 128);

    for (Block *block : allBlock)
    {
        block->initBlock(game->getRenderer(), "res/Grass.png");
    }

    // Event
    // EventTrigger *allEvent[1];
    // allEvent[0] = new EventTrigger(100, 100, 100, 100);
    // allEvent[0]->setEvent([](Player *player) {
    //     std::cout << "yee \n";
    // });

    // BG
    Sprite *bg = new Sprite(2880, 1600, 1, "res/IdiotBackground.jpg");
    bg->setTexture(bg->loadTexture(game->getRenderer(), bg->getSpritePath()));

    // DECORATION
    DecorationStatic *staticBack[4];
    staticBack[0] = new DecorationStatic(game->getRenderer(), "res/Decoration/House1.png", 550, 513, 1000, 770, false);
    staticBack[1] = new DecorationStatic(game->getRenderer(), "res/Decoration/TreeX2.png", 132, 64, 64, 128, false);
    staticBack[2] = new DecorationStatic(game->getRenderer(), "res/Decoration/Pole.png", 540, 0, 98, 196, false);
    staticBack[3] = new DecorationStatic(game->getRenderer(), "res/Grass.png", 640, 64, 1280, 128, false);

    DecorationDynamic *dynamicBack[3];
    dynamicBack[0] = new DecorationDynamic(game->getRenderer(), "res/NakuSheet/NakuLeft.png", 870, 180, 32, 32, 30, 2, 4, false);
    dynamicBack[0]->setAlpha(200);
    dynamicBack[1] = new DecorationDynamic(game->getRenderer(), "res/Fire.png", 540, 240, 74, 154, 10, 8, 1, false);
    dynamicBack[2] = new DecorationDynamic(game->getRenderer(), "res/Sun.png", 1100, -70, 64, 64, 30, 2, 4, true);

    DecorationStatic *staticFront[2];
    staticFront[0] = new DecorationStatic(game->getRenderer(), "res/Decoration/House1_Rail.png", 550, 513, 1000, 770, false);
    staticFront[1] = new DecorationStatic(game->getRenderer(), "res/Lighttest.png", 0, 0, game->getWIDTH(), game->getHEIGHT(), true);
    staticFront[1]->setAlpha(0);

    // Game loop
    float time = 0;
    float time_max = 1200;
    bool pause;

    while (!quit)
    {
        // time++;
        // staticFront[0]->setAlpha(time / time_max * 255);

        // Event handler
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
        SDL_RenderClear(game->getRenderer());

        SDL_Rect bgRect = {-100, -500, 2880, 1600};
        SDL_RenderCopy(game->getRenderer(), bg->getTexture(), NULL, &bgRect);

        for (DecorationStatic *decor : staticBack) {
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        }
        for (DecorationDynamic *decor : dynamicBack) {
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        }

        // for (Block *block : allBlock)
        // {
        //     block->renderBlock(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        // }
        
        player0->playerUpdate(game->getRenderer(), allBlock);

        for (DecorationStatic *decor : staticFront) {
            decor->draw(game->getRenderer(), player0->getX(), player0->getY(), player0->getFocusX(), player0->getOffsetX(), player0->getFocusY(), player0->getOffsetY());
        }

        hud0->draw(game->getRenderer());

        SDL_RenderPresent(game->getRenderer());

        game->frameHandler(game->getDELAYTIME());
    }

    SDL_DestroyRenderer(game->getRenderer());
    SDL_DestroyWindow(game->getWindow());
    SDL_Quit();

    return EXIT_SUCCESS;
}
