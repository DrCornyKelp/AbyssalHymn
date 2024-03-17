#include "block.h"

// Constructor
Block::Block(const char* sPath, float X, float Y, float w, float h, int grid, bool collideDown) : 
    Object2D((X + w/2) * grid, (Y + h/2) * grid,
            w * grid, h * grid, w * grid, h * grid),
    isCollideDown(collideDown), sprite_path(sPath)
{}

void Block::initBlock(SDL_Renderer *renderer)
{
    // Grid sprite
    block_sprite = new Sprite(getWidth(), getHeight(), 1, sprite_path);
    block_sprite->setTexture(Sprite::loadTexture(renderer, block_sprite->getSpritePath()));
    delete sprite_path;
}

bool Block::getCollideDown()
{
    return isCollideDown;
}

void Block::renderBlock(SDL_Renderer *renderer, int px, int py, bool focusX, int offsetX, bool focusY, int offsetY)
{
    int rel_x = focusX ? offsetX + getX() - px : getX();
    int rel_y = focusY ? offsetY + getY() - py : getY();

    SDL_Rect desRect = {rel_x - getWidth() / 2, Game::HEIGHT - rel_y - getHeight() / 2, getWidth(), getHeight()};
    SDL_RenderCopy(renderer, block_sprite->getTexture(), NULL, &desRect);
}