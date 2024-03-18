#ifndef STAGE1_H
#define STAGE1_H

#include "stages.h"

class Stage1 : public Stages
{
private:
    std::vector<const char*> block_path = {
        "res/BlockTile/x64/Stage1/Dirt.png", // 0
        "res/BlockTile/x64/Stage1/DirtUnder.png", // 1
        "res/BlockTile/x64/Stage1/DirtUnder1.png", // 2
        "res/BlockTile/x64/Stage1/DirtUnder2.png", // 3
        "res/BlockTile/x64/Stage1/DirtWall1.png", // 4
        "res/BlockTile/x64/Stage1/DirtWall2.png", // 5
        "res/BlockTile/x64/Stage1/Grass.png", // 6
        "res/BlockTile/x64/Stage1/Grass1.png", // 7
        "res/BlockTile/x64/Stage1/Grass2.png", // 8
    };
public:
    void initBlocks(SDL_Renderer *renderer) override;
    void initDecors(SDL_Renderer *renderer) override;
    void initEnemies(SDL_Renderer *renderer) override;
};

#endif