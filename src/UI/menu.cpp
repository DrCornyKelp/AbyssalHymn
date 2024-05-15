#include <UI/menu.h>

void MenuButton::update(bool hover, SDL_Rect rect)
{
    if ((hover && hover_alpha < 255) ||
        hover_alpha < hover_min)
        hover_alpha += 5;
    else if (hover_alpha > hover_min)
        hover_alpha -= 5;

    SDL_SetTextureAlphaMod(texture, hover_alpha);
    SDL_RenderCopy(CFG->RENDERER, texture, NULL, &rect);
}

Menu::Menu() {
    INPUT.setTemplate(0);
}

void Menu::update()
{
    INPUT.update();

    // Draw Background
    Object2D::objectSetSprite(menuBGsprite);
    SDL_RenderCopy(CFG->RENDERER, menuBGframe[menuBGsprite.si], NULL, NULL);

    // Draw UI BUTTONS
    ObjectBox boxStart = {
        CFG->HEIGHT/2 + 48, CFG->HEIGHT/2 - 48,
        CFG->WIDTH/2 - 128, CFG->WIDTH/2 + 128
    };
    bool hoverStart = INPUT.mouse.inbox(boxStart);
    buttonStart.update(hoverStart, Object2D::BoxToSDLRect(boxStart));
    if (hoverStart && INPUT.mouse.L.state && !CFG->TRANSIT_EFFECT.active)
    {
        CFG->TRANSIT_EFFECT.set(100, 30);
    };

    if (CFG->TRANSIT_EFFECT.midpoint()) end = 1;
}