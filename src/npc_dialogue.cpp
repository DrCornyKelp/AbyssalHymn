#include <npc_dialogue.h>
#include <player.h>

NpcDialogue::NpcDialogue(const char* nPath, const char* bPath, float nx, float ny, int w, int h, 
                        int hw, int hh, int bw, int bh, int sw, int sh,
                        int sim, int sfm, int alpm, int grid):
    Object2D(nx * grid, ny * grid, w * grid, h * grid, hw *grid, hh * grid,
            sw, sh, sim, sfm, 0, 0),
    alpha_max(alpm),
    bubble_width(bw), bubble_height(bh),
    npc_path(nPath), bubble_path(bPath)
{}

void NpcDialogue::initNpc(SDL_Renderer *renderer){
    npc_texture = Sprite::loadTexture(renderer, npc_path);
    bubble_texture = Sprite::loadTexture(renderer, bubble_path);

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
    // Frame index shitty bang bang stuff handler
    objectSetSprite();

    auto distance = Camera::objectDistance(this, player);
    int dist_x = DistGet(distance, 0);
    int dist_y = DistGet(distance, 1);

    // Colliding => Draw bubble
    if (abs(player->getX() - getX()) < getHitWidth() &&
        abs(player->getY() - getY()) < getHitHeight())
        alpha_cur += 10;
    else 
        alpha_cur -= 10;

    if (alpha_cur > alpha_max) alpha_cur = alpha_max;
    if (alpha_cur < 0) alpha_cur = 0;
    
    double cam_scale = player->getCameraScale();
    if (alpha_cur > 20)
    {
        int effectY = float(alpha_cur) / alpha_max * 10 - 10;

        int drawBX = (player->getUnfocusX() ?
            Game::WIDTH/2 + (getX() - player->getUnfocusOffsetX() - bubble_width/2) * player->getCameraScale() :
            Game::WIDTH/2 + (dist_x + player->getOffsetMidX() - bubble_width/2) * player->getCameraScale())
            + Camera::playerShiftX(player);
        int drawBY = (player->getUnfocusY() ?
            Game::HEIGHT/2 - (getY() - player->getUnfocusOffsetY() + bubble_height/2) * player->getCameraScale() :
            Game::HEIGHT/2 - (dist_y + player->getOffsetMidY() + bubble_height/2) * player->getCameraScale())
            + Camera::playerShiftY(player);

        SDL_Rect bDesRect= {drawBX, drawBY - getHeight() - effectY,
                            int(bubble_width * cam_scale),
                            int(bubble_height * cam_scale)};
        if (alpha_cur % 5 == 0 || alpha_cur == alpha_max)
            SDL_SetTextureAlphaMod(bubble_texture, alpha_cur);
        SDL_RenderCopy(renderer, bubble_texture, NULL, &bDesRect);
    }
    // =======================================================

    // Drawing Npc itself
    SDL_Rect nDesRect= {Camera::objectDrawX(player, this),
                        Camera::objectDrawY(player, this),
                        int(getWidth() * cam_scale), int(getHeight() * cam_scale)};

    SDL_Rect nSrcRect;
    if (getSprIndexMax() > 0)
        nSrcRect = {getSprIndex() * getSprWidth(), 0, getSprWidth(), getSprHeight()};
    else 
        nSrcRect = {0, 0, getSprWidth(), getSprHeight()};

    SDL_RenderCopy(renderer, npc_texture, &nSrcRect, &nDesRect);
}