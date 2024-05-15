#include <scene.h>

// SDL_Texture *Scene::getMainBg() { return main_bg; }
// SDL_Texture *Scene::getPauseBg() { return pause_bg; }

void Scene::initScenes(Input *in)
{
    input = in;

    main_bg = Object2D::loadTexture("res/Menu/main.png");
    pause_bg = Object2D::loadTexture("res/Menu/pause.png");
    button_sheet = Object2D::loadTexture("res/Menu/button_silver.png");
    button_high_sheet = Object2D::loadTexture("res/Menu/button_gold.png");
}

void Scene::naviMainMenu()
{
    pressed = false;
    // if (input->getKeyPress(0) && menu_counter > 0)
    // {
    //     input->sethold(0, true);
    //     menu_counter--;
    // }
    // if (input->getKeyPress(1) && menu_counter < 1) 
    // {
    //     input->sethold(1, true);
    //     menu_counter++;
    // }
    // // Play pressed
    // if (input->getKeyPress(4) && menu_counter == 0) 
    // {
    //     input->sethold(4, true);
    //     pressed = true;
    //     game_state = 1;
    //     return;
    // }
    // // Exit pressed
    // if (input->getKeyPress(4) && menu_counter == 1) 
    // {
    //     input->sethold(4, true);
    //     pressed = true;
    //     game_state = 3;
    //     return;
    // }
}

void Scene::naviPauseMenu()
{
    // pressed = false;
    // if (input->getKeyPress(0) && menu_counter > 0)
    // {
    //     input->sethold(0, true);
    //     menu_counter--;
    // }
    // if (input->getKeyPress(1) && menu_counter < 2) 
    // {
    //     input->sethold(1, true);
    //     menu_counter++;
    // }
    // // Continue pressed
    // if (input->getKeyPress(4) && menu_counter == 0) 
    // {
    //     input->sethold(4, true);
    //     pressed = true;
    //     game_state = 1;
    //     return;
    // }
    // // Exit to main pressed
    // if (input->getKeyPress(4) && menu_counter == 1) 
    // {
    //     input->sethold(4, true);
    //     pressed = true;
    //     game_state = 0;
    //     return;
    // }
    // // Exit game pressed
    // if (input->getKeyPress(4) && menu_counter == 2) 
    // {
    //     input->sethold(4, true);
    //     pressed = true;
    //     game_state = 3;
    //     return;
    // }
}

void Scene::renderMainMenu()
{
    // Main menu background
    SDL_RenderCopy(CFG->RENDERER, main_bg, NULL, NULL);

    // Play button
    srcRect = {(pressed && menu_counter == 0) * 222, 0, 222, 108};
    desRect = {275, 275, 222, 108};
    SDL_RenderCopy(CFG->RENDERER, menu_counter == 0 ? button_high_sheet : button_sheet, &srcRect, &desRect);

    // Exit button
    srcRect = {(pressed && menu_counter == 1) * 222, 108, 222, 108};
    desRect = {275, 400, 222, 108};
    SDL_RenderCopy(CFG->RENDERER, menu_counter == 1 ? button_high_sheet : button_sheet, &srcRect, &desRect);
}

void Scene::renderPauseMenu()
{
    // Main menu background
    SDL_RenderCopy(CFG->RENDERER, pause_bg, NULL, NULL);

    // Continue button
    srcRect = {(pressed && menu_counter == 0) * 222, 216, 222, 108};
    desRect = {529, 300, 222, 108};
    SDL_RenderCopy(CFG->RENDERER, menu_counter == 0 ? button_high_sheet : button_sheet, &srcRect, &desRect);

    // Exit to main menu
    srcRect = {(pressed && menu_counter == 1) * 222, 324, 222, 108};
    desRect = {529, 425, 222, 108};
    SDL_RenderCopy(CFG->RENDERER, menu_counter == 1 ? button_high_sheet : button_sheet, &srcRect, &desRect);

    // Exit game
    srcRect = {(pressed && menu_counter == 2) * 222, 108, 222, 108};
    desRect = {529, 550, 222, 108};
    SDL_RenderCopy(CFG->RENDERER, menu_counter == 2 ? button_high_sheet : button_sheet, &srcRect, &desRect);
}