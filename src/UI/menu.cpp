#include <UI/menu.h>

void ButtonUI::update(Input *INPUT)
{

    if (INPUT->mouse.L.state) hold = 1;

    if (INPUT->mouse.L.state && hold &&
        INPUT->mouse.inbox(box))
    {
        press = 1;
        hold = 0;
    }
}

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