#include <map.h>

// ================================ BUBBLE STYLE ================================ 

float BubbleStyle::alphaRatio()
{ return 1 - curAlpha/maxAlpha; }

// ================================ BUBBLE OBJECT ================================ 

void BubbleObject::update(Bubble *bubble, Player *player)
{
    // Update Bubble Transparency
    if (player->insideGridBox(bubble->active_box))
    {
        if (style.curAlpha < style.maxAlpha)
            style.curAlpha += 5;

        SDL_SetTextureAlphaMod(texture, style.curAlpha);
    }
    else if (style.curAlpha > 0)
    {
        style.curAlpha -= 5;
        SDL_SetTextureAlphaMod(texture, style.curAlpha);
    }

    // Update Bubble Offset
    style.curOffX = style.alphaRatio() * style.maxOffX;
    style.curOffY = style.alphaRatio() * style.maxOffY;

    // Update bubble draw Properties
    drawProp(bubble, player);
}

void BubbleObject::drawProp(Bubble *bubble, Player *player)
{
    int b_w = bubble->hitbox.w;
    int b_h = bubble->hitbox.h;

    // Update Rect
    switch (bubble->type)
    {
    default:
    case 0: desRect = {
        Camera::objectDrawX(player->MULTI->MAIN, bubble) + style.curOffX,
        Camera::objectDrawY(player, bubble) - style.curOffY,
        b_w, b_h
    }; break;

    case 1: desRect = {
        Camera::objectDrawX(player->MULTI->MAIN, player) - b_w/2 + style.maxOffX,
        Camera::objectDrawY(player->MULTI->MAIN, player) - b_h/2 - style.maxOffY,
        b_w, b_h
    }; break;

    case 2: desRect = {
        int(bubble->hitbox.x + style.curOffX),
        int(bubble->hitbox.y - style.curOffY),
        b_w, b_h
    }; break;
    }
}
void BubbleObject::draw(Player *player)
{ 
    if (Camera::outOfBound(desRect))
        return;

    SDL_RenderCopy(CFG->RENDERER, texture, NULL, &desRect);
}

// ================================ BUBBLE ================================ 

Bubble::~Bubble() { 
    for (BubbleObject b_obj : bubble_objs)
        SDL_DestroyTexture(b_obj.texture);
}
Bubble::Bubble( string0D bPath, ObjectHitbox bHitbox,
                ObjectBox bActivebox, BubbleStyle bStyle,
                short type, int grid ) :
    Object2D(bHitbox),
    active_box(bActivebox), type(type),
    bubble_path(bPath), style(bStyle)
{}

void Bubble::update(Multiplayer *multi)
{
    // Fill Missing Bubble
    if (bubble_objs.size() > multi->PlayerCount)
    {
        SDL_DestroyTexture(bubble_objs.back().texture);
        bubble_objs.pop_back();
        return;
    }
    if (bubble_objs.size() < multi->PlayerCount)
    {
        SDL_Texture *texture = CFG->loadTexture(bubble_path);
        SDL_SetTextureAlphaMod(texture, 0);
        bubble_objs.push_back({texture, style});
        return;
    }

    // Seperate Bubble for Seperate Player
    for (int i = 0; i < multi->PlayerCount; i++)
        bubble_objs[i].update(this, multi->Players[i]);
}

void Bubble::draw(Multiplayer *multi)
{
    if (bubble_objs.size() != multi->PlayerCount) return;

    for (int i = 0; i < multi->PlayerCount; i++)
        bubble_objs[i].draw(multi->Players[i]);
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

    ObjectHitbox bHitbox = {x * 64, y * 64, w * 64, h * 64};
    ObjectBox bActivebox = {up, down, left, right};
    BubbleStyle bStyle = {offX, offY, mAlpha};

    Bubble *bubble = new Bubble(
        bPath, bHitbox, bActivebox, bStyle, std::stoi(type)
    );
    return bubble;
}

void Bubble::appendBubble(Map *map, string0D bubble_dir)
{
    std::ifstream inputFile(bubble_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        map->BubbleVec.push_back(codeToBubbleInfo(line));
    }
}