#include <input.h>
#include <player.h>

void KeyState::update(const Uint8* state, bool input_delay)
{
    if (state[code] && !input_delay) key = 1;
    else {
        key = 0; keyhold = 0;
    }

    if (key)
    {
        keythreshold++;
        keythrespeak = 0;
    }
    else if (keythreshold)
    {
        keythrespeak = keythreshold;
        keythreshold = 0;
    };

    if (keydelay) keydelay--;
}
bool KeyState::press() { return key && !keyhold && !keydelay; }
bool KeyState::threspass(int max) { return keythreshold >= max; };

void Input::update()
{
    // Update Delay
    if (input_delay) input_delay--;

    // Update KEYBOARD;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    moveU.update(state, input_delay);
    moveD.update(state, input_delay);
    moveL.update(state, input_delay);
    moveR.update(state, input_delay);
    proj.update(state, input_delay);
    equip.update(state, input_delay);
    attack.update(state, input_delay);
    jump.update(state, input_delay);
    dash.update(state, input_delay);

    lctrl.update(state, input_delay);
    arrowU.update(state, input_delay);
    arrowD.update(state, input_delay);
    arrowL.update(state, input_delay);
    arrowR.update(state, input_delay);

    // Update MOUSE
    Uint32 mouseState = SDL_GetMouseState(&mouse_x, &mouse_y);
}

Input::Input(int keytemplate)
{
    // ============= Initialize Controller ==============
    // Check for controller support
    if (SDL_NumJoysticks() < 1)
        printf("No controller connected!\n");
    else
    {
        controller = SDL_GameControllerOpen(0);
        // Open controller devices
        if (controller == NULL)
            printf("Failed to open controller: %s\n", SDL_GetError());
        else
            printf("Controller connected!\n");
    }

    // Initialize key
    for (int i = 0; i < 20; i++)
    {
        key.push_back(false);
        keyhold.push_back(false);
        keythreshold.push_back(0);
        keythrespeak.push_back(0);
    }

    if (!keytemplate)
    {
        KeyTemplate0 keytemplate;
            moveU = keytemplate.moveU;
            moveD = keytemplate.moveD;
            moveL = keytemplate.moveL;
            moveR = keytemplate.moveR;
            proj = keytemplate.proj;
            equip = keytemplate.equip;
            attack = keytemplate.attack;
            jump = keytemplate.jump;
            dash = keytemplate.dash;
    }
    if (keytemplate >= 1)
    {
        KeyTemplate1 keytemplate;
            moveU = keytemplate.moveU;
            moveD = keytemplate.moveD;
            moveL = keytemplate.moveL;
            moveR = keytemplate.moveR;
            proj = keytemplate.proj;
            equip = keytemplate.equip;
            attack = keytemplate.attack;
            jump = keytemplate.jump;
            dash = keytemplate.dash;
    }
}

bool Input::input()
{
    if (key_delay) key_delay--;
    if (click_delay) click_delay--;

    // Key Threshold
    for (int i = 0; i < key.size(); i++)
        if (key[i])
        {
            keythreshold[i] ++;
            keythrespeak[i] = 0;
        }
        else if (keythreshold[i])
        {
            keythrespeak[i] = keythreshold[i];
            keythreshold[i] = 0;
        };
    // Click Threshold
    for (int i = 0; i < 2; i++)
        if (click[i])
        {
            clickthreshold[i] ++;
            clickthrespeak[i] = 0;
        }
        else if (clickthreshold[i])
        {
            clickthrespeak[i] = clickthreshold[i];
            clickthreshold[i] = 0;
        };

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // GTFO
        case SDL_QUIT: return true; break;

        // MOUSE MOVEMENT
        case SDL_MOUSEMOTION:
            mouse_x = event.motion.x;
            mouse_y = CFG->HEIGHT - event.motion.y;
            break;
        // MOUSE CLICK
        case SDL_MOUSEBUTTONDOWN:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT: click[0] = true; break;
                case SDL_BUTTON_RIGHT: click[1] = true; break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    click[0] = false; clickhold[0] = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    click[1] = false; clickhold[1] = false;
                    break;
            }
            break;
        // MOUSE SCROLL
        case SDL_MOUSEWHEEL:
            wheel = event.wheel.y;
            break;

        // KEYBOARD
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: return true; break;
                case SDLK_w: key[0] = true; break;
                case SDLK_s: key[1] = true; break;
                case SDLK_a: key[2] = true; break;
                case SDLK_d: key[3] = true; break;
                case SDLK_SPACE: key[4] = true; break;
                case SDLK_LSHIFT: key[5] = true; break;
                case SDLK_l: key[6] = true; break;
                case SDLK_q: key[7] = true; break;
                case SDLK_e: key[8] = true; break;
                case SDLK_SLASH : key[9] = true; break;
                case SDLK_BACKSLASH : key[10] = true; break;
                case SDLK_UP: key[11] = true; break;
                case SDLK_DOWN: key[12] = true; break;
                case SDLK_LEFT: key[13] = true; break;
                case SDLK_RIGHT: key[14] = true; break;
                case SDLK_LCTRL: key[15] = true; break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_w: key[0] = false; keyhold[0] = false; break;
                case SDLK_s: key[1] = false; keyhold[1] = false; break;
                case SDLK_a: key[2] = false; keyhold[2] = false; break;
                case SDLK_d: key[3] = false; keyhold[3] = false; break;
                case SDLK_SPACE: key[4] = false; keyhold[4] = false; break;
                case SDLK_LSHIFT: key[5] = false; keyhold[5] = false; break;
                case SDLK_l: key[6] = false; keyhold[6] = false; break;
                case SDLK_q: key[7] = false; keyhold[7] = false; break;
                case SDLK_e: key[8] = false; keyhold[8] = false; break;
                case SDLK_SLASH: key[9] = false; keyhold[9] = false; break;
                case SDLK_BACKSLASH: key[10] = false; keyhold[10] = false; break;
                case SDLK_UP: key[11] = false; keyhold[11] = false; break;
                case SDLK_DOWN: key[12] = false; keyhold[12] = false; break;
                case SDLK_LEFT: key[13] = false; keyhold[13] = false; break;
                case SDLK_RIGHT: key[14] = false; keyhold[14] = false; break;
                case SDLK_LCTRL: key[15] = false; keyhold[15] = false; break;
            }
            break;

        // CONTROLLER
        case SDL_CONTROLLERBUTTONDOWN:
            switch (event.cbutton.button) {
                case SDL_CONTROLLER_BUTTON_DPAD_UP: key[0] = true; break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN: key[1] = true; break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT: key[2] = true; break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: key[3] = true; break;
                case SDL_CONTROLLER_BUTTON_A: key[4] = true; break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: key[5] = true; break;
                case SDL_CONTROLLER_BUTTON_X: key[6] = true; break;
                case SDL_CONTROLLER_BUTTON_Y: key[7] = true; break;
                case SDL_CONTROLLER_BUTTON_B: key[8] = true; break;
            }
            break;
        case SDL_CONTROLLERBUTTONUP:
            switch (event.cbutton.button) {
                case SDL_CONTROLLER_BUTTON_DPAD_UP: key[0] = false; keyhold[0] = false; break;
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN: key[1] = false; keyhold[1] = false; break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT: key[2] = false; keyhold[2] = false; break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: key[3] = false; keyhold[3] = false; break;
                case SDL_CONTROLLER_BUTTON_A: key[4] = false; keyhold[4] = false; break;
                case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: key[5] = false; keyhold[5] = false; break;
                case SDL_CONTROLLER_BUTTON_X: key[6] = false; keyhold[6] = false; break;
                case SDL_CONTROLLER_BUTTON_Y: key[7] = false; keyhold[7] = false; break;
                case SDL_CONTROLLER_BUTTON_B: key[8] = false; keyhold[8] = false; break;
            }
            break;
        }
    }

    return false;
}

// KEYBOARD/CONTROLLER
void Input::setKeyDelay(int delay) { key_delay = delay; }
void Input::setKeyHold(int i, bool held) { keyhold[i] = held; }
bool Input::getKeyHold(int i) { return key[i]; }
bool Input::getKeyPress(int i) { return key[i] && !keyhold[i] && !key_delay; }
bool Input::getKeyThreshold(int i, int max) { return keythreshold[i] >= max; }
int Input::getKeyThresValue(int i) { return keythreshold[i]; }
int Input::getKeyThresPeak(int i) { return keythrespeak[i]; }
void Input::resetKeyThresPeak(int i) { keythrespeak[i] = 0; }

// MOUSE
void Input::setClickDelay(int delay) { click_delay = delay; }
void Input::setClickHold(int i, bool held) { clickhold[i] = held; }
bool Input::getClickHold(int i) { return click[i]; }
bool Input::getClickPress(int i) { return click[i] && !clickhold[i] && !click_delay; }
bool Input::getClickThreshold(int i, int max) { return clickthreshold[i] >= max; }
int Input::getClickThresValue(int i) { return clickthreshold[i]; }
int Input::getClickThresPeak(int i) { return clickthrespeak[i]; }
void Input::resetClickThresPeak(int i) { clickthrespeak[i] = 0; }

int Input::getMouseX(bool fromright) {
    return fromright ? CFG->WIDTH - mouse_x : mouse_x;
}
int Input::getMouseY(bool fromtop) {
    return fromtop ? CFG->HEIGHT - mouse_y : mouse_y;
}
int Input::getMOffMidX() {
    return CFG->WIDTH / 2 - mouse_x;
}
int Input::getMOffMidY() {
    return mouse_y - CFG->HEIGHT / 2;
}
int Input::getMOffPlayerX(Player *player) {
    return-(player->camera.offset_mid_x +
            Camera::playerShiftX(player) +
            getMOffMidX());
}
int Input::getMOffPlayerY(Player *player) {
    return-(player->camera.offset_mid_y +
            Camera::playerShiftY(player) +
            getMOffMidY());
}
int Input::getMMapX(Player *player, short grid)
{ 
    int mx = player->getX() + getMOffPlayerX(player);
    return (mx > 0) ? (mx/grid) : (mx/grid - 1);
}
int Input::getMMapY(Player *player, short grid)
{
    int my = player->getY() + getMOffPlayerY(player);
    return (my > 0) ? (my/grid) : (my/grid - 1);
}
bool Input::mouseInBox(ObjectBox mbox)
{ return !(
    (mouse_y > mbox.up && mbox.up > -1) ||
    (mouse_y < mbox.down && mbox.down > -1) ||
    (mouse_x < mbox.left && mbox.left > -1) ||
    (mouse_x > mbox.right && mbox.right > -1)
); }

// Mouse Wheel
void Input::resetWheel() { wheel = 0; }
short Input::getWheel() { return wheel; }