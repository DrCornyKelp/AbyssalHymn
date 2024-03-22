#include <npc_dialogue.h>
#include <player.h>

NpcDialogue::NpcDialogue(const char* nPath, const char* bPath, float nx, float ny, int w, int h, int hw, int hh, int bw, int bh, int sw, int sh, int sim, int sfm, int si, int sf, int alpm, int grid, bool f_player):
    Object2D(nx * grid, ny * grid, w * grid, h * grid, hw *grid, hh * grid,
            sim, sfm, si, sf),
    facing_player(f_player), alpha_max(alpm),
    sprite_width(sw), sprite_height(sh),
    bubble_width(bw), bubble_height(bh),
    npc_path(nPath), bubble_path(bPath)
{}

void NpcDialogue::initNpc(SDL_Renderer *renderer){
    npc = new Sprite(getWidth(), getHeight(), 1, npc_path);
    npc->setTexture(Sprite::loadTexture(renderer, npc->getSpritePath()));

    bubble = new Sprite(getWidth(), getHeight(), 1, bubble_path);
    bubble->setTexture(Sprite::loadTexture(renderer, bubble->getSpritePath()));

    delete npc_path, bubble_path;
};

void NpcDialogue::setDisplay(bool display)
{
    display_bubble = display;
}

void NpcDialogue::draw(SDL_Renderer *renderer, Player *player)
{
    // Outside seeable? unrender
    int colli_x = abs(player->getX() - getX());
    int colli_y = abs(player->getY() - getY());
    if (colli_x - bubble_width / 2 > Game::WIDTH ||
        colli_y - bubble_height / 2 > Game::HEIGHT)
        return;

    // Camera is a piece of shit
    int rel_x = player->getFocusX() ? player->getOffsetX() + getX() - player->getX() : getX();
    int rel_y = player->getFocusY() ? player->getOffsetY() + getY() - player->getY() : getY();

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
    if (abs(player->getX() - getX()) < getHitWidth() &&
        abs(player->getY() - getY()) < getHitHeight())
        alpha_cur += 10;
    else 
        alpha_cur -= 10;

    if (alpha_cur > alpha_max) alpha_cur = alpha_max;
    if (alpha_cur < 0) alpha_cur = 0;

    if (alpha_cur > 20)
    {
        int effectY = float(alpha_cur) / alpha_max * 10 - 10;

        SDL_Rect bDesRect = {rel_x - bubble_width / 2, Game::HEIGHT - rel_y - getHeight() - bubble_height / 2 - effectY, bubble_width, bubble_height};
        if (alpha_cur % 5 == 0 || alpha_cur == alpha_max)
            SDL_SetTextureAlphaMod(bubble->getTexture(), alpha_cur);
        SDL_RenderCopy(renderer, bubble->getTexture(), NULL, &bDesRect);
    }
    // =======================================================

    // Drawing Npc itself
    SDL_Rect nDesRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2,getWidth(), getHeight()};
    
    SDL_Rect nSrcRect;
    if (getSprIndexMax() > 0) 
    {
        nSrcRect = {getSprIndex() * sprite_width, 0, sprite_width, sprite_height};
    } else nSrcRect = {0, 0, sprite_width, sprite_height};

    SDL_RenderCopy(renderer, npc->getTexture(), &nSrcRect, &nDesRect);
}