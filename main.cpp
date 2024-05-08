#include <scene.h>
#include <hud.h>
#include <renderer.h>
#include <world.h>

#include <developer/editor.h>
#include <developer/console.h>

#include <audio.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_GAMECONTROLLER);

    bool quit = false;
    SDL_Event event;

    // Game
    CFG->drawIcon();

    // Audio Handler
    Audio *audio = new Audio();

    // Input Handler
    Input *input = new Input();
    input->initInput();

    // Renderer
    Renderer *rend = new Renderer();

    // Player + Hud
    Player *player = new Player();
    player->initPlayer();
    Hud *hud = new Hud(player);

    // Collision
    Collision *collision = new Collision();

    // ZA WARUDO
    World *world = new World({
        // Void
        new Map("Tutorial1"), // 0 (this is going to be a default map)
        // Tutorial
        new Map("Tutorial1"), // 1
        new Map("Tutorial2"), // 2
        new Map("Tutorial3"), // 3
        new Map("Tutorial4"), // 4
        // Lobby
        new Map("LobbyOutside"), // 5
        new Map("LobbyInside"), // 6
        // Main Map
        new Map("SunlightValley"), // 7
        new Map("SnowyCanyon"), // 8
        new Map("DustyMirage"), // 9
        new Map("AncientEmrald"), // 10
        new Map("DeepCavern"), // 11
        new Map("DeadAhead"), // 12
        new Map("SeaHorizon"), // 13
        new Map("CloudHighway") // 14
    });
    world->initWorld(player, audio, input, collision,
        {1, 7, 2, 1}
    );

    // Console Command
    Console *console = new Console(world, input, player, collision);
    // Map editor
    Editor *editor = new Editor(console, world, input, player, collision);

    bool pause = false;
    while (!input->input())
    {
        // Devlog
        CFG->printDevlog();
        CFG->DEVLOG = "";

        // Main
        // audio->updateTrack();
        world->updateWorld();
        rend->renderGameplay(world->MapCurrent, hud);
        player->playerDeveloper(world->MapCurrent);

        // Console + Editor
        editor->update();
        console->update();

        // FUN STUFF XD
        if (input->getKeyPress(13))
        {
            input->setKeyHold(13, 1);
            player->setVelY(8);
            player->setVelX(-20);
        }
        if (input->getKeyPress(14))
        {
            input->setKeyHold(14, 1);
            player->setVelY(8);
            player->setVelX(20);
        }

        // SDL and shit
        SDL_RenderPresent(CFG->RENDERER);
        CFG->frameHandler(CFG->DELAY_TIME);
    }

    // Clean up
    delete  world, audio, input, CFG,
            collision, hud, rend,
            player;

    SDL_DestroyRenderer(CFG->RENDERER);
    SDL_DestroyWindow(CFG->WINDOW);
    SDL_Quit();

    return EXIT_SUCCESS;
}