#include <developer/editor.h>

void BlockEditor::normalize(int maxPath, int maxPage, int maxType)
{
    if (index < 0) index = maxPath - 1;
    if (index > maxPath - 1) index = 0;
    if (page < 0) page = maxPage - 1;
    if (page > maxPage - 1) page = 0;
    if (type < 0) type = maxType - 1;
    if (type > maxType - 1) type = 0;
}

Editor::~Editor()
{
    Object2D::deleteTextures({
        EditBack, EditLetterType, EditLetterFront, EditLetterBack,
        EditLetterDel, EditLetterGlob, EditLetterSave, EditLetterLoad,
        EditArrow.up, EditArrow.down, EditArrow.left, EditArrow.right
    });

    Object2D::deleteTextures(EditNumber);
}

Editor::Editor(Console *consl, World *w, Player *p, Collision *c) :
    console(consl), world(w), player(p), collision(c)
{
    map_cur = world->MapCurrent;

    EditBack = Object2D::loadTexture("res/Editor/EditorBack.png");

    EditArrow = {
        Object2D::loadTexture("res/Editor/ArrowUp.png"),
        Object2D::loadTexture("res/Editor/ArrowDown.png"),
        Object2D::loadTexture("res/Editor/ArrowLeft.png"),
        Object2D::loadTexture("res/Editor/ArrowRight.png")
    };

    for (int i = 0; i < 10; i++)
        EditNumber.push_back(
            Object2D::loadTexture("res/Editor/Num" + std::to_string(i) + ".png")
        );

    EditLetterType = Object2D::loadTexture("res/Editor/LetterType.png");
    EditLetterFront = Object2D::loadTexture("res/Editor/LetterFront.png");
    EditLetterBack = Object2D::loadTexture("res/Editor/LetterBack.png");
    EditLetterDel = Object2D::loadTexture("res/Editor/LetterDel.png");
    EditLetterGlob = Object2D::loadTexture("res/Editor/LetterGlobal.png");
    EditLetterSave = Object2D::loadTexture("res/Editor/LetterSave.png");
    EditLetterLoad = Object2D::loadTexture("res/Editor/LetterLoad.png");
}

void Editor::blockEditor()
{
    // Background of the editor (not important, just fun)
    int bgWidth = minimize ? 200 : CFG->WIDTH;
    SDL_Rect bgRect = {0, 0, bgWidth, 200};
    SDL_RenderCopy(CFG->RENDERER, EditBack, NULL, &bgRect);

    // SOME STARTING VALUE
    int mX = player->INPUT.getMMapX(player);
    int mY = player->INPUT.getMMapY(player);

    int pageRatioInt = map_cur->BlockPreview.size() / blockPerPage;
    int maxPage =   map_cur->BlockPreview.size() % blockPerPage ?
                    pageRatioInt + 1 : pageRatioInt;

    // ============================ INPUT ================================

    // -------------------- KEYBOARD --------------------

    // Change stuff with scroll
    if (player->INPUT.getWheel())
    {
        // Normal Scrolling -> Scroll Through Block
        if (!player->INPUT.lctrl.key)
        {
            BlockEdit.index += player->INPUT.getWheel();
            BlockEdit.normalize(map_cur->BlockPreview.size(), maxPage);
            BlockEdit.page = BlockEdit.index / blockPerPage;
        }
        // Hold Ctrl + Scrolling -> Scroll Through Type
        else
        {
            BlockEdit.type += player->INPUT.getWheel();
            BlockEdit.normalize(map_cur->BlockPreview.size(), maxPage);
        }

        player->INPUT.resetWheel();
    }

    // -------------------- MOUSE ------------------------

    int menuSize = minimize ?
        player->INPUT.mouseInBox({CFG->HEIGHT, CFG->HEIGHT - 200, 0, 200}) :
        player->INPUT.mouseInBox({CFG->HEIGHT, CFG->HEIGHT - 200});

    // INPUT WITH CERTAIN BOUNDARY
    switch (menuSize)
    {
    // Input On The Map
    case false:
        // Hover -> Highlight
        // Highlight Front
        if (BlockEdit.front) for (int i = 0; i < map_cur->BlockMainVec.size(); i++)
        {
            if (map_cur->BlockMainVec[i]->getBox().contain(
                    player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                ) && map_cur->BlockMainVec[i]->isType(BlockEdit.type))
            {
                CFG->addDevlog("B_FRONT", 46);
                CFG->addDevlog(
                    "Tpe: " + std::to_string(BlockEdit.type) +
                    " | Id: " + std::to_string(i)
                ,36);
                map_cur->BlockMainVec[i]->setHighlight(1);
            }
            else
                map_cur->BlockMainVec[i]->setHighlight(0);
        }
        // Highlight Back
        else for (int i = 0; i < map_cur->BlockBackVec.size(); i++)
        {
            if (map_cur->BlockBackVec[i]->getBox().contain(
                    player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                ) && map_cur->BlockBackVec[i]->isType(BlockEdit.type))
            {
                CFG->addDevlog("B_BACK", 44);
                CFG->addDevlog(
                    "Tpe: " + std::to_string(BlockEdit.type) +
                    " | Id: " + std::to_string(i)
                ,34);
                map_cur->BlockBackVec[i]->setHighlight(1);
            }
            else
                map_cur->BlockBackVec[i]->setHighlight(0);
        }


        // Click manipulation
        if (player->INPUT.getClickPress(0))
        { 
            player->INPUT.setClickHold(0, 1);
            DragLast = {};

            if (player->INPUT.gethold(15))
                BlockEdit.front = !BlockEdit.front;
        }

        if (player->INPUT.getClickPress(1))
        { 
            player->INPUT.setClickHold(1, 1);

            // SPLIT INTO SINU
            if (player->INPUT.gethold(15))
            {
                if (BlockEdit.front)
                for (int i = 0; i < map_cur->BlockMainVec.size(); i++)
                {
                    if (map_cur->BlockMainVec[i]->getBox().contain(
                        player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                    )&& map_cur->BlockMainVec[i]->isType(BlockEdit.type))
                    {
                        // Split into singular block
                        Block1D splitted = BlockTemplate::split(
                            map_cur->BlockMainVec[i]
                        );
                        // Erase current block
                        MapComponent::eraseBlockMain(map_cur, i);
                        // Append singular block
                        for (Block *block : splitted)
                        {
                            map_cur->BlockMainVec.push_back(block);
                            map_cur->BlockMainVec.back()->blockEngine(map_cur->BlockPath);
                        }
                        break;
                    }
                }
                else
                for (int i = 0; i < map_cur->BlockBackVec.size(); i++)
                {
                    if (map_cur->BlockBackVec[i]->getBox().contain(
                        player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                    )&& map_cur->BlockBackVec[i]->isType(BlockEdit.type))
                    {
                        // Split into singular block
                        Block1D splitted = BlockTemplate::split(
                            map_cur->BlockBackVec[i]
                        );
                        // Erase current block
                        MapComponent::eraseBlockBack(map_cur, i);
                        // Append singular block
                        for (Block *block : splitted)
                        {
                            map_cur->BlockBackVec.push_back(block);
                            map_cur->BlockBackVec.back()->blockEngine(map_cur->BlockPath);
                        }
                        break;
                    }
                }
            }
        }

        if (player->INPUT.gethold(15)) break;

        // Placing block (draggable)
        if (player->INPUT.getClickHold(0))
        {
            // Cant place in occupied position
            bool newDrag = true;
            for (int1D drag : DragLast)
                if (drag[0] == mX && drag[1] == mY)
                { newDrag = false; break; }
            if (!newDrag) break;
            DragLast.push_back({mX, mY});

            if (BlockEdit.front)
            {
                map_cur->BlockMainVec.push_back(new Block(
                mX, mY, BlockEdit.type, {{BlockEdit.index}}
                ));
                map_cur->BlockMainVec.back()->blockEngine(map_cur->BlockPath);
            }
            else
            {
                map_cur->BlockBackVec.push_back(new Block(
                mX, mY, BlockEdit.type, {{BlockEdit.index}}
                ));
                map_cur->BlockBackVec.back()->blockEngine(map_cur->BlockPath);
            }
        }
        // Deleting block (also draggable)
        if (player->INPUT.getClickHold(1))
        {
            if (BlockEdit.front)
            for (int i = 0; i < map_cur->BlockMainVec.size(); i++)
            {
                if (map_cur->BlockMainVec[i]->getBox().contain(
                    player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                )&& map_cur->BlockMainVec[i]->isType(BlockEdit.type))
                {
                    MapComponent::eraseBlockMain(map_cur, i);
                    break;
                }
            }
            else
            for (int i = 0; i < map_cur->BlockBackVec.size(); i++)
            {
                if (map_cur->BlockBackVec[i]->getBox().contain(
                    player->INPUT.getMMapX(player, 1), player->INPUT.getMMapY(player, 1)
                )&& map_cur->BlockBackVec[i]->isType(BlockEdit.type))
                {
                    MapComponent::eraseBlockBack(map_cur, i);
                    break;
                }
            }
        }
        break;

    // Input On The Editor Menu
    case true:  
        int mU = CFG->HEIGHT - 118,
            mD = CFG->HEIGHT - 178;

        // ===================== Instant Press =====================
        if (player->INPUT.getClickPress(0))
        {
            bool meaningful_input = true;

            // Change Block Type
            if (player->INPUT.mouseInBox({mU, mD, 100, 150}))
                BlockEdit.type++;
            // Change Block Direction
            else if (player->INPUT.mouseInBox({mU, mD, 150, 250}))
                BlockEdit.front = !BlockEdit.front;
            // Delete Last Block (instant)
            else if (player->INPUT.mouseInBox({mU, mD, 260, 360}))
            {
                if (BlockEdit.front) MapComponent::eraseBlockMain(
                    map_cur, map_cur->BlockMainVec.size() - 1
                );
                else                 MapComponent::eraseBlockBack(
                    map_cur, map_cur->BlockBackVec.size() - 1
                );
            }
            // Apply global function to MAP
            else if (player->INPUT.mouseInBox({mU, mD, 370, 470}))
            {
                console->execute(map_cur, {"block", "front",
                "global", "split", "sort", "merge", "sort", "y", "merge", "row"});
                console->execute(map_cur, {"block", "back",
                "global", "split", "sort", "merge", "sort", "y", "merge", "row"});
            }
            // Save Map To File
            else if (player->INPUT.mouseInBox({mU, mD, 480, 580}))
            {
                CFG->addDevlog("MAP SAVED", 45);
                console->execute(map_cur, {"block", "front", "update", "to"});
                console->execute(map_cur, {"block", "back", "update", "to"});
            }
            // Load Map From File
            else if (player->INPUT.mouseInBox({mU, mD, 590, 690}))
            {
                CFG->addDevlog("MAP LOADED", 45);
                console->execute(map_cur, {"block", "front", "update", "from"});
                console->execute(map_cur, {"block", "back", "update", "from"});
            }
            // Useless click
            else meaningful_input = false;

            if (meaningful_input) player->INPUT.setClickHold(0, 1);
        }

        if (player->INPUT.getClickPress(1) && !minimize)
        {
            bool meaningful_input = true;

            // Change Block Type
            if (player->INPUT.mouseInBox({mU, mD, 100, 150}))
                BlockEdit.type--;
            else meaningful_input = false;

            if (meaningful_input)
                player->INPUT.setClickHold(1, 1);
        }

        // ===================== Threshold Press =====================

        // Delete Last Block (repeat)
        if (player->INPUT.getClickThreshold(0, 100) &&
            player->INPUT.getClickThresValue(0) % 10 == 1 &&
            player->INPUT.mouseInBox({mU, mD, 260, 360}))
        {
            if (BlockEdit.front && map_cur->BlockMainVec.size())
                map_cur->BlockMainVec.pop_back();
            if (!BlockEdit.front && map_cur->BlockBackVec.size())
                map_cur->BlockBackVec.pop_back();
        }
        break;
    }

    // INDEX/VALUE NORMALIZER
    BlockEdit.normalize(map_cur->BlockPreview.size(), maxPage);

    // ======================= DRAW LETTER AND STUFF =====================

    // ----------------------- MINIMIZE MENU ------------------------
    SDL_Rect EditLetterRect;

    if (minimize) 
    {
        SDL_Rect blockRect = {68, 32, 64, 64};
        SDL_SetTextureAlphaMod(map_cur->BlockPreview[BlockEdit.index], 255);
        SDL_RenderCopy(CFG->RENDERER, map_cur->BlockPreview[BlockEdit.index],
            NULL, &blockRect
        );

        EditLetterRect = {20, 120, 50, 50};
        SDL_RenderCopy(CFG->RENDERER, EditNumber[BlockEdit.type],
            NULL, &EditLetterRect
        );

        EditLetterRect = {80, 120, 100, 50};
        SDL_RenderCopy(CFG->RENDERER, BlockEdit.front ? EditLetterFront :
                                                            EditLetterBack,
            NULL, &EditLetterRect
        );

        return;
    };

    // ----------------------- NORMAL SIZE MENU ---------------------

    // Chose Your Block
    for (int i = 0; i < blockPerPage; i++)
    {
        SDL_Rect blockRect = {i*96 + 32, 32, 64, 64};

        int cur_index = BlockEdit.page * blockPerPage + i;
        if (cur_index >= map_cur->BlockPreview.size()) break;

        SDL_RenderCopy(CFG->RENDERER, map_cur->BlockPreview[cur_index],
            NULL, &blockRect
        );

        if (cur_index == BlockEdit.index)
            SDL_SetTextureAlphaMod(map_cur->BlockPreview[cur_index], 255);
        else
            SDL_SetTextureAlphaMod(map_cur->BlockPreview[cur_index], 80);

        if (player->INPUT.mouseInBox({
            CFG->HEIGHT - 32, CFG->HEIGHT - 96,
            i*96 + 22, i*96 + 106}))
        {
            if (player->INPUT.getClickPress(0))
            {
                player->INPUT.setClickHold(0, 1);
                BlockEdit.index = cur_index;
            }
            else if (cur_index != BlockEdit.index)
                SDL_SetTextureAlphaMod(map_cur->BlockPreview[cur_index], 200);
        }
    }

    EditLetterRect = {0, 120, 100, 50};
    SDL_RenderCopy(CFG->RENDERER, EditLetterType,
        NULL, &EditLetterRect
    );

    EditLetterRect = {100, 120, 50, 50};
    SDL_RenderCopy(CFG->RENDERER, EditNumber[BlockEdit.type],
        NULL, &EditLetterRect
    );

    EditLetterRect = {150, 120, 100, 50};
    SDL_RenderCopy(
        CFG->RENDERER, BlockEdit.front ? EditLetterFront : EditLetterBack,
        NULL, &EditLetterRect
    );

    EditLetterRect = {260, 120, 100, 50};
    SDL_RenderCopy(
        CFG->RENDERER, EditLetterDel,
        NULL, &EditLetterRect
    );

    EditLetterRect = {370, 120, 100, 50};
    SDL_RenderCopy(
        CFG->RENDERER, EditLetterGlob,
        NULL, &EditLetterRect
    );

    EditLetterRect = {480, 120, 100, 50};
    SDL_RenderCopy(
        CFG->RENDERER, EditLetterSave,
        NULL, &EditLetterRect
    );

    EditLetterRect = {590, 120, 100, 50};
    SDL_RenderCopy(
        CFG->RENDERER, EditLetterLoad,
        NULL, &EditLetterRect
    );
}

void Editor::update()
{
    // Open/Close Editor (/)
    if (!player->INPUT.lctrl.key &&
        player->INPUT.slash.press())
    { 
        player->INPUT.slash.hold = 1;
        open = !open;
    }

    // Mini/Maximizing Editor (Ctrl + /)
    if (player->INPUT.lctrl.key &&
        player->INPUT.slash.press())
    {
        player->INPUT.slash.hold = 1;
        open = true;
        minimize = !minimize;
    }

    if (!open) return;
    // Update current map (incase of a map change)
    map_cur = world->MapCurrent;

    blockEditor();
}