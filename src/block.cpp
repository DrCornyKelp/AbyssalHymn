#include <block.h>
#include <player.h>

// Constructor
Block::Block(float X, float Y, float w, float h, short gr, bool gothru, bool seethru, int seethruAlpha) :
    Object2D((X + w/2) * gr, (Y + h/2) * gr,
            w * gr, h * gr, w * gr, h * gr),
    isGoThru(gothru), isSeeThru(seethru), seeAlphaMin(seethruAlpha),
    grid_w(int(w) < w ? w + 1 : w),
    grid_h(int(h) < h ? h + 1 : h),
    grid(gr)
{}

void Block::blockEngine(SDL_Renderer *renderer, std::vector<const char*> sPath, std::vector<std::vector<int>> b_index)
{
    block_sprites.resize(grid_h);
    for (int i = 0; i < grid_h; i++)
        for (int j = 0; j < grid_w; j++)
        {
            block_sprites[i].push_back(new Sprite(getWidth(), getHeight(), 1, sPath[b_index[i][j]]));
            block_sprites[i][j]->setTexture(Sprite::loadTexture(renderer, block_sprites[i][j]->getSpritePath()));
        }
}

// Setter
void Block::setGoThru(bool GoThru)
{
    isGoThru = GoThru;
}
void Block::setSeeThru(bool seethru)
{
    isSeeThru = seethru;
}
void Block::setSeeAlpha(int alpha)
{
    seeAlpha = alpha;
}
void Block::setStepOn(bool step)
{
    isStepOn = step;
}
void Block::setOutBound(bool oob)
{
    isOutBound = oob;
}
void Block::setHugged(short hug)
{
    isHugged = hug;
}
void Block::setVelX(float vx)
{
    vel_x = vx;
}
void Block::setVelY(float vy)
{
    vel_y = vy;
}

// Getter
bool Block::getGoThru()
{
    return isGoThru;
}
bool Block::getSeeThru()
{
    return isSeeThru;
}
int Block::getSeeAlpha()
{
    return seeAlpha;
}
int Block::getSeeAlphaMin()
{
    return seeAlphaMin;
}
bool Block::getStepOn()
{
    return isStepOn;
}
bool Block::getOutBound()
{
    return isOutBound;
}
short Block::getHugged()
{
    return isHugged;
}
float Block::getVelX()
{
    return vel_x;
}
float Block::getVelY()
{
    return vel_y;
}

void Block::draw(SDL_Renderer *renderer, Player *player)
{
    if (getVelX() || getVelY())
    {
        isMoving = true;
        setX(getX() + getVelX());
        setY(getY() + getVelY());
    }
    else
        isMoving = false;

    if (isOutBound) return;

    // Draw
    for (int i = 0; i < block_sprites.size(); i++)
        for (int j = 0; j < block_sprites[i].size(); j++)
        {
            // If a grid x grid texture is out of bound
            // Ignore the rendering process
            // This cannot use camera cuz holy shit wtf
            int colli_x = abs(player->getX() - getX() + getWidth() / 2 - j*grid);
            int colli_y = abs(player->getY() - getY() - getHeight() / 2 + i*grid);
            if (colli_x - grid / 2 > Game::WIDTH ||
                colli_y - grid / 2 > Game::HEIGHT)
                continue;

            if (isSeeThru)
                SDL_SetTextureAlphaMod(block_sprites[i][j]->getTexture(), seeAlpha);

            double cam_scale = player->getCameraScale();
            SDL_Rect desRect = {Camera::objectDrawX(player, this) + int(j*grid * cam_scale),
                                Camera::objectDrawY(player, this) + int(i*grid * cam_scale),
                                int(64 * cam_scale), int(64 * cam_scale)};
    
            SDL_RenderCopy(renderer, block_sprites[i][j]->getTexture(), NULL, &desRect);        
        }
}