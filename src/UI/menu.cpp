#include <UI/menu.h>

Menu::Menu() {
    INPUT.setTemplate(0);
}

void Menu::update()
{
    INPUT.update();

    Object2D::objectSetSprite(sprite);

    SDL_RenderClear(CFG->RENDERER);
    SDL_RenderCopy(CFG->RENDERER, menuBGframe[sprite.si], NULL, NULL);
}