#include <input.h>
#include <player.h>

// ============================== KEYSTATE ==============================

void KeyState::update(const Uint8* keystate, Input *input)
{
    // Key Script
    if (!(script_history.size() % 2) && state ||
        script_history.size() % 2 && !state)
        script_history.push_back(CFG->TIME);

    if (moveset) input->script_history_full += scriptHistoryToStr() + "\n";

    // Key State
    int script_size = script.size();
    // // KEY SCRIPT
    if (script_size)
    {
        if (CFG->TIME >= script[0])
        {
            if (CFG->TIME == script[0])
            {
                if (script_size % 2) {
                    state = 0; hold = 0;
                } else state = 1;
            }
            script.erase(script.begin());
        }
    }
    // // KEY INPUT
    else {
        if (keystate[code] && !input->delay) state = 1;
        else { state = 0; hold = 0; }
    }

    // Threshold
    if (state)
    {
        threshold++;
        threspeak = 0;
    }
    else if (threshold)
    {
        threspeak = threshold;
        threshold = 0;
    }

    // Key Delay
    if (keydelay) keydelay--;
}
bool KeyState::press() { return state && !hold && !keydelay; }
bool KeyState::threspass(int max) { return threshold >= max; }
string0D KeyState::scriptHistoryToStr()
{
    if (!script_history.size()) return "-";
    string0D script_str = "";

    for (long num : script_history)
        script_str += std::to_string(num) + ",";
    // Remove the comma at the end
    script_str.erase(script_str.size() - 1);

    return script_str;
}

// ============================== MOUSESTATE ==============================

void MouseState::update(Uint32 mousestate)
{
    if (mousestate & SDL_BUTTON(button)) state = 1;
    else { state = 0; hold = 0; }

    if (state)
    {
        threshold++;
        threspeak = 0;
    }
    else if (threshold)
    {
        threspeak = threshold;
        threshold = 0;
    }
}
bool MouseState::click() { return state && !hold; }
bool MouseState::threspass(int max) { return threshold >= max; }

void MouseMain::update()
{
    // Update MOUSE POSITION/CLICK
    SDL_PumpEvents();
    Uint32 mousestate = SDL_GetMouseState(&x, &y);
    L.update(mousestate);
    M.update(mousestate);
    R.update(mousestate);

    // Update MOUSE WHEEL
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEWHEEL) 
            W = event.wheel.y;
    }
}

int MouseMain::offMidX()
{ return CFG->WIDTH / 2 - x; }
int MouseMain::offMidY()
{ return y - CFG->HEIGHT / 2; }
int MouseMain::offPlayerX(Player *player)
{ return - ( player->camera.offset_x + offMidX() ); }
int MouseMain::offPlayerY(Player *player)
{ return - ( player->camera.offset_y + offMidY() ); }
int MouseMain::mapX(Player *player, short grid)
{
    int mx = player->getX() + offPlayerX(player);
    return (mx > 0) ? (mx/grid) : (mx/grid - 1);
}
int MouseMain::mapY(Player *player, short grid)
{
    int my = player->getY() + offPlayerY(player);
    return (my > 0) ? (my/grid) : (my/grid - 1);
}
bool MouseMain::inbox(ObjectBox mbox)
{ return !(
    (y > mbox.up && mbox.up > -1) ||
    (y < mbox.down && mbox.down > -1) ||
    (x < mbox.left && mbox.left > -1) ||
    (x > mbox.right && mbox.right > -1)
); }

void Input::update()
{
    // Update Delay
    if (delay) delay--;

    // Update KEYBOARD;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

	script_history_full = "";

    moveU.update(keystate, this);
    moveD.update(keystate, this);
    moveL.update(keystate, this);
    moveR.update(keystate, this);
    proj.update(keystate, this);
    equip.update(keystate, this);
    attack.update(keystate, this);
    jump.update(keystate, this);
    dash.update(keystate, this);

    lctrl.update(keystate, this);
    arrowU.update(keystate, this);
    arrowD.update(keystate, this);
    arrowL.update(keystate, this);
    arrowR.update(keystate, this);

    slash.update(keystate, this);
    backslash.update(keystate, this);

    escape.update(keystate, this);

    f1.update(keystate, this);
    f2.update(keystate, this);
    f3.update(keystate, this);
    f4.update(keystate, this);
    f5.update(keystate, this);

    // UPDATE MOUSE IN GENERAL
    mouse.update();
}

void Input::executeScript(string0D script_dir, bool from_cur)
{
    std::ifstream inputFile(script_dir);
    string0D line;

    int index = 0;
    while (std::getline(inputFile, line))
    {   
        index ++;
        // Empty or Comment => Skip
        if (line == "-" || line == "" ||
            line.back() == '#' ||
            line[0] ==  '#') continue;

        long1D script = CFG->convertStrLong1D(line);
        if (from_cur) for (long &s : script) s += CFG->TIME;

        // A .1 ms input, needed to ensure correct hold/release cycle
        if (script.size() % 2) script.push_back(script.back() + 1);

        if (index == 1) moveU.script = script;
        if (index == 2) moveD.script = script;
        if (index == 3) moveL.script = script;
        if (index == 4) moveR.script = script;
        if (index == 5) proj.script = script;
        if (index == 6) equip.script = script;
        if (index == 7) attack.script = script;
        if (index == 8) jump.script = script;
        if (index == 9) dash.script = script;
    }
}

// ============================== OLD AND OBSOLETE ==============================

Input::Input()
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
}

void Input::setTemplate(int keytemplate)
{
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