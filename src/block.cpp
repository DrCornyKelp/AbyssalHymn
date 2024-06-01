#include <map.h>

// Destructor
Block::~Block()
{
    for (SDLTexture1D btx1D : textures)
    for (SDL_Texture *btx : btx1D)
        SDL_DestroyTexture(btx);
}
// Default
Block::Block() : isValid(0) {}
// Pull This Shit Out From The CSV Lmao
Block::Block(float1D main_val) :
    Object2D({
        (main_val[1] + main_val[3]/2) * 64,
        (main_val[2] + main_val[4]/2) * 64,
        int(main_val[3] * 64), int(main_val[4]) * 64,
        int(main_val[3] * 64), int(main_val[4]) * 64
    }),
    type(main_val[0])
{}
// Simple Block (but with predefined index)
Block::Block(float X, float Y, short t, int2D b_index) :
    Object2D({X * 64, Y * 64}), // PLACEHOLDER VALUE
    indexs(b_index), type(t)
{}

// ====================== PRETTY FUCKING ADVANCED ===========================

void Block::blockEngine(string1D sPath, int2D bIndex)
{
    // Just for block editor and stuff
    highlight_texture = CFG->loadTexture("assets/BoxTile.png");

    // Type 6 block (Texturing and Decoration)
    // can be render outside of camera border
    cam_depend = type != 6;

    paths = sPath;
    // Already Predefined Block Index
    if (indexs.size())
    {
        hitbox.w = indexs[0].size() * grid;
        hitbox.h = indexs.size() * grid;
        hitbox.x += hitbox.w / 2;
        hitbox.y += hitbox.h / 2;
    }
    else
    {
        indexs.resize(hitbox.gridH());

        for (int i = 0; i < hitbox.gridH(); i++)
        for (int j = 0; j < hitbox.gridW(); j++)
            indexs[i].push_back(bIndex[i][j]);
    }

    hitbox.hw = hitbox.w;
    hitbox.hh = hitbox.h;

    // Init Texture and Rect
    rects.resize(hitbox.gridH());
    noRenders.resize(hitbox.gridH());
    textures.resize(hitbox.gridH());

    for (int i = 0; i < hitbox.gridH(); i++)
    for (int j = 0; j < hitbox.gridW(); j++)
    {
        textures[i].push_back(NULL);
        rects[i].push_back({0, 0, 0, 0});
        noRenders[i].push_back(0);
    }

    refreshTexture();
}

BlockGrid Block::getGrid()
{
    return {
        hitbox.gridLX(),
        hitbox.gridBY(),
        int(indexs[0].size()),
        int(indexs.size()),
        indexs 
    };
}

void Block::setHighlight(short hl)
{ highlight = (!hl) ? false : (hl == 1) ? true : (!highlight); }

void Block::blockSeethrough(Player *player, bool yes)
{
    if (seeAlpha > 0 && yes) seeAlpha -= 5;
    else if (seeAlpha < 255) seeAlpha += 5;
}

void Block::blockCollision(Map *map, Player *player, PlayerState &pState)
{
    if (objectIgnore(player, this)) return;

    // Player Value
    int px = player->hitbox.x;
    int py = player->hitbox.y;
    float p_vel_y = player->vel.y;
    float p_hit_x = player->move.hitX();
    float p_hit_y = player->move.hitY();
    int p_hit_w = player->hitbox.hw;
    int p_hit_h = player->hitbox.hh;

    // Collision Value
    int colli_x = abs(p_hit_x - hitbox.x);
    int colli_y = abs(p_hit_y - hitbox.y);
    int colli_y_stand = abs(py - hitbox.y);

    int hit_dist_x = (p_hit_w + hitbox.w) / 2;
    int hit_dist_y = (p_hit_h + hitbox.h) / 2;
    int hit_dist_x_crawl = (78 + hitbox.w) / 2;
    int hit_dist_y_stand = (80 + hitbox.h) / 2;

    state.hugged = false;
    state.stepOn = false;

    // Bridge block has different hitbox detection
    if (type == 3 && !pState.on_ground &&
        p_vel_y <= 0 &&
        p_hit_y > hitbox.y + hit_dist_y + p_vel_y - 2 &&
        colli_y < hit_dist_y &&
        (p_hit_x < hitbox.x + hit_dist_x) &&
        (p_hit_x > hitbox.x - hit_dist_x))
    {
        if (vel.x) player->hitbox.x += vel.x;
        if (vel.y) player->hitbox.y += vel.y;

        if (!player->move.crawl && !player->g_dash.frame)
            player->hitbox.y = hitbox.y + (hitbox.h + p_hit_h) / 2 - 1;

        state.stepOn = 1;

        pState.on_ground = 1;
        pState.hug_wall = 0;
    }

    // Not Solid or Not Ice => No standard hitbox detection 
    if (type != 0 && type != 1) return;

    // if (p_hit_x < hitbox.x + hit_dist_x - 1 &&
    //     p_hit_x > hitbox.x - hit_dist_x + 1)
    // {
    //     if (player->collide.predictU(this))
    //     {
    //         player->hitbox.y = hitbox.y - hit_dist_y - 1;
    //         player->vel.y = 0;
    //         player->collide.lockU = 1;
    //     }
    //     if (player->collide.predictD(this))
    //     {
    //         state.stepOn = 1;

    //         pState.on_ground = true;
    //         if (type == 1) pState.on_ice = true;
    //         pState.hug_wall = 0;

    //         player->vel.y = 0;
    //         player->hitbox.y = hitbox.y + hit_dist_y + 1;
    //         player->collide.lockD = 1;
    //     }
    // }

    // if (p_hit_y < hitbox.y + hit_dist_y - 1 &&
    //     p_hit_y > hitbox.y - hit_dist_y + 1)
    // {
    //     if (player->collide.predictL(this))
    //     {
    //         player->vel.x = 0;
    //         player->hitbox.x = hitbox.x + hit_dist_x;
    //         player->collide.lockL = 1;
    //     }
    //     if (player->collide.predictR(this))
    //     {
    //         std::cout << "predict \n";
    //         player->vel.x = 0;
    //         player->hitbox.x = hitbox.x - hit_dist_x;
    //         player->collide.lockR = 1;
    //     }
    // }
    
    // Hit Wall
    if (p_hit_y < hitbox.y + hit_dist_y - 10 &&
        p_hit_y > hitbox.y - hit_dist_y + 10)
    {
        // Going Right Then Hitting Left wall
        if (player->collide.predictR(this))
        {
            player->vel.x = 0;

            if (player->moveset.hug_wall &&
                !player->state.on_ground &&
                !player->a_dash.frame &&
                type == 0)
            {
                pState.hug_wall = -1;
                state.hugged = -1;

                player->hitbox.x = hitbox.x - hit_dist_x + 1;
            }
            else
            {
                player->collide.lockR = 1;
                player->hitbox.x = (hitbox.x -
                    (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
                );

                if (player->a_dash.frame || player->g_dash.frame)
                {
                    map->appendParticle(new ParticleEffect(
                        CFG->loadTexture(
                            "assets/ParticleSheet/NakuEffect/WallBangRight.png"),
                        player->hitbox.x, player->hitbox.y, 128, 128,
                        64, 64, 8, 4, 0
                    ));

                    if (player->g_dash.frame)
                        player->psprite.right = 0;
                    if (player->a_dash.frame)
                        player->a_dash.frame = 0;
                }
            }

            return;
        }

        // Going Left Then Hitting Right wall
        if (player->collide.predictL(this))
        {
            player->vel.x = 0;

            if (player->moveset.hug_wall &&
                !player->state.on_ground &&
                !player->a_dash.frame &&
                type == 0)
            {
                pState.hug_wall = 1;
                state.hugged = 1;
                player->hitbox.x = hitbox.x + hit_dist_x - 1;
            }
            else
            {
                player->collide.lockL = 1;
                player->hitbox.x = (hitbox.x +
                    (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
                );

                if (player->a_dash.frame || player->g_dash.frame)
                {
                    map->appendParticle(new ParticleEffect(
                        CFG->loadTexture(
                            "assets/ParticleSheet/NakuEffect/WallBangLeft.png"),
                        player->hitbox.x, player->hitbox.y, 128, 128,
                        64, 64, 8, 4, 0
                    ));

                    if (player->g_dash.frame)
                        player->psprite.right = 1;
                    if (player->a_dash.frame)
                        player->a_dash.frame = 0;
                }
            }

            return;
        }
    }

    // Ceiling logic

    if ((p_hit_x >= hitbox.x + hit_dist_x - 1) ||
        (p_hit_x <= hitbox.x - hit_dist_x + 1))
        return;

    if (p_vel_y > 0 &&
        p_hit_y < hitbox.y + p_vel_y + 4 &&
        colli_y < hit_dist_y)
    {
        map->appendParticle(new ParticleEffect(
            CFG->loadTexture(
                "assets/ParticleSheet/NakuEffect/WallBangDown.png"),
            player->hitbox.x, player->hitbox.y, 70, 70,
            64, 64, 8, 4, 0
        ));

        player->jump.knockout = 50;
        player->hitbox.y = hitbox.y - hit_dist_y - p_vel_y;
        player->vel.y = -p_vel_y * .1;
        return;
    }

    // Stuck Under Ceiling
    if (player->state.on_ground &&
        player->hitbox.y < hitbox.y &&
        colli_y_stand < hit_dist_y_stand)
        pState.crawl_lock = 1;

    // Stand on block
    if (!pState.on_ground &&
        p_hit_y > hitbox.y &&
        colli_y < hit_dist_y)
    {
        if (vel.x) player->hitbox.x += vel.x;
        if (vel.y) player->hitbox.y += vel.y;

        if (!player->move.crawl && !player->g_dash.frame)
            player->hitbox.y = hitbox.y + (hitbox.h + p_hit_h) / 2 - 1;

        state.stepOn = 1;

        pState.on_ground = true;
        if (type == 1) pState.on_ice = true;
        pState.hug_wall = 0;
        return;
    }
}

// Draw Block

void Block::drawProp(Player *player)
{
    int drawX = Camera::objectDrawX(player, this);
    int drawY = Camera::objectDrawY(player, this);

    // Draw
    for (int i = 0; i < indexs.size(); i++)
    for (int j = 0; j < indexs[i].size(); j++)
    {
        rects[i][j] = {drawX + j*grid, drawY + i*grid, grid, grid};

        noRenders[i][j] =
            (indexs[i][j] == -1) ||
            Camera::outOfBound(rects[i][j]);

        if (type == -1)
            SDL_SetTextureAlphaMod(textures[i][j], seeAlpha);
    }
}

void Block::draw(Player *player)
{
    for (int i = 0; i < indexs.size(); i++)
    for (int j = 0; j < indexs[i].size(); j++)
        if (!noRenders[i][j]) SDL_RenderCopy(
            CFG->RENDERER, textures[i][j], NULL, &rects[i][j]
        );
}

void Block::drawHighlight(Player *player)
{
    int drawX = Camera::objectDrawX(player, this);
    int drawY = Camera::objectDrawY(player, this);
    SDL_SetRenderDrawColor(CFG->RENDERER, 0, 255, 0, 150);
    SDL_Rect highlightRect = {drawX, drawY, hitbox.w, hitbox.h};
    SDL_RenderCopy(CFG->RENDERER, highlight_texture, NULL, &highlightRect);
}

// ============================ BLOCK MANIPULATION =============================

void Block::setBlockIndexs(int2D newIndex)
{
    indexs = newIndex;
    refreshTexture();
}

void Block::refreshTexture(string1D sPath)
{
    string1D bPath = sPath.size() ? sPath : paths;

    rects.resize(hitbox.gridH());
    textures.resize(hitbox.gridH());
    for (int i = 0; i < hitbox.gridH(); i++)
    for (int j = 0; j < hitbox.gridW(); j++)
    { 
        if (indexs[i][j] >= bPath.size() ||
            indexs[i][j] < 0)
        {
            indexs[i][j] = -1;
            textures[i][j] = NULL;
        }
        else
        {
            // Delete old texture memory
            SDL_DestroyTexture(textures[i][j]);
            // Add new texture
            textures[i][j] = CFG->loadTexture(bPath[indexs[i][j]]);
        }
    }
}

void Block::tileEdit(string1D sPath, int1D tIndex, int bIndex)
{
    textures[tIndex[1]][tIndex[0]] = CFG->loadTexture( sPath[bIndex]);
    indexs[tIndex[1]][tIndex[0]] = bIndex;
}

void Block::overlap(int2D overlap, int offX, int offY)
{
    int olapWidth = overlap[0].size();
    int olapHeight = overlap.size();

    // Cant overlap shit if the overlaper is too big
    // (like a blonde with a black coc... nvm)
    if (olapWidth > hitbox.gridW() || 
        olapWidth > hitbox.gridH()) return;

    for (int r = 0; r < olapHeight; r++)
        for (int c = 0; c < olapWidth; c++)
            indexs[offY + r][offX + c] = overlap[r][c];

    refreshTexture();
}