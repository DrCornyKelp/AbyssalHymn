#include <input.h>

void Input::initInput()
{
    // Initialize input
    for (int i = 0; i < 12; i++)
        button.push_back(false);
}

bool Input::input(SDL_GameController *controller)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return true;
                break;
            case SDLK_w:
                button[0] = true;
                break;
            case SDLK_s:
                button[1] = true;
                break;
            case SDLK_a:
                button[2] = true;
                break;
            case SDLK_d:
                button[3] = true;
                break;
            case SDLK_SPACE:
                button[4] = true;
                break;
            case SDLK_LSHIFT:
                button[5] = true;
                break;
            case SDLK_l:
                button[6] = true;
                break;
            case SDLK_q:
                button[7] = true;
                break;
            case SDLK_e:
                button[8] = true;
                break;
            case SDLK_g:
                button[9] = true;
                break;
            case SDLK_h:
                button[10] = true;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                button[0] = false;
                break;
            case SDLK_s:
                button[1] = false;
                break;
            case SDLK_a:
                button[2] = false;
                break;
            case SDLK_d:
                button[3] = false;
                break;
            case SDLK_SPACE:
                button[4] = false;
                break;
            case SDLK_LSHIFT:
                button[5] = false;
                break;
            case SDLK_l:
                button[6] = false;
                break;
            case SDLK_q:
                button[7] = false;
                break;
            case SDLK_e:
                button[8] = false;
                break;
            case SDLK_g:
                button[9] = false;
                break;
            case SDLK_h:
                button[10] = false;
                break;
            }
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            switch (event.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                button[0] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                button[1] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                button[2] = true;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                button[3] = true;
                break;
            case SDL_CONTROLLER_BUTTON_A:
                button[4] = true;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                button[5] = true;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                button[6] = true;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                button[7] = true;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                button[8] = true;
                break;
            }
            break;
        case SDL_CONTROLLERBUTTONUP:
            switch (event.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                button[0] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                button[1] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                button[2] = false;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                button[3] = false;
                break;
            case SDL_CONTROLLER_BUTTON_A:
                button[4] = false;
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                button[5] = false;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                button[6] = false;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                button[7] = false;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                button[8] = false;
                break;
            }
            break;
        }
    }

    return false;  
}

bool Input::getButton(int i)
{
    return button[i];
}