#include <developer/console.h>

// ============================== BLOCK ==============================

// --------------- Self function ---------------
void BlockSyntax::reupdateType(string1D cmd)
{
    front = Console::syntaxComps(cmd, 1, {"f", "front"});
    ini_size = front ? map->BlockMainVec.size() : map->BlockBackVec.size();
}

// --------- High reusability function ---------
void BlockSyntax::Copy(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp)
{
    int b_index = Console::normalizeIndex(std::stoi(cmd[3]), ini_size);
    if (b_index == -1) return;

    Block *cur_block =  front ? map->BlockMainVec[b_index] :
                        map->BlockBackVec[b_index];

    b_syn_temp.newX = cur_block->getGridLX();
    b_syn_temp.newY = cur_block->getGridBY();
    b_syn_temp.newIndex = cur_block->getBlockIndexs();
    b_syn_temp.type = cur_block->getType();

    start++;
}

// ------------------ Delete -------------------
void BlockSyntax::Delete(string1D cmd)
{
    if (Console::syntaxComps(cmd, 3, {"a", "all"}))
    {
        if (front) MapComponent::clearBlockMain(map);
        else       MapComponent::clearBlockBack(map);
        return;
    }

    int del_index = Console::normalizeIndex(std::stoi(cmd[3]), ini_size);
    if (del_index == -1) return;

    if (front) MapComponent::eraseBlockMain(map, del_index);
    else       MapComponent::eraseBlockBack(map, del_index);
}

// ------------------ Highlight -------------------
void BlockSyntax::Highlight(string1D cmd, int &start)
{
    if (start > cmd.size() - 1) { start = -1; return; }

    int hl_state =  Console::syntaxComp(cmd, start + 1, "1") ? 1 :
                    Console::syntaxComp(cmd, start + 1, "0") ? 0 : 2;

    if (Console::syntaxComps(cmd, start, {"a", "all"}))
    {
        if (front) for (Block *block : map->BlockMainVec)
            block->setHighlight(hl_state);
        else for (Block *block : map->BlockBackVec)
            block->setHighlight(hl_state);
    }
    // Hihglight Odd
    else if (Console::syntaxComps(cmd, start, {"o", "odd"}))
    {
        if (front) for (int i = 1; i < map->BlockMainVec.size() - 1; i += 2)
            map->BlockMainVec[i]->setHighlight(hl_state);
        else for (int i = 1; i < map->BlockBackVec.size() - 1; i += 2)
            map->BlockBackVec[i]->setHighlight(hl_state);
    }
    // Highlight Even
    else if (Console::syntaxComps(cmd, start, {"e", "even"}))
    {
        if (front) for (int i = 0; i < map->BlockMainVec.size(); i += 2)
            map->BlockMainVec[i]->setHighlight(hl_state);
        else for (int i = 0; i < map->BlockBackVec.size(); i += 2)
            map->BlockBackVec[i]->setHighlight(hl_state);
    }
    // Highlight Chosen Block"s", yes, can be many
    else
    {
        int1D b_indexs_line = Map::convertStrInt1D(cmd[start]);
        for (int b : b_indexs_line)
        {
            int b_index = Console::normalizeIndex(b, ini_size);
            if (b_index == -1) continue;

            if (front) map->BlockMainVec[b_index]->setHighlight(hl_state);
            else       map->BlockBackVec[b_index]->setHighlight(hl_state);
        }
    }

    start += (1 + Console::syntaxComps(cmd, start + 1, {"1", "0"}));
}

// ------------------ Insert -------------------
void BlockSyntax::InsertOffset(string1D cmd, int &start,
                                BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComps(cmd, start, {
            "off", "offset"
        }))
    return;

    int1D newXY = Map::convertStrInt1D(cmd[start + 1]);
    b_syn_temp.newX += newXY[0];
    b_syn_temp.newY += newXY[1];
    start += 2;
}

void BlockSyntax::InsertAbsolute(string1D cmd, int &start,
                                BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComps(cmd, start, {
            "ab", "abs", "absolute"
        }))
    return;

    int1D newXY = Map::convertStrInt1D(cmd[start + 1]);
    b_syn_temp.newX = newXY[0];
    b_syn_temp.newY = newXY[1];
    start += 2;
}

void BlockSyntax::InsertSingle(string1D cmd, int &start,
                                BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComps(cmd, start, {
            "si", "sin", "sing", "single" 
        }))
    return;

    b_syn_temp.newIndex = {{std::stoi(cmd[start + 1])}};
    start += 2;
}

void BlockSyntax::InsertLine(string1D cmd, int &start,
                            BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComps(cmd, start, {"li", "line"})) return;

    bool lineY = Console::syntaxComp(cmd, start + 1, "y");

    int1D index1d = Map::convertStrInt1D(cmd[start + 2]);
    int2D index2d;
    if (lineY) for (int index : index1d) index2d.push_back({index});
    else index2d = {index1d};

    b_syn_temp.newIndex = index2d;

    start += 3;
}

void BlockSyntax::InsertRect(string1D cmd, int &start,
                            BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComps(cmd, start, {"re", "rect"})) return;

    int1D rect_index_1d = Map::convertStrInt1D(cmd[start + 1]);
    int2D rect_new_index;

    // Invalid Block
    if (rect_index_1d.size() != 9 && rect_index_1d.size() != 4)
    {
        start = -1;
        b_syn_temp.valid = false;
        return;
    }

    // 2 x 2 Block
    if (rect_index_1d.size() == 4)
    {
        rect_new_index = Map::resizeInt2D(rect_index_1d, 2, 2);
        start += 2;
    }
    // 3 x 3 Block
    else if (rect_index_1d.size() == 9)
    {
        int2D rect_index_2d = Map::resizeInt2D(rect_index_1d, 3, 3);
        int1D rect_size = Map::convertStrInt1D(cmd[start + 2]);

        rect_new_index = BlockTemplate::rect(
        rect_index_2d, rect_size[1], rect_size[0]);
        start += 3;
    }

    b_syn_temp.newIndex = rect_new_index;
}

void BlockSyntax::InsertProperty(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp)
{
    if (start > cmd.size() - 1) return;
    b_syn_temp.type = std::stoi(cmd[start]);
}

// ------------------ Expand -------------------

void BlockSyntax::ExpandX(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComp(cmd, start, "x"))
    return;

    int expandWidth = std::stoi(cmd[start + 1]);

    // Cant resize to itself or nothing
    if (abs(expandWidth) <= 1)
    { start = -1; return; }

    if (expandWidth < 0) b_syn_temp.newX += expandWidth + 1;

    b_syn_temp.newIndex = BlockTemplate::expandX(
        b_syn_temp.newIndex, abs(expandWidth)
    );

    start += 2;
}

void BlockSyntax::ExpandY(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp)
{
    if (start == -1 || !b_syn_temp.valid ||
        !Console::syntaxComp(cmd, start, "y"))
    return;

    int expandHeight = std::stoi(cmd[start + 1]);

    // Cant resize to itself or nothing
    if (abs(expandHeight) <= 1)
    { start = -1; return; }

    if (expandHeight < 0) b_syn_temp.newY += expandHeight + 1;

    b_syn_temp.newIndex = BlockTemplate::expandY(
        b_syn_temp.newIndex, abs(expandHeight)
    );

    start += 2;
}

void BlockSyntax::Replace(string1D cmd)
{
    int oldIndex = std::stoi(cmd[3]),
        newIndex = std::stoi(cmd[4]);

    for (Block *block : (front ? map->BlockMainVec : map->BlockBackVec))
        BlockTemplate::replaceIndex(block, oldIndex, newIndex);
}

void BlockSyntax::GlobalShift(string1D cmd, int &start)
{
    if (!Console::syntaxComp(cmd, start, "shift")) return;

    int1D shiftXY = Map::convertStrInt1D(cmd[start + 1]);

    for (Block *block : (front ? map->BlockMainVec : map->BlockBackVec))
    {
        block->setX(block->getX() + shiftXY[0] * 64);
        block->setY(block->getY() + shiftXY[1] * 64);
    }

    start += 2;
}

void BlockSyntax::GlobalSort(string1D cmd,  int &start, short &sorted)
{
    if (!Console::syntaxComp(cmd, start, "sort"))
    return;

    bool compareY = Console::syntaxComp(cmd, start + 1, "y");
    bool descend = Console::syntaxComp(cmd, start + 2, "descend");

    sorted = compareY ? 2 : 1;

    if (front)
        std::sort(map->BlockMainVec.begin(), map->BlockMainVec.end(),
        [compareY, descend](Block* a, Block* b) {
            return compareY ?   BlockTemplate::compareY(a, b, descend):
                                BlockTemplate::compareX(a, b, descend);
        });
    else
        std::sort(map->BlockBackVec.begin(), map->BlockBackVec.end(),
        [compareY, descend](Block* a, Block* b) {
            return compareY ?   BlockTemplate::compareY(a, b, descend):
                                BlockTemplate::compareX(a, b, descend);
        });

    start += (1+Console::syntaxComps(cmd, start + 1, {"x", "y"}) +
                Console::syntaxComps(cmd, start + 2, {"ascend", "descend"}));
}

void BlockSyntax::GlobalSplit(string1D cmd, int &start)
{
    if (!Console::syntaxComp(cmd, start, "split")) return;

    bool splitRow = Console::syntaxComp(cmd, start + 1, "row");

    Block1D newBlockMainVec;
    for (Block *block : (front ? map->BlockMainVec : map->BlockBackVec))
        for (Block *block_col : (splitRow ? BlockTemplate::splitX(block):
                                            BlockTemplate::splitY(block)))
        {
            block_col->needReset = true;
            newBlockMainVec.push_back(block_col);
        }

    if (front) map->BlockMainVec = newBlockMainVec;
    else       map->BlockBackVec = newBlockMainVec;

    start += (1 + Console::syntaxComps(cmd, start + 1, {"row", "col"}));
}

void BlockSyntax::GlobalMerge(string1D cmd,  int &start, short &sorted)
{
    bool mergeRow = Console::syntaxComp(cmd, start + 1, "row");
    // Have to be sorted accordingly in order to work
    if (!Console::syntaxComp(cmd, start, "merge") ||
        (!mergeRow && (sorted != 1)) ||
        (mergeRow && (sorted != 2))
    ) return;

    Block1D oldBlockMainVec = (front ? map->BlockMainVec : map->BlockBackVec);
    Block1D newBlockMainVec = BlockTemplate::mergeGlobal(oldBlockMainVec, mergeRow);

    if (front) map->BlockMainVec = newBlockMainVec;
    else       map->BlockBackVec = newBlockMainVec;

    start += (1 + Console::syntaxComps(cmd, start + 1, {"row", "col"}));
}

void BlockSyntax::UpdateBlock(bool back, bool f2m)
{
    string0D block_path = map->MapDirectory +
                            (back ? "/block_back.csv" :
                                    "/block_main.csv");

    // FILE TO MAP
    if (f2m)
    {
        if (back) MapComponent::clearBlockBack(map);
        else      MapComponent::clearBlockMain(map);
        BlockTemplate::appendBlock(map, block_path, !back);
        return;
    }

    // MAP TO FILE
    string0D block_string = "";
    for (Block *block : back ? map->BlockBackVec : map->BlockMainVec)
        block_string += BlockTemplate::blockToCode(block);

    std::ofstream outputFile(block_path);
    outputFile << block_string;
}

void BlockSyntax::AppendBlock(Block *block)
{
    if (front) map->BlockMainVec.push_back(block);
    else       map->BlockBackVec.push_back(block);
}

// ======================= SUB FUNCTION ==============================

// ======================= MAIN CONSOLE ============================== 

Console::Console(World *w, Input *i, Player *p, Collision *c) :
    world(w), input(i), player(p), collision(c)
{};

void Console::blockCommand(Map *map,string1D cmd)
{
    blocksyntax.reupdateType(cmd);

    // Insert Block
    if (syntaxComp(cmd, 2, "insert"))
    {
        BlockSyntaxTemplate b_syn_temp = {
            player->getGridX(),
            player->getGridY(),
            0, {{0}}
        };
        int step = 3;

        blocksyntax.InsertOffset(cmd, step, b_syn_temp);
        blocksyntax.InsertAbsolute(cmd, step, b_syn_temp);
        blocksyntax.InsertSingle(cmd, step, b_syn_temp);
        blocksyntax.InsertRect(cmd, step, b_syn_temp);
        blocksyntax.InsertLine(cmd, step, b_syn_temp);
        blocksyntax.InsertProperty(cmd, step, b_syn_temp);

        if (!b_syn_temp.valid) return;

        Block *newBlock = new Block(
            b_syn_temp.newX, b_syn_temp.newY,
            b_syn_temp.type, b_syn_temp.newIndex);
        newBlock->blockEngine(map->BlockPath);
        blocksyntax.AppendBlock(newBlock);
    }

    // Delete Block
    if (syntaxComp(cmd, 2, "delete") && blocksyntax.ini_size)
        blocksyntax.Delete(cmd);

    // Highlight block
    if (syntaxComp(cmd, 2, "highlight") && blocksyntax.ini_size)
    {
        int step = 3;
        while (step != -1) blocksyntax.Highlight(cmd, step);
    }

    // Extending Block
    if (syntaxComp(cmd, 2, "expand") && blocksyntax.ini_size)
    {
        BlockSyntaxTemplate b_syn_temp = {};
        int step = 3;

        // Create Copy
        blocksyntax.Copy(cmd, step, b_syn_temp);
        // New Block Offset/Absolute
        blocksyntax.InsertOffset(cmd, step, b_syn_temp);
        blocksyntax.InsertAbsolute(cmd, step, b_syn_temp);
        // New Block Expand
        blocksyntax.ExpandX(cmd, step, b_syn_temp);
        blocksyntax.ExpandY(cmd, step, b_syn_temp);

        Block *newBlock = new Block(
            b_syn_temp.newX, b_syn_temp.newY,
            b_syn_temp.type, b_syn_temp.newIndex);
        newBlock->blockEngine(map->BlockPath);
        // Delete Old Unextended Block
        if (blocksyntax.front) MapComponent::eraseBlockMain(map, blocksyntax.ini_size - 1);
        else                   MapComponent::eraseBlockBack(map, blocksyntax.ini_size - 1);
        // Append New Block
        blocksyntax.AppendBlock(newBlock);
    }

    // Replace Block Index
    if (syntaxComp(cmd, 2, "replace") && blocksyntax.ini_size)
    {
        blocksyntax.Replace(cmd);
    }

    // Global Block Function
    if (syntaxComp(cmd, 2, "global") && blocksyntax.ini_size)
    {
        int step = 3;
        // This boolean needed to make
        // the global merge function workds
        short sorted = 0;
        blocksyntax.GlobalShift(cmd, step);
        blocksyntax.GlobalSplit(cmd, step);
        blocksyntax.GlobalSplit(cmd, step);
        blocksyntax.GlobalSort(cmd, step, sorted);
        blocksyntax.GlobalMerge(cmd, step, sorted);
        blocksyntax.GlobalSort(cmd, step, sorted);
        blocksyntax.GlobalMerge(cmd, step, sorted);

        // Reupdate block
        for (Block *block : (blocksyntax.front ? map->BlockMainVec : map->BlockBackVec))
            if (block->needReset)
                block->blockEngine(map->BlockPath);
    }

    // Update block_main.csv Info
    if (syntaxComp(cmd, 2, "update"))
        blocksyntax.UpdateBlock(!blocksyntax.front, syntaxComp(cmd, 3, "from"));
}

void Console::playerCommand(Map *map, string1D cmd)
{
    // Experimental (not useful at all)
    if (syntaxComp(cmd, 1, "map"))
    {
        int newMapIndex = std::stoi(cmd[2]);
        world->switchMap({
            newMapIndex, player->getGridX(), player->getGridY()
        });
    }

    if (syntaxComp(cmd, 1, "reset"))
    {
        map->MapComp.clearComponent(map);
        map->MapComp.appendComponent(map);
    }
}

void Console::execute(Map *map, string1D cmd)
{
    // Cant use switch statement (yet) cuz no enum type :(
    if (syntaxComp(cmd, 0, "read")) readFile(map, cmd[1]);
    if (syntaxComp(cmd, 0, "block")) 
    {
        if (world->MapCurrent->MapEmpty) return;
        blocksyntax = {world->MapCurrent, input, player, collision};
        blockCommand(map, cmd);
    }
    if (syntaxComp(cmd, 0, "player")) playerCommand(map, cmd);
}

void Console::readFile(Map *map, string0D cmd_file)
{
    // Read File
    std::ifstream inputFile(cmd_file);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Filter Data (remove all whitespace)
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

        // Empty or Comment => Skip
        if (line.empty() ||
            line.back() == comment_syntax ||
            line[0] == comment_syntax) continue;
        // End the Console Command
        if (line == "Break") break;

        // Split cmd into segment
        string1D cmd = splitCmdSegment(line);
        // Execute Each Command
        execute(map, cmd);
    }
}

void Console::update()
{
    if (input->getKeyPress(10))
    {
        input->setKeyHold(10, 1);
        readFile(world->MapCurrent, cmd_main);
    };
}

// ============================= Helpful =============================

int Console::normalizeIndex(int i, int m_size)
{
    // No size
    if (m_size < 1) return -1;
    // Normalization
    int index = i;
    if (index < 0) index = m_size + index;
    // STILL < 0 or is too large
    if (index >= m_size || index < 0) return -1;
    return index;
}

string0D Console::toLowerCase(const string0D& str) {
    string0D result;
    for (char c : str)
        result += std::tolower(c);
    return result;
}

string1D Console::splitCmdSegment(string0D str, char delimiter) {
    std::vector<string0D> tokens;
    std::stringstream ss(str);
    string0D token;

    while (std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

// Compare syntax
bool Console::syntaxComp(string1D cmd, int index, string0D keyword)
{
    if (index < cmd.size() &&
        toLowerCase(cmd[index]) == keyword)
        return true;

    return false;
}
// Also Compare syntax but with multiple compatible keywords
bool Console::syntaxComps(string1D cmd, int index, string1D keywords)
{
    if (index >= cmd.size()) return false;

    for (string0D keyword : keywords)
        if (syntaxComp(cmd, index, keyword)) return true;

    return false;
}