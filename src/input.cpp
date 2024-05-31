#include <input.h>
#include <player.h>

// ============================== KEYSTATE ==============================

void KeyState::update(const Uint8* keystate, Input *input)
{
    // Key Script
    if (!(script_history.size() % 2) && state ||
        script_history.size() % 2 && !state)
        script_history.push_back(CFG->WORLDTIME);

    if (moveset) input->script_history_full += scriptHistoryToStr() + "\n";

    // Key State
    int script_size = script.size();
    // // KEY SCRIPT
    if (script_size)
    {
        if (CFG->WORLDTIME >= script[0])
        {
            if (CFG->WORLDTIME == script[0])
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
        if (keystate[code] && !input->delay)
            state = 1;
        else 
        { 
            state = 0;
            hold = 0;
        }
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
bool KeyState::press() { 
    return state && !hold && !keydelay;
}

bool KeyState::threspass(int max) { return threshold >= max; }
string0D KeyState::scriptHistoryToStr()
{
    if (!script_history.size()) return "#";
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
    while (SDL_PollEvent(&CFG->EVENT))
    {
        if (CFG->EVENT.type == SDL_MOUSEWHEEL)
            W = CFG->EVENT.wheel.y;

        if (CFG->EVENT.type == SDL_QUIT)
            CFG->QUIT = 1;
    }
}

int MouseMain::offMidX()
{ return CFG->WIDTH / 2 - x; }
int MouseMain::offMidY()
{ return y - CFG->HEIGHT / 2; }
int MouseMain::offPlayerX(Player *player)
{ return - ( player->camera.mid.x + offMidX() ); }
int MouseMain::offPlayerY(Player *player)
{ return - ( player->camera.mid.y + offMidY() ); }
int MouseMain::mapX(Player *player, short grid)
{
    int mx = player->hitbox.x + offPlayerX(player);
    return mx / grid;
}
int MouseMain::mapY(Player *player, short grid)
{
    int my = player->hitbox.y + offPlayerY(player);
    return my / grid;
}
bool MouseMain::inbox(ObjectBox mbox)
{ return !(
    (y > mbox.up && mbox.up > -1) ||
    (y < mbox.down && mbox.down > -1) ||
    (x < mbox.left && mbox.left > -1) ||
    (x > mbox.right && mbox.right > -1)
); }

void Input::updateMoveset()
{
    // ====================== Update Delay ======================
    if (delay) delay--;

    // ====================== Update KEYBOARD ======================;
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
}

void Input::updateOther()
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

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
    f6.update(keystate, this);

    // Mouse Update
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
        if (CFG->isComment(line)) continue;

        long1D script = CFG->convertStrLong1D(line);
        if (from_cur) for (long &s : script) s += CFG->WORLDTIME;

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

void Input::endScript()
{
    moveU.script = {};
    moveD.script = {};
    moveL.script = {};
    moveR.script = {};
    proj.script = {};
    equip.script = {};
    attack.script = {};
    jump.script = {};
    dash.script = {};
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
    KeyTemplateN1 kN1;
    KeyTemplate0 k0;
    KeyTemplate1 k1;

    switch (keytemplate)
    {
    default:
    case -1:
        moveU = kN1.moveU;
        moveD = kN1.moveD;
        moveL = kN1.moveL;
        moveR = kN1.moveR;
        proj = kN1.proj;
        equip = kN1.equip;
        attack = kN1.attack;
        jump = kN1.jump;
        dash = kN1.dash;
        break;
    
    case 0:
        moveU = k0.moveU;
        moveD = k0.moveD;
        moveL = k0.moveL;
        moveR = k0.moveR;
        proj = k0.proj;
        equip = k0.equip;
        attack = k0.attack;
        jump = k0.jump;
        dash = k0.dash;
        break;

    case 1:
        moveU = k1.moveU;
        moveD = k1.moveD;
        moveL = k1.moveL;
        moveR = k1.moveR;
        proj = k1.proj;
        equip = k1.equip;
        attack = k1.attack;
        jump = k1.jump;
        dash = k1.dash;
        break;
    }
}