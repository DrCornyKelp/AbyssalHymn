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
#include "input.h"
#include "scene.h"
#include "player.h"
#include "hud.h"
#include "audio.h"
#include "renderer.h"

#include "map/map1.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_GAMECONTROLLER);

    bool quit = false;
    SDL_Event event;

    // Game
    Game *game = new Game();
    game->drawIcon();

    // Scene Switching
    Scene *scene = new Scene();
    scene->game_state = 0;
    scene->initMainMenuBg(game->getRenderer(), "res/Menu/Main.png");
    scene->initLevelSelectBg(game->getRenderer(), "res/Menu/LevelSelect.png");

    // Input Handler
    Input *input = new Input();
    input->initInput();

    // Controller Detection
    SDL_GameController *controller;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Check for controller support
    if (SDL_NumJoysticks() < 1)
        printf("No controller connected!\n");
    else
    {
        controller = SDL_GameControllerOpen(0);
        // Open controller devices
        if (controller == NULL)
            printf("Failed to open controller: %s\n", SDL_GetError());
        else
            printf("Controller connected!\n");
    }

    // Audio
    int test = Mix_Init(0); // wav = 0, flac = 1, mp3 = 8
    Audio::playBGM("res/Audio/BGM/StringTheory.wav");

    // Player + Hud
    Player *player0 = new Player();
    player0->initPlayer(game->getRenderer());
    Hud *hud0 = new Hud(game->getRenderer(), player0);

    // Renderer
    Renderer *rend = new Renderer();

    // Stage 1
    Map1 *map1 = new Map1();
    map1->initAll(game->getRenderer(), player0);

    bool pause = false;
    while (!input->input(controller))
    {
        input->input(controller);
        scene->mainMenuNavi(input);

        switch(scene->game_state)
        {
            case 0:
                rend->renderMainMenu(game->getRenderer(), scene);
                break;
            case 1:
                rend->renderLevelSelectMenu(game->getRenderer(), scene);
                break;
            case 2:
                // Update
                SDL_SetRenderDrawColor(game->getRenderer(), 62, 46, 83, 255);
                SDL_RenderClear(game->getRenderer());

                // Update Map
                map1->updateMapExclusive(game->getRenderer(), player0, input);
                // Render the game
                rend->renderGameplay(game->getRenderer(), player0, map1);

                // Draw Hud
                hud0->update(game->getRenderer());
                break;
            // case 3:
            //     rend->renderMainMenu(game->getRenderer(), pause_menu);
            //     break;
            default:
                break;
        }

        // SDL and shit
        SDL_RenderPresent(game->getRenderer());
        game->frameHandler(game->getDELAYTIME());
    }

    SDL_DestroyRenderer(game->getRenderer());
    SDL_DestroyWindow(game->getWindow());
    SDL_Quit();

    return EXIT_SUCCESS;
}