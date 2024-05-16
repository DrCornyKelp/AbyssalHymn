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

    // Draw 1P BUTTONS
    ObjectBox box1P = {
        CFG->HEIGHT/2 - 20, CFG->HEIGHT/2 - 100,
        CFG->WIDTH/2 - 180, CFG->WIDTH/2 + 180
    };
    bool hover1P = INPUT.mouse.inbox(box1P);
    button1P.update(hover1P, Object2D::BoxToSDLRect(box1P));

    // Draw 2P Button
    ObjectBox box2P = {
        CFG->HEIGHT/2 + 100, CFG->HEIGHT/2 + 20,
        CFG->WIDTH/2 - 180, CFG->WIDTH/2 + 180
    };
    bool hover2P = INPUT.mouse.inbox(box2P);
    button2P.update(hover2P, Object2D::BoxToSDLRect(box2P));

    if (hover1P &&
        INPUT.mouse.L.state && 
        !CFG->TRANSIT_EFFECT.active)
    {
        CFG->TRANSIT_EFFECT.set(100, 30);
        finish = 1;
    };

    if (hover2P &&
        INPUT.mouse.L.state && 
        !CFG->TRANSIT_EFFECT.active)
    {
        CFG->TRANSIT_EFFECT.set(100, 30);
        finish = 1;
        multi = 1;
    };

    if (CFG->TRANSIT_EFFECT.midpoint() && finish)
        CFG->STATE = 1;
}