#include <scene.h>
#include <object2D.h>

SDL_Texture *Scene::getMainMenuBg()
{
    return main_menu_bg;
}

SDL_Texture *Scene::getLevelSelectBg()
{
    return level_select_bg;
}

// Main Menu
void Scene::initMainMenuBg(const char *path)
{
    main_menu_bg = Object2D::loadTexture(path);
}

// Level Select Menu
void Scene::initLevelSelectBg(const char *path)
{
    level_select_bg = Object2D::loadTexture(path);
}

void Scene::mainMenuNavi(Input *input)
{
    if (input->getKeyHold(0) && menu_counter > 0) menu_counter--;
    if (input->getKeyHold(1) && menu_counter < 1) menu_counter++;
    if (input->getKeyHold(4) && menu_counter == 0) game_state = 2;
    if (input->getKeyHold(4) && menu_counter == 1) game_state = 2;
    if (input->getKeyHold(4) && menu_counter == 2) game_state = 3;
}