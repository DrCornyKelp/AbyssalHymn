#include "map/map1.h"

void Map1::initBlocksBack(SDL_Renderer *renderer)
{}

void Map1::initBlocks(SDL_Renderer *renderer)
{
    // Boundary Left
    BlockVec.push_back(new Block(-5, 0, 5, 100));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        BlockTemplate::expandX(
            BlockTemplate::expandY({{0}}, 100), 4
        ),
        BlockTemplate::expandY({{8}}, 100)
    ));
    
    // Starting Ground
    BlockVec.push_back(new Block(-1, -1, 21, 3, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        {{19}, {7}, {7}},
        BlockTemplate::expandX({{18}, {0}, {0}}, 20)
    ));

     // Starting stair blocks
    BlockVec.push_back(new Block(20, 0, 4, 3, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        {{19, 18, 18, 18}},
        BlockTemplate::expandY({{0, 0, 0, 0}}, 2)
    ));
    BlockVec.push_back(new Block(24, 0, 4, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        {{19, 18, 18, 18}},
        BlockTemplate::expandY({{0, 0, 0, 0}}, 3)
    ));
    BlockVec.push_back(new Block(28, 0, 4, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        {{19, 18, 18, 18}},
        BlockTemplate::expandY({{0, 0, 0, 0}}, 4)
    ));
    BlockVec.push_back(new Block(32, 2, 4, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18, 20}},
        {{7, 0, 0, 8}},
        BlockTemplate::expandY({{0, 0, 0, 8}}, 3)
    ));

    // After the stair blocks
    BlockVec.push_back(new Block(32, 0, 20, 2, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        BlockTemplate::expandX({{0}, {0}}, 4),
        BlockTemplate::expandX({{18}, {0}}, 16)
    ));

    BlockVec.push_back(new Block(40, 5, 7, 2, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {2}},
        BlockTemplate::expandX({{18}, {1}}, 5),
        {{20}, {3}}
    ));

    BlockVec.push_back(new Block(52, 0, 1, 3, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19}, {0}, {0}}
    );

    BlockVec.push_back(new Block(53, 0, 8, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {0}, {0}, {0}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}}, 6),
        {{20}, {8}, {8}, {8}}
    ));

    BlockVec.push_back(new Block(64, 0, 5, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {7}, {7}, {7}, {7}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}, {0}}, 3),
        {{0}, {0}, {0}, {0}, {8}}
    ));

    BlockVec.push_back(new Block(68, 1, 2, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 20}},
        BlockTemplate::expandY({{nb, 8}}, 3),
        {{nb, 3}}
    ));

    BlockVec.push_back(new Block(74, 0, 3, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        {{19, 18, 20}},
        BlockTemplate::expandY({{7, 0, 8}}, 6)
    ));

    BlockVec.push_back(new Block(80, 0, 7, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}},
        BlockTemplate::expandX({{18}}, 5),
        {{20}}
    ));

    BlockVec.push_back(new Block(81, 2, 3, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18}},
        BlockTemplate::expandY({{7, 0, 0}}, 5),
        {{2, 1, 3}}
    ));

    BlockVec.push_back(new Block(84, 3, 1, 6, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{20}},
        BlockTemplate::expandY({{8}}, 4),
        {{3}}
    ));

    // Bridge 1
    BlockVec.push_back(new Block(85, 8, 11, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{22}},
        BlockTemplate::expandX({{21}}, 9),
        {{23}}
    ));

    BlockVec.push_back(new Block(92, 0, 15, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        {{19}},
        BlockTemplate::expandX({{18}}, 14)
    ));

    BlockVec.push_back(new Block(96, 3, 5, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18, 18, 20}},
        BlockTemplate::expandY({{7, 0, 0, 0, 8}}, 5),
        {{2, 0, 0, 0, 3}}
    ));

    BlockVec.push_back(new Block(97, 2, 3, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{2, 1, 3}}
    );

    BlockVec.push_back(new Block(97, 11, 3, 3, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19, 18, 20},
     {7, 0, 8},
     {2, 1, 3}}
    );

    // Bridge 2
    BlockVec.push_back(new Block(101, 9, 8, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{22}},
        BlockTemplate::expandX({{21}}, 6),
        {{23}}
    ));

    BlockVec.push_back(new Block(107, 0, 14, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        {{19}, {7}, {7}, {0}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}}, 13)
    ));

    BlockVec.push_back(new Block(109, 6, 5, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18, 18, 20}},
        BlockTemplate::expandY({{7, 0, 0, 0, 8}}, 2),
        {{2, 0, 0, 0, 8}}
    ));

    BlockVec.push_back(new Block(110, 5, 4, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{2, 1, 1, 3}}
    );

    BlockVec.push_back(new Block(110, 11, 3, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19, 18, 20},
     {7, 0, 8},
     {7, 0, 8},
     {2, 1, 3}}
    );

    BlockVec.push_back(new Block(119, 9, 5, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 0, 0, 0, 20}},
        BlockTemplate::expandY({{7, 0, 0, 0, 8}}, 5),
        {{2, 1, 1, 1, 3}}
    ));
    
    BlockVec.push_back(new Block(120, 16, 3, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19, 18, 20}}
    );

    BlockVec.push_back(new Block(120, 0, 8, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {0}, {0}, {0}, {0}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}, {0}}, 6),
        {{18}, {0}, {0}, {0}, {3}}
    ));

    BlockVec.push_back(new Block(128, 1, 1, 8, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19}, {7}, {7}, {7}, {0}, {0}, {0}, {3}});

    BlockVec.push_back(new Block(129, 2, 1, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{18}, {0}, {0}, {0}, {0}, {0}, {3}});

    BlockVec.push_back(new Block(130, 3, 1, 6, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{18}, {0}, {0}, {0}, {0}, {3}});

    BlockVec.push_back(new Block(131, 4, 1, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{20}, {8}, {8}, {8}, {3}});

    BlockVec.push_back(new Block(131, 12, 6, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{21, 21, 21, 21, 21, 23}});

    BlockVec.push_back(new Block(137, 5, 4, 8, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18, 20}},
        BlockTemplate::expandY({{7, 0, 0, 8}}, 6),
        {{2, 0, 0, 8}}
    ));

    BlockVec.push_back(new Block(138, 0, 3, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
        BlockTemplate::expandY({{7, 0, 8}}, 5)
    );

    // std::cout << BlockVec.size() - 1;
}

void Map1::initNpcDialogues(SDL_Renderer *renderer)
{
    // Teach jump
    NpcVec.push_back(new NpcDialogue("res/NpcSheet/Npc2/Squid.png", "res/NpcSheet/Npc2/SquidJumpTutorial.png",
        17, 3, 2, 2, 3, 3, 300, 138, 32, 32, 4, 25, 0, 0, 230));

    // Teach hold jump
    NpcVec.push_back(new NpcDialogue("res/NpcSheet/Npc2/Squid.png", "res/NpcSheet/Npc2/SquidSuperJumpTutorial.png",
        56.5, 5, 2, 2, 3, 3, 300, 138, 32, 32, 4, 25, 0, 0, 230));

    // Teach crawl
    NpcVec.push_back(new NpcDialogue("res/NpcSheet/Npc2/Squid.png", "res/NpcSheet/Npc2/SquidSuperJumpTutorial.png",
        78, 5, 2, 2, 3, 3, 300, 138, 32, 32, 4, 25, 0, 0, 230));

    // Teach super jump
    NpcVec.push_back(new NpcDialogue("res/NpcSheet/Npc2/Squid.png", "res/NpcSheet/Npc2/SquidSuperJumpTutorial.png",
        100, 6, 2, 2, 5, 5, 300, 138, 32, 32, 4, 25, 0, 0, 230));

    for (NpcDialogue *npc : NpcVec)
        npc->initNpc(renderer);
}

void Map1::initBackground(SDL_Renderer *renderer)
{
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer1.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer1.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer2.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer2.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer3.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer3.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer4.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer4.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer5.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer5.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer6.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    BackgroundVec.push_back(new Decoration("res/Decoration/Background3/Layer6.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));

    for (Decoration *background : BackgroundVec)
    {
        background->setBackground(true);
        background->initDecoration(renderer);
    }
}

void Map1::initBackDecors(SDL_Renderer *renderer)
{
    DecorBackVec.push_back(new Decoration("res/Decoration/House1.png", 0, 2, 15, 12.5));

    for (Decoration *backDecor : DecorBackVec)
        backDecor->initDecoration(renderer);
}

void Map1::initFrontDecors(SDL_Renderer *renderer)
{
    DecorFrontVec.push_back(new Decoration("res/Decoration/Tree1.png", 24, 3, 4.3, 5));
    // DecorFrontVec.push_back(new Decoration("res/Decoration/House1Rail.png", 0, 2, 15, 1.4));
    DecorFrontVec.push_back(new Decoration("res/Decoration/Grass1.png", 0, 1.99, 20, 2));

    // Filter
    DecorFrontVec.push_back(new Decoration("res/Decoration/Background3/LayerColor.png", 0, 0, Game::WIDTH / 64, float(Game::HEIGHT) / 64));
    DecorFrontVec[DecorFrontVec.size() - 1]->setAbs(true);

    for (Decoration *frontDecor : DecorFrontVec)
        frontDecor->initDecoration(renderer);
}

void Map1::initMapPlayer(Player *player)
{
    // Set spawn point
    player->setX(checkpoint_x * 64);
    player->setY(checkpoint_y * 64);

    // Set player Camera 
    player->setFocusFunction([](Player *player) {
        // Focus X
        if (player->getX() < Game::WIDTH / 2)
        {
            player->setUnfocusX(true);
            player->setUnfocusOffsetX(Game::WIDTH / 2);
            player->setOffsetMidX(player->getX() - Game::WIDTH / 2);
        }
        // else if (player->getX() > Game::WIDTH * 2)
        // {
        //     player->setUnfocusX(true);
        //     player->setUnfocusOffsetX(Game::WIDTH * 2);
        //     player->setOffsetMidX(player->getX() - Game::WIDTH * 2);
        // }
        else player->setUnfocusX(false);
        // Focus Y
        if (player->getY() < Game::HEIGHT / 2)
        {
            player->setUnfocusY(true);
            player->setUnfocusOffsetY(Game::HEIGHT / 2);
            player->setOffsetMidY(player->getY() - Game::HEIGHT / 2);
        }
        else if (player->getY() > Game::HEIGHT * 2)
        {
            player->setUnfocusY(true);
            player->setUnfocusOffsetY(Game::HEIGHT * 2);
            player->setOffsetMidY(player->getY() - Game::HEIGHT * 2);
        }
        else player->setUnfocusY(false);
    });

    // EXPERIMENTATION
    player->playerEnableAllMoveset();
}

void Map1::initEnemies(SDL_Renderer *renderer)
{
    EnemyVec.push_back(new Slime(5, 2.5, 1, 20, 1));
    // EnemyVec.push_back(new Slime(26, 3.5, 24.5, 29.5, 1));
    // EnemyVec.push_back(new Slime(45, 4.5, 40, 60, 1));

    for (Enemy *enemy : EnemyVec)
        enemy->initEnemy(renderer);
}

void Map1::updateMapExclusive(SDL_Renderer *renderer, Player *player, Input *input)
{
    // ====================== UPDATE PLAYER ============================

    // Standard update
    player->playerUpdate(renderer, this, input);

    // Some variable
    float player_x = player->getX();
    float player_y = player->getY();

    // Fall off the fucking map lmao
    if (player_y < 0)
    {
        player->setVelY(10);
        // Minus health function down here
        //           (- v -)
    }

    // Checkpoint
    if (player_x > 102 * 64)
    {
        checkpoint_x = 101;
        checkpoint_y = 6;
    }

    // Misc
    if (player_x > 14 * 64) player->setCanJump(true);
    if (player_x > 76 * 64) player->setCanCrawl(true);

    // ====================== UPDATE ENEMIES ===========================
    for (Enemy *enemy : EnemyVec)
        enemy->updateEnemy(player, this);

    // Erase Dead Enemy
    EnemyVec.erase(std::remove_if(EnemyVec.begin(), EnemyVec.end(),
    [](Enemy* enemy) {
        // The other condition is to ensure enemy play dead animation
        return enemy->getDead() &&
        enemy->getSprIndex() == enemy->getSprIndexMax() - 1;
    }), EnemyVec.end());

    // ====================== UPDATE PROJECTILE ========================
    for (Projectile *projectile : ProjectileVec)
        projectile->updateProjectile(renderer, player, this);

    // Erase Dead Bullet
    ProjectileVec.erase(std::remove_if(ProjectileVec.begin(), ProjectileVec.end(),
    [](Projectile* projectile) {
        return projectile->getBulletDead();
    }), ProjectileVec.end());

    // std::cout << EnemyVec.size() << " " << ProjectileVec.size() << "\n";

    // ====================== UPDATE SPECIFIC ==========================

    // Moving block
    BlockVec[19]->setVelX(0);
    if ((BlockVec[19]->getStepOn()) && BlockVec[19]->getX() < 115 * 64)
        BlockVec[19]->setVelX(1);
    if (!BlockVec[19]->getStepOn() && BlockVec[19]->getX() > 104 * 64)
        BlockVec[19]->setVelX(-1);

    // Background
    for (float i = 0; i < BackgroundVec.size(); i+=2)
    {
        BackgroundVec[i]->setX(Game::WIDTH / 2 - int((player_x - Game::WIDTH / 2) * (.1 - i/200)) % Game::WIDTH);
        BackgroundVec[i+1]->setX(Game::WIDTH * 1.5 - int((player_x - Game::WIDTH / 2) * (.1 - i/200)) % Game::WIDTH);

        if (i > 0)
        {
            BackgroundVec[i]->setY(int((player->getY() - Game::HEIGHT / 2) * i/200) + Game::HEIGHT / 2);
            BackgroundVec[i+1]->setY(int((player->getY() - Game::HEIGHT / 2) * i/200) + Game::HEIGHT / 2);
        }
    }
}