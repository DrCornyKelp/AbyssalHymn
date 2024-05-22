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

    CFG->TRANSIT_EFFECT.BLACKSCREEN = CFG->loadTexture("assets/BlackScreen.png");

    // Renderer
    Renderer *REND = new Renderer();

    // Audio Handler
    Audio *AUDIO = new Audio();
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
    while (!intro->finish)
    {
        SDL_RenderClear(CFG->RENDERER);
        intro->update();
        CFG->postupdate();
    }
    delete intro;

    // Menu
    Menu *MENU = new Menu();
    Pause *PAUSE = new Pause(WORLD);

    while (!CFG->QUIT)
    {
        switch (CFG->STATE)
        {
        case 0:
            SDL_RenderClear(CFG->RENDERER);

            MENU->update();
            if (MENU->multi) 
            {
                MENU->multi = 0;
                MULTI->addPlayer();
                MULTI->MAIN->INPUT.setTemplate(0);
            };

            if (CFG->TRANSIT_EFFECT.leftactive())
                WORLD->switchMap({1, 7, 2, 1});
            break;

        case 1:
            // Devlog
            CFG->printDevlog();
            CFG->DEVLOG = "";

            // Main
            WORLD->updateWorld();
            REND->renderGameplay(WORLD->MapCur);

            // Console + Editor
            EDITOR->update();
            CONSOLE->update();

            if (MULTI->MAIN->INPUT.escape.press())
            {
                MULTI->MAIN->INPUT.escape.hold = 1;
                CFG->STATE = 2;
                PAUSE->transit_time = 0;
                PAUSE->end_pause = 0;
            }

            break;

        case 2:
            // Render what currently onscreen
            REND->renderGameplay(WORLD->MapCur);
            MULTI->MAIN->INPUT.update();

            PAUSE->update(&MULTI->MAIN->INPUT);

            break;
        }

        // Config
        CFG->postupdate();
    }

    // Clean up
    delete WORLD, CFG, REND, EDITOR, CONSOLE;

    SDL_Quit();

    return EXIT_SUCCESS;
}