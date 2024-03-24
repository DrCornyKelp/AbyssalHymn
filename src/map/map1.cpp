#include "map/map1.h"

void Map1::initBlocksBack(SDL_Renderer *renderer)
{
    BlockBackVec.push_back(new Block(50, -0.5, 4, 7, 64, true));
    BlockBackVec[BlockBackVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::mergeY({{19}}, BlockTemplate::expandY({{16}}, 6)),
        BlockTemplate::expandX(
            BlockTemplate::mergeY({{18}}, BlockTemplate::expandY({{9}}, 6)), 2
        ),
        BlockTemplate::mergeY({{20}}, BlockTemplate::expandY({{17}}, 6))
    ));

    BlockBackVec.push_back(new Block(82, 0, 17, 5, 64, true));
    BlockBackVec[BlockBackVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        BlockTemplate::mergeX(
            BlockTemplate::expandX({{nb}}, 10),
            BlockTemplate::expandX({{13}}, 7)
        ),
        BlockTemplate::mergeX(
            BlockTemplate::expandX({{13}, {9}, {9}, {9}}, 11),
            BlockTemplate::expandX({{9}, {9}, {9}, {9}}, 11)
        )
    ));
}

void Map1::initBlocks(SDL_Renderer *renderer)
{
    // Boundary
    BlockVec.push_back(new Block(-1, 0, 1, 100));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::expandY({{0}}, 100)
    );
    
    // Starting Ground
    BlockVec.push_back(new Block(0, 0, 20, 2, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {7}},
        BlockTemplate::expandX({{18}, {0}}, 18),
        {{20}, {8}}
    ));

    // Platforms
    BlockVec.push_back(new Block(24, 0, 6, 3, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {7}, {7}},
        BlockTemplate::expandX({{18}, {0}, {0}}, 4),
        {{20}, {8}, {8}}
    ));

    // Bridge
    BlockVec.push_back(new Block(39, 3, 22, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::expandX({{21}}, 22)
    );
    // Bridge railing decoration
    BlockVec.push_back(new Block(39, 4, 22, 1, 64, true));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{25}},
        BlockTemplate::expandX({{24}}, 20),
        {{26}}
    ));

    // Layer previous platform over bridge for drawing consitency
    BlockVec.push_back(new Block(34, 0, 6, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {7}, {7}, {7}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}}, 4),
        {{20}, {8}, {8}, {8}}
    ));

    // See through mechanic
    BlockVec.push_back(new Block(50, 5.5, 4, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY2(
        {{19, 18, 18, 20}},
        BlockTemplate::expandY({{7, 0, 0, 8}}, 2),
        {{2, 1, 1, 3}}
    ));
    BlockVec.push_back(new Block(50, -0.5, 4, 7, 64, true, true));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::expandY({{7}}, 7),
        BlockTemplate::expandX(
            BlockTemplate::expandY({{0}}, 7), 2
        ),
        BlockTemplate::expandY({{8}}, 7)
    ));

    // More random platforms and bridge
    BlockVec.push_back(new Block(70, 3, 7, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::expandX({{21}}, 7)
    );
    BlockVec.push_back(new Block(70, 4, 7, 1, 64, true));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        BlockTemplate::expandX({{24}}, 6),
        {{26}}
    ));

    BlockVec.push_back(new Block(66, -0.5, 5, 7, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::mergeY({{19}}, BlockTemplate::expandY({{7}}, 6)),
        BlockTemplate::expandX(
            BlockTemplate::mergeY({{18}}, BlockTemplate::expandY({{0}}, 6)), 3
        ),
        BlockTemplate::mergeY({{20}}, BlockTemplate::expandY({{8}}, 6))
    ));
    
    BlockVec.push_back(new Block(60, 0, 7, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::mergeY({{19}}, BlockTemplate::expandY({{7}}, 3)),
        BlockTemplate::expandX(
            BlockTemplate::mergeY({{18}}, BlockTemplate::expandY({{0}}, 3)), 5
        ),
        BlockTemplate::expandY({{0}}, 4)
    ));

    BlockVec.push_back(new Block(76, 0, 7, 4, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::mergeY({{19}}, BlockTemplate::expandY({{7}}, 3)),
        BlockTemplate::expandX(
            BlockTemplate::mergeY({{18}}, BlockTemplate::expandY({{0}}, 3)), 5
        ),
        {{20}, {8}, {8}, {0}}
    ));

    BlockVec.push_back(new Block(83, 0, 15, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::expandX({{13}}, 15)
    );

    BlockVec.push_back(new Block(87, 2, 6, 9, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block, {
    {nb, nb, 19, 20, nb, nb},
    {nb, 19,  0,  8, nb, nb},
    {19,  0,  0,  0, 20, nb},
    { 7,  0,  0,  0,  0, 20},
    { 7,  0,  0,  0,  0,  8},
    { 7,  0,  0,  0,  0,  8},
    { 7,  0,  0,  0,  0,  8},
    { 7,  0,  0,  0,  0,  8},
    { 2,  1,  1,  1,  1,  3},
    });

    BlockVec.push_back(new Block(97, -0.5, 1, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{5}, {7}, {7}, {7}, {0}}
    );

    BlockVec.push_back(new Block(83, 0, 15, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX(
        BlockTemplate::expandX({{4}}, 14),
        {{0}}
    ));

    BlockVec.push_back(new Block(98, 0, 5, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        {{19}, {0}, {0}, {0}, {0}},
        BlockTemplate::expandX({{18}, {0}, {0}, {0}, {0}}, 3),
        {{20}, {8}, {8}, {8}, {8}}
    ));

    BlockVec.push_back(new Block(82, 0, 17, 5, 64, true, true));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeY(
        BlockTemplate::mergeX2(
            BlockTemplate::expandX({{nb}}, 10),
            BlockTemplate::expandX({{0}}, 1),
            BlockTemplate::expandX({{18}}, 6)
        ),
        BlockTemplate::mergeX(
            BlockTemplate::expandX({{18}, {0}, {0}, {0}}, 5),
            BlockTemplate::expandX({{0}, {0}, {0}, {0}}, 12)
        )
    ));

    // 19
    BlockVec.push_back(new Block(103, 4, 2, 1, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    {{19, 20}});

    // 20
    BlockVec.push_back(new Block(116, 0, 50, 5, 64));
    BlockVec[BlockVec.size() - 1]->blockEngine(renderer, nature_block,
    BlockTemplate::mergeX2(
        BlockTemplate::mergeY({{19}}, BlockTemplate::expandY({{7}}, 4)),
        BlockTemplate::expandX(
            BlockTemplate::mergeY({{18}}, BlockTemplate::expandY({{0}}, 4)), 48
        ),
        BlockTemplate::mergeY({{20}}, BlockTemplate::expandY({{8}}, 4))
    ));

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
    DecorBackVec.push_back(new Decoration("res/Decoration/House1.png", 0, 2, 15, 11.25));

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

    // Camera Focus
    player->setFocusXCondition([](int x, int y) {
        if (x > Game::WIDTH / 2) FocusReturn(Game::WIDTH / 2, true);
        FocusReturn(0, false);
    });
    player->setFocusYCondition([](int x, int y) {
        if (y > Game::HEIGHT / 2) FocusReturn(Game::HEIGHT / 2, true);
        FocusReturn(0, false);
    });

    // EXPERIMENTATION
    player->playerEnableAllMoveset();
}

void Map1::initEnemies(SDL_Renderer *renderer)
{
    EnemyVec.push_back(new Slime(5, 2.5, 1, 19.5, 1));
    EnemyVec.push_back(new Slime(26, 3.5, 24.5, 29.5, 1));
    EnemyVec.push_back(new Slime(45, 4.5, 40, 60, 1));

    for (Enemy *enemy : EnemyVec)
        enemy->initEnemy(renderer);
}

void Map1::updateMapExclusive(SDL_Renderer *renderer, Player *player)
{
    // EXPERIMENTATION
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (time > time_max) dayForward = -1;
    if (time < 0) dayForward = 1;
    time += dayForward;

    // ====================== UPDATE PLAYER ============================

    // Standard update
    player->playerUpdate(renderer, this);

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
        enemy->getSprIndex() == enemy->getSprIndexMax();
    }), EnemyVec.end());

    // ====================== UPDATE PROJECTILE ========================
    for (Projectile *projectile : ProjectileVec)
    {
        projectile->updateProjectile(renderer, player, this);
    }

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
        if (player->getFocusX())
        {
            BackgroundVec[i]->setX(Game::WIDTH / 2 - int((player_x - Game::WIDTH / 2) * (.1 - i/200)) % Game::WIDTH);
            BackgroundVec[i+1]->setX(Game::WIDTH * 1.5 - int((player_x - Game::WIDTH / 2) * (.1 - i/200)) % Game::WIDTH);
        }
        else
        {
            BackgroundVec[i]->setX(Game::WIDTH / 2);
            BackgroundVec[i+1]->setX(Game::WIDTH / 2);
        }

        if (i > 0)
        {
            if (player->getFocusY())
            {
                BackgroundVec[i]->setY(int((player->getY() - Game::HEIGHT / 2) * i/200) + Game::HEIGHT / 2);
                BackgroundVec[i+1]->setY(int((player->getY() - Game::HEIGHT / 2) * i/200) + Game::HEIGHT / 2);
            }
            else
            {
                BackgroundVec[i]->setY(Game::HEIGHT / 2);
                BackgroundVec[i+1]->setY(Game::HEIGHT / 2);
            }
        }
    }
}