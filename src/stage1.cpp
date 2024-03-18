#include "stage1.h"

void Stage1::initBlocks(SDL_Renderer *renderer)
{
    // // 0
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", -1, 0, 1, 64, 64));

    // // 1 -> 18
    // for (int i = 0; i < 19; i++) {
    //     BlockVec.push_back(new Block(block_path[0], i, 0, 1, 1, 64));
    //     BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", i, 1, 1, 1, 64));
    // }
    
    // // 19 - 20
    // BlockVec.push_back(new Block(block_path[0], 19, 0, 6, 2, 64));
    // BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 19, 1, 1, 1, 64));

    // // 21 - 24
    // BlockVec.push_back(new Block(block_path[7], 20, 2, 1, 1, 64));
    // for (int i = 1; i < 4; i++) {
    //     BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 20 + i, 2, 1, 1, 64));
    // }
    
    // // 25 - 27
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 24, 3, 4, 1, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 28, 2, 4, 3, 64));
    // BlockVec.push_back(new Block("res/BlockTile/Test.png", 32, 2, 5, 4, 64));

    // // Test 28 - 30
    BlockVec.push_back(new Block(block_path[7], 14, 6, 1, 1, 64, true));
    BlockVec.push_back(new Block(block_path[6], 15, 6, 1, 1, 64, true));
    BlockVec.push_back(new Block(block_path[8], 16, 6, 1, 1, 64, true));


    // for (int i = 0; i < 200; i++)
    //     BlockVec.push_back(new Block("res/BlockTile/x64/Grass.png", 25 + i, 0, 1, 1, 64));

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
    // BlockVec.push_back(new Block(block_path[7], 0, 0, 1, 1, 128));
    // for (int i = 1; i < 9; i++)
    // {
    //     BlockVec.push_back(new Block("res/BlockTile/Test.png", i, 0, 1, 1, 128));
    // }
    // BlockVec.push_back(new Block(block_path[8], 9, 0, 1, 1, 128));
    BlockVec.push_back(new Block("res/Test.png", -1, 0, 1, 10, 64));
    
    BlockVec.push_back(new Block(block_path[0], 0, 0, 25, 1, 64));
    BlockVec.push_back(new Block(block_path[0], 20, 1, 5, 1, 64));
    for (int i = 0; i < 20; i++)
    {
        BlockVec.push_back(new Block(block_path[6], i, 1, 1, 1, 64));
    }

    for (int i = 0; i < 107; i++)
    {
        BlockVec.push_back(new Block(block_path[6], 25 + i, 0, 1, 1, 64));
    }
    for (int i = 0; i < 29; i++)
    {
        BlockVec.push_back(new Block(block_path[6], 137 + i, 0, 1, 1, 64));
    }


    // Tsting
    for (int i = 0; i < 4; i++)
    {
        BlockVec.push_back(new Block(block_path[0], 35, 1 + i, 1, 1, 64));
    }

    // Inner (just for fillign and stuff)

    BlockVec.push_back(new Block(block_path[5], 24, 1, 1, 1, 64));
    BlockVec.push_back(new Block(block_path[5], 24, 2, 1, 1, 64));
    for (int i = 0; i < 4; i++)
    {
        const char* path = i == 0 ? block_path[7] : block_path[6];
        BlockVec.push_back(new Block(path, 24 + i, 3, 1, 1, 64));
        BlockVec.push_back(new Block(path, 28 + i, 4, 1, 1, 64));
        BlockVec.push_back(new Block(path, 32 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 120 + i, 11, 1, 1, 64));
        BlockVec.push_back(new Block(path, 131 + i, 13, 1, 1, 64));
        BlockVec.push_back(new Block(path, 160 + i, 3, 1, 1, 64));
    }
    for (int i = 0; i < 4; i++)
    {
        const char* path = i == 0 ? block_path[7] : block_path[6];
        BlockVec.push_back(new Block(path, 20 + i, 2, 1, 1, 64));
        BlockVec.push_back(new Block(path, 124 + i, 23, 1, 1, 64));
    }
    
    // for (int i = 0; i < 20; i++)
    // {
    //     BlockVec.push_back(new Block("res/Test.png", 119 + i, 24, 1, 1, 64));
    // }

    // BlockVec.push_back(new Block("res/Test.png", 36, 2, 1, 4, 64));

    // BlockVec.push_back(new Block("res/Test.png", 69, 2, 3, 5, 64));
    // BlockVec.push_back(new Block("res/Test.png", 75, 2, 3, 5, 64));
    // BlockVec.push_back(new Block("res/Test.png", 78, 5, 7, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 78, 8, 3, 12, 64));
    // BlockVec.push_back(new Block("res/Test.png", 78, 20, 2, 7, 64));
    // BlockVec.push_back(new Block("res/Test.png", 85, 11, 3, 9, 64));

    // BlockVec.push_back(new Block("res/Test.png", 92, 18, 4, 3, 64));
    // BlockVec.push_back(new Block("res/Test.png", 96, 19, 1, 2, 64));

    // BlockVec.push_back(new Block("res/Test.png", 92, 6, 20, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 95, 8, 4, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 95, 10, 4, .5, 64));
    
    // BlockVec.push_back(new Block("res/Test.png", 105, 19, 2, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 107, 18, 3, 3, 64));
    
    // BlockVec.push_back(new Block("res/Test.png", 137, 31, 10, 13, 64));
    // BlockVec.push_back(new Block("res/Test.png", 152, 30, 2, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 150, 30, 2, 4, 64));
    // BlockVec.push_back(new Block("res/Test.png", 154, 30, 2, 8, 64));
    // BlockVec.push_back(new Block("res/Test.png", 150, 38, 1, 4, 64));

    // BlockVec.push_back(new Block("res/Test.png", 151, 40, 8, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 159, 7, 2, 35, 64));
    // BlockVec.push_back(new Block("res/Test.png", 164, 1, 2, 55, 64));
    
    // BlockVec.push_back(new Block("res/Test.png", 147, 19, 3, 8, 64));
    // BlockVec.push_back(new Block("res/Test.png", 153, 17, 3, 9, 64));
    
    // BlockVec.push_back(new Block("res/Test.png", 115, 22, 1, 1, 64));

    // BlockVec.push_back(new Block("res/Test.png", 117, 29, 1, 5, 64));
    // BlockVec.push_back(new Block("res/Test.png", 115, 30, 2, 4, 64));
    // BlockVec.push_back(new Block("res/Test.png", 113, 31, 2, 3, 64));

    // BlockVec.push_back(new Block("res/Test.png", 112, 37, 3, 3, 64));
    // BlockVec.push_back(new Block("res/Test.png", 115, 37, 1, 2, 64));
    // BlockVec.push_back(new Block("res/Test.png", 116, 37, 1, 1, 64));
    
    // BlockVec.push_back(new Block("res/Test.png", 108, 42, 1, 5, 64));

    // BlockVec.push_back(new Block("res/Test.png", 112, 44, 3, 3, 64));
    // BlockVec.push_back(new Block("res/Test.png", 115, 45, 4, 2, 64));


    // BlockVec.push_back(new Block("res/Test.png", 122, 26, 5, 10, 64));

    // Every 2 tile block
    for (int i = 0; i < 2; i++)
    {
        const char* path = i == 0 ? block_path[7] : block_path[8];
        BlockVec.push_back(new Block(path, 41 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 48 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 59 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 84 + i, 1, 1, 1, 64));
        BlockVec.push_back(new Block(path, 99 + i, 1, 1, 1, 64));
        BlockVec.push_back(new Block(path, 115 + i, 1, 1, 1, 64));
        BlockVec.push_back(new Block(path, 116 + i, 9, 1, 1, 64));
        BlockVec.push_back(new Block(path, 122 + i, 1, 1, 1, 64));
        BlockVec.push_back(new Block(path, 124 + i, 2, 1, 1, 64));
        BlockVec.push_back(new Block(path, 126 + i, 3, 1, 1, 64));
        BlockVec.push_back(new Block(path, 128 + i, 4, 1, 1, 64));
        BlockVec.push_back(new Block(path, 130 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 137 + i, 5, 1, 1, 64));
        BlockVec.push_back(new Block(path, 139 + i, 4, 1, 1, 64));
        BlockVec.push_back(new Block(path, 141 + i, 3, 1, 1, 64));
        BlockVec.push_back(new Block(path, 143 + i, 2, 1, 1, 64));
        BlockVec.push_back(new Block(path, 145 + i, 1, 1, 1, 64));
    }



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
