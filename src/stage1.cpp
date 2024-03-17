#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // 0
    BlockVec.push_back(new Block("res/BlockTile/Test.png", -1, 0, 1, 64, 64));

    // 1 -> 18
    for (int i = 0; i < 19; i++) {
        BlockVec.push_back(new Block("res/BlockTile/x64/Dirt1.png", i, 0, 1, 1, 64));
        BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", i, 1, 1, 1, 64));
    }
    
    // 19 - 20
    BlockVec.push_back(new Block("res/BlockTile/x64/Dirt1.png", 19, 0, 6, 2, 64));
    BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 19, 1, 1, 1, 64));

    // 21 - 24
    BlockVec.push_back(new Block("res/BlockTile/x64/GrassCorner1.png", 20, 2, 1, 1, 64));
    for (int i = 1; i < 4; i++) {
        BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 20 + i, 2, 1, 1, 64));
    }
    
    // 25 - 27
    BlockVec.push_back(new Block("res/BlockTile/Test.png", 24, 3, 4, 1, 64));
    BlockVec.push_back(new Block("res/BlockTile/Test.png", 28, 2, 4, 3, 64));
    BlockVec.push_back(new Block("res/BlockTile/Test.png", 32, 2, 5, 4, 64));

    // Test 28 - 30
    BlockVec.push_back(new Block("res/BlockTile/x64/GrassCorner1.png", 14, 4, 1, 1, 64, true));
    BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 15, 4, 1, 1, 64, true));
    BlockVec.push_back(new Block("res/BlockTile/x64/GrassCorner2.png", 16, 4, 1, 1, 64, true));


    for (int i = 0; i < 200; i++)
        BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 25 + i, 0, 1, 1, 64));

    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 41, 5, 2, 1, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 48, 5, 2, 1, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 59, 5, 2, 1, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 69, 2, 3, 5, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 75, 2, 3, 5, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 78, 5, 7, 2, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 78, 8, 3, 12, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 78, 20, 2, 7, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 84, 11, 3, 9, 64));

    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 84, 1, 2, 1, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 99, 1, 2, 1, 64));

    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 92, 19, 5, 2, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 92, 18, 4, 1, 64));

    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 92, 6, 20, 2, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 95, 8, 4, 3, 64));
    
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 105, 19, 5, 2, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 107, 18, 3, 1, 64));
    

    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 25, 0, 100, 1, 64));

    // // Ground
    // BlockVec.push_back(new Block("res/BlockTile/x64/GrassCorner1.png", 0, 0, 1, 1, 128));
    // for (int i = 1; i < 9; i++)
    // {
    //     BlockVec.push_back(new Block("res/BlockTile/Test.png", i, 0, 1, 1, 128));
    // }
    // BlockVec.push_back(new Block("res/BlockTile/x64/GrassCorner2.png", 9, 0, 1, 1, 128));


    for (Block *block : BlockVec)
        block->initBlock(renderer);
}

void Stage1::initDecors(SDL_Renderer *renderer)
{

}

void Stage1::initEnemies(SDL_Renderer *renderer)
{
    std::cout << "WIP";
}
