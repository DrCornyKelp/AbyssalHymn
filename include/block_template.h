#ifndef BLOCK_TEMPLATE_H
#define BLOCK_TEMPLATE_H

#include <block.h>

struct BlockSquare
{
    int TL; int TM; int TR;
    int ML; int MM; int MR;
    int BL; int BM; int BR;

    void filterInfo(int2D square)
    {
        TL = square[0][0]; TM = square[0][1]; TR = square[0][2];
        ML = square[1][0]; MM = square[1][1]; MR = square[1][2];
        BL = square[2][0]; BM = square[2][1]; BR = square[2][2];
    }

    int2D topRow() { return {{TL, TM, TR}}; }
    int2D midRow() { return {{ML, MM, MR}}; }
    int2D botRow() { return {{BL, BM, BR}}; }

    int2D lefCol() { return {{TL}, {ML}, {BL}}; }
    int2D midCol() { return {{TM}, {MM}, {BM}}; }
    int2D rigCol() { return {{TR}, {MR}, {BR}}; }
};

class Map;
class BlockTemplate
{
private:

public:
    // ================ Block Manipulation =================

    // Get A Column (Why not also Row? Are you fucking stupid)
    static int2D getColumn(int2D vec, int col_index);
    // Split
    static Block1D splitX(Block *block);
    static Block1D splitY(Block *block);
    static Block1D split(Block *block);
    // Compare (for sorting algorithm)
    static bool compareX(Block *block1, Block *block2, bool descend = 0);
    static bool compareY(Block *block1, Block *block2, bool descend = 0);
    // Swap Index
    static void replaceIndex(Block *block, int pre, int post);
    // Expand
    static int2D expandX(int2D original, int cols);
    static int2D expandY(int2D original, int rows);
    // Merge 2 
    static int2D mergeX(int2D vec1, int2D vec2);
    static int2D mergeY(int2D vec1, int2D vec2);
    // Also Merge 2 but more convenient for my fucking console
    static Block *mergeBlockX(Block *blockMain, Block *blockSub);
    static Block *mergeBlockY(Block *blockMain, Block *blockSub);
    // Merge 3
    static int2D mergeX2(int2D vecPre, int2D vecCur, int2D vecPost);
    static int2D mergeY2(int2D vecPre, int2D vecCur, int2D vecPost);
    // MERGE SUPER!!!
    static Block1D mergeGlobal(Block1D oldVec, bool mergeRow = 0);
    // Rectangle Template
    static int2D rect(int2D vecSqr, int row, int col);

    // ================ File/Map Manipulation =================

    // Generate Block Code (.csv)
    static std::string blockToCode(Block *block);
    // Generate Block Info From Code
    static float2D codeToBlockInfo(std::string str);
    // Append Block To Map Based On File
    static void appendBlock(
        Map *map, std::string block_dir, short type = 0
    );
};

#endif