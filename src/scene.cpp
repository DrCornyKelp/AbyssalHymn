#include "scene.h"

Sprite *Scene::getMainMenuBg()
{
    return main_menu_bg;
}

Sprite *Scene::getLevelSelectBg()
{
    return level_select_bg;
}

// Main Menu
void Scene::initMainMenuBg(SDL_Renderer *renderer, const char *path)
{
    main_menu_bg = new Sprite(Game::WIDTH, Game::HEIGHT, 1, path);
    main_menu_bg->setTexture(Sprite::loadTexture(renderer, main_menu_bg->getSpritePath()));
}

// Level Select Menu
void Scene::initLevelSelectBg(SDL_Renderer *renderer, const char *path)
{
    level_select_bg = new Sprite(Game::WIDTH, Game::HEIGHT, 1, path);
    level_select_bg->setTexture(Sprite::loadTexture(renderer, level_select_bg->getSpritePath()));
}

void Scene::mainMenuNavi(Input *input)
{
    if (input->getButton(0) && menu_counter > 0) menu_counter--;
    if (input->getButton(1) && menu_counter < 1) menu_counter++;
    if (input->getButton(4) && menu_counter == 0) game_state = 2;
    if (input->getButton(4) && menu_counter == 1) game_state = 2;
    if (input->getButton(4) && menu_counter == 2) game_state = 3;
    std::cout << menu_counter << "\n";
}