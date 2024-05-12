#include <map.h>

int2D BlockTemplate::getColumn(int2D vec, int col_index)
{
    int2D newVec;

    for (int1D row : vec)
        newVec.push_back({{row[col_index]}});

    return newVec;
}

// ================= SPLITTING BLOCK =================

Block1D BlockTemplate::splitX(Block *block)
{
    int oldHeight = block->getGridHeight();
    int oldGridX = block->getGridLX();
    int oldGridY = block->getGridBY();
    short oldType = block->getType();

    Block1D block1d;
    for (int row = 0; row < oldHeight; row++)
    {
        block1d.push_back(new Block(
            oldGridX, oldGridY + row, oldType,
            {block->getBlockIndexs()[oldHeight - row - 1]}
        ));
    }

    return block1d;
}
Block1D BlockTemplate::splitY(Block *block)
{
    int oldWidth = block->getGridWidth();
    int oldGridX = block->getGridLX();
    int oldGridY = block->getGridBY();
    short oldType = block->getType();

    Block1D block1d;
    for (int col = 0;
        col < block->getBlockIndexs()[0].size();
        col++)
    {
        block1d.push_back(new Block(
            oldGridX + col, oldGridY, oldType,
            BlockTemplate::getColumn(
                block->getBlockIndexs(), col
            )
        ));
    }

    return block1d;
}
// Split into singular 1x1 block
Block1D BlockTemplate::split(Block *block)
{
    Block1D block1d;
    Block1D block1dX = splitX(block);
    for (Block *bX : block1dX)
    {
        Block1D block1dY = splitY(bX);
        for (Block *bY : block1dY)
            block1d.push_back(bY);
    }

    return block1d;
}

// ================= COMPARING BLOCK =================

bool BlockTemplate::compareX(Block *block1, Block *block2, bool descend)
{
    // Block 1
    int lx1 = block1->getGridLX();
    int by1 = block1->getGridBY();
    // Block 2
    int lx2 = block2->getGridLX();
    int by2 = block2->getGridBY();
    // Blocks Prop (with priority)
    int pr1 = block1->getType();
    int pr2 = block2->getType();

    // Some block type must 100% be in front no matter what
    if (pr1 != pr2) return pr1 < pr2;
    switch (descend)
    {
    case true:
        if (lx1 == lx2) return by1 > by2;
        return lx1 > lx2; break;
    case false:
        if (lx1 == lx2) return by1 < by2;
        return lx1 < lx2; break;
    }
}
bool BlockTemplate::compareY(Block *block1, Block *block2, bool descend)
{
    // Block 1
    int lx1 = block1->getGridLX();
    int by1 = block1->getGridBY();
    // Block 2
    int lx2 = block2->getGridLX();
    int by2 = block2->getGridBY();
    // Blocks Prop (with priority)
    int pr1 = block1->getType();
    int pr2 = block2->getType();

    // Some block type must 100% be in front no matter what
    if (pr1 != pr2) return pr1 < pr2;
    switch (descend)
    {
    case true:
        if (by1 == by2) return lx1 > lx2;
        return by1 > by2; break;
    case false:
        if (by1 == by2) return lx1 < lx2;
        return by1 < by2; break;
    }
}

// ================= REPLACING INDEX ==================
void BlockTemplate::replaceIndex(Block *block, int pre, int post)
{
    int2D oldIndex = block->getBlockIndexs();

    for (int r = 0; r < oldIndex.size(); r++)
    for (int c = 0; c < oldIndex[r].size(); c++)
    { if (oldIndex[r][c] == pre) oldIndex[r][c] = post; }

    block->setBlockIndexs(oldIndex);
}

// ================= EXPANDING BLOCK =================

int2D BlockTemplate::expandX(int2D original, int cols)
{
    int2D expanded;

    for (int1D row : original)
    {
        int1D expandedRow;

        for (int i = 0; i < cols; ++i)
            expandedRow.push_back(row[0]);

        expanded.push_back(expandedRow); // Add the expanded row to the expanded vector
    }

    return expanded;
}
int2D BlockTemplate::expandY(int2D original, int rows)
{
    int2D expanded;
    int1D row = original[0];

    for (int i = 0; i < rows; ++i)
        expanded.push_back(row);

    return expanded;
}

// ================= MERGING BLOCK =================

// Merge 2 Blocks
int2D BlockTemplate::mergeX(int2D vec1, const int2D vec2)
{
    int2D merged = vec1;

    for (int i = 0; i < vec2.size(); i++)
        for (int j = 0; j < vec2[0].size(); j++)
            merged[i].push_back(vec2[i][j]);

    return merged;
}
int2D BlockTemplate::mergeY(int2D vec1, int2D vec2)
{
    int2D merged = vec1;

    for (int1D row : vec2)
        merged.push_back(row);

    return merged;
}

// Merge 2 Blocks and return the Block instead (nice)
Block *BlockTemplate::mergeBlockX(Block *block1, Block *block2)
{
    // Must be the same type of block
    if (block1->getType() != block2->getType()) return new Block();

    BlockGrid gridLeft, gridRight;

    if (block1->getGridLX() > block2->getGridLX())
    {
        gridRight = block1->getGrid();
        gridLeft = block2->getGrid();
    }
    else
    {
        gridLeft = block1->getGrid();
        gridRight = block2->getGrid();
    }

    // Invalid merge
    if (gridLeft.by != gridRight.by ||
        gridLeft.h  != gridRight.h  ||
        gridLeft.lx == gridRight.lx ||
        (gridRight.lx - gridLeft.lx != gridLeft.w)
    )   return new Block();

    int newLX = gridLeft.lx;
    int newBY = gridLeft.by;
    int2D newIndex = mergeX(gridLeft.index, gridRight.index);

    return new Block(newLX, newBY, block1->getType(), newIndex);
}
Block *BlockTemplate::mergeBlockY(Block *block1, Block *block2)
{
    // Must be the same type of block
    if (block1->getType() != block2->getType()) return new Block();

    BlockGrid gridUp, gridDown;

    if (block1->getGridBY() > block2->getGridBY())
    {
        gridUp = block1->getGrid();
        gridDown = block2->getGrid();
    }
    else
    {
        gridDown = block1->getGrid();
        gridUp = block2->getGrid();
    }

    // Invalid merge
    if (gridUp.lx != gridDown.lx ||
        gridUp.w  != gridDown.w  ||
        gridUp.by == gridDown.by ||
        (gridUp.by - gridDown.by != gridDown.h)
    )
        return new Block();

    int newLX = gridDown.lx;
    int newBY = gridDown.by;
    int2D newIndex = mergeY(gridUp.index, gridDown.index);

    return new Block(newLX, newBY, block1->getType(), newIndex);
}

// Merge 3 Blocks
int2D BlockTemplate::mergeX2(int2D vecPre, int2D vecCur, int2D vecPost)
{
    int2D merged = vecPre;

    int height = vecCur.size();

    for (int i = 0; i < height; i++)
        for (int j = 0; j < vecCur[0].size(); j++)
            merged[i].push_back(vecCur[i][j]);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < vecPost[0].size(); j++)
            merged[i].push_back(vecPost[i][j]);

    return merged;
}
int2D BlockTemplate::mergeY2(int2D vecPre, int2D vecCur, int2D vecPost)
{
    int2D merged = vecPre;

    for (int1D row : vecCur)
        merged.push_back(row);
    for (int1D row : vecPost)
        merged.push_back(row);

    return merged;
}

Block1D BlockTemplate::mergeGlobal(Block1D oldVec, bool mergeRow)
{
    Block1D newVec;

    for (Block *block : oldVec)
    {
        // Initialize emptyness
        if (!newVec.size())
        { newVec.push_back(block); continue; }

        // Get A Merge Block (if possible)
        Block *mergeBlock = mergeRow ?
        BlockTemplate::mergeBlockX(block, newVec.back()) :
        BlockTemplate::mergeBlockY(block, newVec.back());
        mergeBlock->needReset = true;

        // If valid block then append
        if (mergeBlock->isValid)
        {
            newVec.pop_back();
            newVec.push_back(mergeBlock);
        }
        else
            newVec.push_back(block);
    }

    return newVec;
}

// ================= CREATING BLOCK =================

// Squarify A Block (WHAT THE FUCK IS THAT WORD LMAO)
int2D BlockTemplate::rect(int2D vecSqr, int row, int col)
{
    // Must be a 3x3 vec To expand
    if (vecSqr.size() != 3 ||
        vecSqr[0].size() != 3 ||
        row < 2 || col < 2) return vecSqr;

    BlockSquare bSqr;
    bSqr.filterInfo(vecSqr);

    int2D newTop = mergeX2(
        {{bSqr.TL}},
        expandX({{bSqr.TM}}, col - 2),
        {{bSqr.TR}}
    );
    int2D newMid = expandY(
        mergeX2(
        {{bSqr.ML}},
        expandX({{bSqr.MM}}, col - 2),
        {{bSqr.MR}}
    ), row - 2);
    int2D newBot = mergeX2(
        {{bSqr.BL}},
        expandX({{bSqr.BM}}, col - 2),
        {{bSqr.BR}}
    );

    int2D newVec = mergeY2(newTop, newMid, newBot);

    return newVec;
}

// ========================= Other Method =============================

string0D BlockTemplate::blockToCode(Block *block)
{
    string0D block_main =
        std::to_string(block->getType()) + "," +
        std::to_string(block->getGridLX()) + "," +
        std::to_string(block->getGridBY()) + "," +
        std::to_string(block->getGridWidth()) + "," +
        std::to_string(block->getGridHeight());

    string0D block_engine = "";
    for (int1D r : block->getBlockIndexs())
        for (int v : r)
            block_engine += "," + std::to_string(v);

    return block_main + block_engine + "\n";
}

float2D BlockTemplate::codeToBlockInfo(string0D str)
{
    float1D values = CFG->convertStrFloat1D(str, ',');
    float1D prop;

    for (int i = 0; i < 5; i++)
        prop.push_back(values[i]);

    float1D index;
    for (int i = 5; i < values.size(); i++)
        index.push_back(values[i]);

    return {prop, index};
}

void BlockTemplate::appendBlock(
    Map *map, string0D block_dir, short type
){
    std::ifstream inputFile(block_dir);
    string0D line;

    Block1D hiddenSection;
    while (std::getline(inputFile, line)) 
    {
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] ==  '#') continue;

        if (line == ">")
        {
            map->BlockHiddenVec.push_back(hiddenSection);
            hiddenSection = {};
            continue;
        }

        float2D info = BlockTemplate::codeToBlockInfo(line);

        int2D index_info = CFG->convertFloat2DInt(
            CFG->resizeFloat2D(
                info[1], info[0][4], info[0][3]
            )
        );

        switch (type)
        {
        case 0:
            map->BlockMainVec.push_back(new Block(info[0]));
            map->BlockMainVec.back()->blockEngine(
                map->BlockPath, index_info
            );
            break;

        case 1:
            map->BlockBackVec.push_back(new Block(info[0]));
            map->BlockBackVec.back()->blockEngine(
                map->BlockPath, index_info
            );
            break;

        case 2:
            info[0][0] = -1;
            hiddenSection.push_back(new Block(info[0]));
            hiddenSection.back()->blockEngine(
                map->BlockPath, index_info
            );
            break;
        }
    }

    if (hiddenSection.size())
        map->BlockHiddenVec.push_back(hiddenSection);
}