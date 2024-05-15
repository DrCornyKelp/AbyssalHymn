#include <renderer.h>
#include <audio.h>

#include <UI/intro.h>
#include <UI/pause.h>
#include <UI/menu.h>

#include <developer/editor.h>
#include <developer/console.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_GAMECONTROLLER);

    CFG->TRANSIT_EFFECT.BLACKSCREEN = CFG->loadTexture("res/BlackScreen.png");

    // Audio Handler
    Audio *audio = new Audio();

    // Renderer
    Renderer *rend = new Renderer();

    // Player + Hud
    Player1D PlayerVec;

    int playercount = 1;
    // std::cout << "SET PLAYER COUNT: ";
    // std::cin >> playercount;
    // std::cout << "Welcome \n";

    for (int i = 0; i < playercount; i++)
        PlayerVec.push_back(new Player());
    Multiplayer *multi = new Multiplayer(PlayerVec);

    // Collision
    Collision *collision = new Collision();

    // ZA WARUDO
    World *world = new World({
        // Void
        new Map("Tutorial1"), // 0 (Default)
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
    world->initWorld(multi, audio, collision);

    // Console Command
    Console *console = new Console(world, multi->MAIN, collision);
    // Map editor
    Editor *editor = new Editor(console, world, multi->MAIN, collision);

    // Play Intro Sequence
    Intro *intro = new Intro();
    while (!intro->finish)
    {
        SDL_RenderClear(CFG->RENDERER);
        intro->update();
        CFG->frameHandler();
        SDL_RenderPresent(CFG->RENDERER);
    }

    Menu *menu = new Menu();
    while (!menu->end)
    {
        SDL_RenderClear(CFG->RENDERER);

        menu->update();

        CFG->TRANSIT_EFFECT.update();
        CFG->frameHandler();
        SDL_RenderPresent(CFG->RENDERER);
    }

    world->switchMap({1, 7, 2, 1});

    while (!multi->MAIN->INPUT.escape.state)
    {
        // Devlog
        CFG->printDevlog();
        CFG->DEVLOG = "";

        // Main
        // audio->updateTrack();
        world->updateWorld();
        multi->MAIN->playerDeveloper(world->MapCurrent);
        rend->renderGameplay(world->MapCurrent);

        // Console + Editor
        editor->update();
        console->update();

        // Config
        CFG->TRANSIT_EFFECT.update();
        CFG->frameHandler();
        SDL_RenderPresent(CFG->RENDERER);
    }

    // Clean up (REMEMBER TO ADD PLAYER CLEAN UP AS WELL)
    delete  world, audio, CFG,
            collision, rend, multi;

    SDL_Quit();

    return EXIT_SUCCESS;
}