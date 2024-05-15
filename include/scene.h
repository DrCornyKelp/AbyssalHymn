#ifndef SCENE_H
#define SCENE_H

#include <input.h>

class Object2D;
class Scene
{
private:
    short menu_counter = 0;
    
    bool pressed = false;

    // Placeholder input for easy access
    Input *input;
    
    // Textures
    SDL_Texture *main_bg;
    SDL_Texture *pause_bg;
    SDL_Texture *button_sheet;
    SDL_Texture *button_high_sheet;

    SDL_Rect srcRect;
    SDL_Rect desRect;
public:
    short game_state = 0;   // 0: Main Menu
                            // 1: Gameplay
                            // 2: Pause
                            // 3: Quit

    // SDL_Texture *getMainBg();
    // SDL_Texture *getPauseBg();

    void initScenes(Input *in);

    // Navigation (Button only)
    void naviMainMenu();
    void naviPauseMenu();

    // Render (option menu for keymapping soon?)
    void renderMainMenu();
    void renderPauseMenu();
};

#endif