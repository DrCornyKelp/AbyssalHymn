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
    Audio *AUDIO = new Audio();

    // Renderer
    Renderer *REND = new Renderer();

    // Multiplayer (can support single player dont worry)
    Multiplayer *MULTI = new Multiplayer({new Player()});

    // Collision
    Collision *COLLI = new Collision();

    // ZA WARUDO
    World *WORLD = new World({
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
    WORLD->initWorld(MULTI, AUDIO, COLLI);

    // Console Command
    Console *CONSOLE = new Console(WORLD, MULTI->MAIN, COLLI);
    // Map editor
    Editor *EDITOR = new Editor(CONSOLE, WORLD, MULTI->MAIN, COLLI);

    // Play Intro Sequence
    Intro *intro = new Intro();
    // while (!intro->finish)
    // {
    //     SDL_RenderClear(CFG->RENDERER);
    //     intro->update();
    //     CFG->postupdate();
    // }
    delete intro;

    Menu *menu = new Menu();
    while (!menu->end)
    {
        SDL_RenderClear(CFG->RENDERER);

        menu->update();
        if (menu->multi) 
        {
            menu->multi = 0;
            MULTI->addPlayer();
        };

        CFG->postupdate();
    }

    WORLD->switchMap({1, 7, 2, 1});

    while (!MULTI->MAIN->INPUT.escape.state)
    {
        // Devlog
        CFG->printDevlog();
        CFG->DEVLOG = "";

        // Main
        // audio->updateTrack();
        WORLD->updateWorld();
        MULTI->MAIN->playerDeveloper(WORLD->MapCurrent);
        REND->renderGameplay(WORLD->MapCurrent);

        // Console + Editor
        EDITOR->update();
        CONSOLE->update();

        // Config
        CFG->postupdate();
    }

    // Clean up
    delete WORLD, CFG, REND, EDITOR, CONSOLE;

    SDL_Quit();

    return EXIT_SUCCESS;
}