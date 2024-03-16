#include <npc_dialogue.h>

NpcDialogue::NpcDialogue(float nx, float ny, int w, int h, int hw, int hh, int bw, int bh, int sw, int sh, int sim, int sfm, int si, int sf, int alpm, bool f_player):
    Object2D(nx, ny, w, h, hw, hh, sim, sfm, si, sf),
    facing_player(f_player), alpha_max(alpm),
    sprite_width(sw), sprite_height(sh),
    bubble_width(bw), bubble_height(bh)
{}

void NpcDialogue::initNpc(SDL_Renderer *renderer, const char* nPath, const char* bPath)
{
    npc = new Sprite(getWidth(), getHeight(), 1, nPath);
    npc->setTexture(Sprite::loadTexture(renderer, npc->getSpritePath()));

    bubble = new Sprite(getWidth(), getHeight(), 1, bPath);
    bubble->setTexture(Sprite::loadTexture(renderer, bubble->getSpritePath()));
};


void NpcDialogue::setDisplay(bool display)
{
    display_bubble = display;
}

void NpcDialogue::drawNpc(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    // Camera is a piece of shit
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    // Frame index shitty bang bang stuff handler
    if (getSprFrame() < getSprFrameMax())
        setSprFrame(getSprFrame() + 1);
    else
    {
        setSprFrame(0);
        setSprIndex(getSprIndex() + 1);
    }

    if (getSprIndex() >= getSprIndexMax())
        setSprIndex(0);

    // Colliding => Draw bubble
    if (abs(px - getX()) < getHitWidth() &&
        abs(py - getY()) < getHitHeight())
    {
        alpha_cur += 10;
    } else {
        alpha_cur -= 10;
    }

    if (alpha_cur > alpha_max) alpha_cur = alpha_max;
    if (alpha_cur < 0) alpha_cur = 0;

    if (alpha_cur > 20)
    {
        int offsetY = bubble_height + getHeight();
        int effectY = float(alpha_cur) / alpha_max * 10 - 10;

        SDL_Rect bDesRect = {rel_x - bubble_width / 2, 720 - rel_y / 2 - offsetY - effectY, bubble_width, bubble_height};
        if (alpha_cur % 5 == 0 || alpha_cur == alpha_max)
            SDL_SetTextureAlphaMod(bubble->getTexture(), alpha_cur);
        SDL_RenderCopy(renderer, bubble->getTexture(), NULL, &bDesRect);
    }

    // Drawing Npc itself
    SDL_Rect nDesRect = {rel_x - getWidth() / 2, 720 - rel_y - getHeight() / 2,getWidth(), getHeight()};
    
    SDL_Rect nSrcRect;
    if (getSprIndexMax() > 0) 
    {
        nSrcRect = {getSprIndex() * sprite_width, 0, sprite_width, sprite_height};
    } else nSrcRect = {0, 0, sprite_width, sprite_height};

    SDL_RenderCopy(renderer, npc->getTexture(), &nSrcRect, &nDesRect);
}