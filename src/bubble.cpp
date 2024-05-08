#include <map.h>

float BubbleStyle::alphaRatio()
{ return 1 - curAlpha/maxAlpha; }

Bubble::~Bubble() { SDL_DestroyTexture(bubble_texture); }
Bubble::Bubble( string0D bPath, ObjectHitbox bHitbox,
                ObjectBox bActivebox, BubbleStyle bStyle,
                short type, int grid ) :
    Object2D(bHitbox.hitboxGrid(grid)),
    b_active_box(bActivebox), b_type(type),
    bubble_path(bPath), b_style(bStyle)
{}

void Bubble::initBubble()
{
    bubble_texture = loadTexture(bubble_path);
    SDL_SetTextureAlphaMod(bubble_texture, 0);
}

void Bubble::updateBubble(Map *map)
{
    // Update Bubble Transparency
    if (map->MapActive &&
        map->MapPlayer->insideGridBox(b_active_box))
    {
        if (b_style.curAlpha < b_style.maxAlpha)
            b_style.curAlpha += 5;

        SDL_SetTextureAlphaMod(bubble_texture, b_style.curAlpha);
    }
    else if (b_style.curAlpha > 0)
    {
        b_style.curAlpha -= 5;
        SDL_SetTextureAlphaMod(bubble_texture, b_style.curAlpha);
    }

    // Update Bubble Offset
    b_style.curOffX = b_style.alphaRatio() * b_style.maxOffX;
    b_style.curOffY = b_style.alphaRatio() * b_style.maxOffY;
}

void Bubble::draw(Player *player)
{
    if (Camera::objectIgnore(player, this, 1) &&
        !b_type == 2) return;

    SDL_Rect desRect;

    switch (b_type)
    {
    default:
    case 0: desRect = {
        Camera::objectDrawX(player, this) + b_style.curOffX,
        Camera::objectDrawY(player, this) - b_style.curOffY,
        getWidth(), getHeight()
    }; break;

    case 1: desRect = {
        Camera::playerDrawX(player, getWidth()) + b_style.maxOffX,
        Camera::playerDrawY(player, getHeight()) - b_style.maxOffY,
        getWidth(), getHeight()
    }; break;

    case 2: desRect = {
        int(getX() + b_style.curOffX),
        int(getY() - b_style.curOffY),
        getWidth(), getHeight()
    }; break;
    }

    SDL_RenderCopy(CFG->RENDERER, bubble_texture, NULL, &desRect);
}

// ============================ FILE MANIPULATION ===================================

Bubble *Bubble::codeToBubbleInfo(string0D str)
{
    std::stringstream ss(str);
    char cm = ',';

    string0D type, bPath;
    float x, y, w, h;
    int up, down, left, right;
    int offX, offY; float mAlpha;

    std::getline(ss, type, ',');
    std::getline(ss, bPath, ',');

    ss  >>  x >> cm >> y >> cm >> w >> cm >> h >> cm >>
            up >> cm >> down >> cm >> left >> cm >> right >> cm >>
            offX >> cm >> offY >> cm >> mAlpha;

    ObjectHitbox bHitbox = {x, y, w, h};
    ObjectBox bActivebox = {up, down, left, right};
    BubbleStyle bStyle = {offX, offY, mAlpha};

    Bubble *bubble = new Bubble(
        bPath, bHitbox, bActivebox, bStyle, std::stoi(type)
    );
    bubble->initBubble();
    return bubble;
}

void Bubble::appendBubble(Map *map, string0D bubble_dir)
{
    std::ifstream inputFile(bubble_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] == '#') continue;

        map->BubbleVec.push_back(codeToBubbleInfo(line));
    }
}