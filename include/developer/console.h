#ifndef CONSOLE_H
#define CONSOLE_H

#include <world.h>

#define BSynTempVec std::vector<BlockSyntaxTemplate>
struct ConsoleDependency
{
    Map *map;
    Input *input;
    Player *player;
    Collision *collision;
};

struct BlockSyntaxTemplate
{
    int newX = 0;
    int newY = 0;
    short type = 0;
    int2D newIndex = {{0}};
    bool valid = true;
};

struct BlockSyntax
{
    Map *map;
    Input *input;
    Player *player;
    Collision *collision;

    bool front = true;
    int ini_size = 0;

    // Self function
    void reupdateType(string1D cmd);

    // High reusability
    void Copy(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    // Delete Block
    void Delete(string1D cmd);
    // Highligh Block
    void Highlight(string1D cmd, int &start);
    // Insert Block
    void InsertOffset(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void InsertAbsolute(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void InsertSingle(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void InsertRect(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void InsertLine(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void InsertProperty(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    // Expand Block
    void ExpandX(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    void ExpandY(string1D cmd, int &start, BlockSyntaxTemplate &b_syn_temp);
    // Replace Block Index
    void Replace(string1D cmd);

    // == Global Block Functions ==
    // !! Extremely Dangerous + Performance Intensive
    // sorted| 0: none | 1: X | 2: Y |
    // PI (Performance Intensity)

    // PI [##-------------]
    void GlobalShift(string1D cmd, int &start);
    // PI [###------------]
    void GlobalSort(string1D cmd, int &start, short &sorted);
    // PI [#######--------]
    void GlobalSplit(string1D cmd, int &start);
    // PI [###############]
    void GlobalMerge(string1D cmd, int &start, short &sorted);
    /*
    Guide: Usually the order of operation generally goes like this:
    - Split Block into each column/row
    - Sort it ascending in the x/y direction
    - Merge Each Column
    */

    // f2m: File To Map, back: back?
    void UpdateBlock(bool back = 0, bool f2m = 0);

    // Append Block
    void AppendBlock(Block *block);
};

class Console
{
public:
    string0D version = "1.0.beta";
    string0D author = "Asciiz";
    string0D co_author = "Trackmaker";

    char delimiter = '|';
    char comment_syntax = '#';
    // The console file
    string0D cmd_main = "COMMAND.a";
    World *world;
    Input *input;
    Player *player;
    Collision *collision;

    BlockSyntax blocksyntax;

    Console(World *w, Input *i, Player *p, Collision *c);

    void blockCommand(Map *map, string1D cmd);
    void playerCommand(Map *map, string1D cmd);

    void execute(Map *map, string1D cmd);
    void readFile(Map *map, string0D cmd_file);
    void update();

    // ========================= Helpful =========================

    // Its like arr[-1] in python, thought beware that Max Size =/= Max Index
    static int normalizeIndex(int i, int m_size);

    static string0D toLowerCase(const string0D& str);
    static string1D splitCmdSegment(string0D str, char delimiter = '|');
    // Compare syntaxes (the reason this command exist is cuz some time the syntax index is way out of range)
    static bool syntaxComp(string1D cmd, int index, string0D keyword);
    static bool syntaxComps(string1D cmd, int index, string1D keyword);
};

#endif