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
    Object2D((main_val[1] + main_val[3]/2) * 64,
             (main_val[2] + main_val[4]/2) * 64,
             main_val[3] * 64, main_val[4] * 64,
             main_val[3] * 64, main_val[4] * 64),
    type(main_val[0])
{}
// Simple Block
Block::Block(float X, float Y, float w, float h, short t, short gr) :
    Object2D((X + w/2) * gr, (Y + h/2) * gr,
            w * gr, h * gr, w * gr, h * gr),
    type(t), grid(gr)
{}
// Simple Block (but with predefined index)
Block::Block(float X, float Y, short t, int2D b_index) :
    Object2D(X * 64, Y * 64, 0, 0), // PLACEHOLDER VALUE
    indexs(b_index), type(t)
{}

// ====================== PRETTY FUCKING ADVANCED ===========================

void Block::blockEngine(string1D sPath, int2D bIndex)
{
    // Just for block editor and stuff
    highlight_texture = CFG->loadTexture("assets/BoxTile.png");

    // Type 6 block (Texturing and Decoration)
    // can be render outside of camera border
    setCamDepend(type != 6);

    paths = sPath;
    // Already Predefined Block Index
    if (indexs.size())
    {
        setWidth(indexs[0].size() * grid);
        setHeight(indexs.size() * grid);
        setX((getX() + getWidth() / 2));
        setY((getY() + getHeight() / 2));
    }
    else
    {
        indexs.resize(getGridHeight(1));

        for (int i = 0; i < getGridHeight(1); i++)
        for (int j = 0; j < getGridWidth(1); j++)
            indexs[i].push_back(bIndex[i][j]);
    }

    setHitWidth(getWidth());
    setHitHeight(getHeight());

    // Init Texture and Rect
    rects.resize(getGridHeight(1));
    noRenders.resize(getGridHeight(1));
    textures.resize(getGridHeight(1));

    for (int i = 0; i < getGridHeight(1); i++)
    for (int j = 0; j < getGridWidth(1); j++)
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
        getGridLX(), getGridBY(),
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

    drawProp(player);
}

void Block::blockCollision(Map *map, Player *player, PlayerState &pState)
{
    if (objectIgnore(player, this)) return;

    // Player Value
    int px = player->getX();
    int py = player->getY();
    int p_vel_y = player->getVelY();
    int p_hit_x = player->move.hitX();
    int p_hit_y = player->move.hitY();
    int p_hit_w = player->getHitWidth();
    int p_hit_h = player->getHitHeight();

    // Collision Value
    int colli_x = abs(p_hit_x - getX());
    int colli_y = abs(p_hit_y - getY());
    int colli_y_stand = abs(py - getY());

    int hit_dist_x = (p_hit_w + getWidth()) / 2;
    int hit_dist_y = (p_hit_h + getHeight()) / 2;
    int hit_dist_x_crawl = (78 + getWidth()) / 2;
    int hit_dist_y_stand = (80 + getHeight()) / 2;

    state.hugged = false;
    state.stepOn = false;

    // Bridge block has different hitbox detection
    if (type == 3 && !pState.on_ground &&
        p_vel_y <= 0 &&
        p_hit_y > getY() + hit_dist_y + p_vel_y - 2 &&
        colli_y < hit_dist_y &&
        (p_hit_x < getX() + hit_dist_x) &&
        (p_hit_x > getX() - hit_dist_x))
    {
        if (getVelX())
            player->setX(player->getX() + getVelX());
        if (getVelY())
            player->setY(player->getY() + getVelY());

        if (!player->move.crawl && !player->g_dash.frame)
            player->setY(getY() + (getHeight() + p_hit_h) / 2 - 1);

        state.stepOn = 1;

        pState.on_ground = 1;
        pState.hug_wall = 0;
    }

    // Not Solid or Not Ice => No standard hitbox detection 
    if (type != 0 && type != 1) return;

    // Ceiling min
    if (colli_x < hit_dist_x - 10 && py < getY())
    {
        player->jump.ceiling_min = std::min(
                player->jump.ceiling_min,
                int(getY() - py - hit_dist_y)
        );
    }

    // Hit Left wall
    if (p_hit_x < getX() && colli_x < hit_dist_x &&
        p_hit_y < getY() + hit_dist_y - 10 &&
        p_hit_y > getY() - hit_dist_y + 10)
    {
        if (player->moveset.hug_wall &&
            !player->state.on_ground &&
            !player->a_dash.frame &&
            type == 0)
        {
            pState.hug_wall = -1;

            player->setVelX(0);
            player->setX(getX() - hit_dist_x + 3);
            state.hugged = -1;
        }
        else
        {
            player->setX(getX() - 3 -
                (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
            );
            if (player->a_dash.frame || player->g_dash.frame)
            {
                map->appendParticle(new ParticleEffect(
                    CFG->loadTexture(
                        "assets/ParticleSheet/NakuEffect/WallBangRight.png"),
                    player->getX(), player->getY(), 128, 128,
                    64, 64, 8, 4, 0
                ));

                if (player->g_dash.frame)
                    player->sprite.right = 0;
                if (player->a_dash.frame)
                    player->a_dash.frame = 0;
            }
        }

        return;
    }

    // Hit Right wall
    if (p_hit_x > getX() && colli_x < hit_dist_x &&
        p_hit_y < getY() + hit_dist_y - 10 &&
        p_hit_y > getY() - hit_dist_y + 10)
    {
        if (player->moveset.hug_wall &&
            !player->state.on_ground &&
            !player->a_dash.frame &&
            type == 0)
        {
            pState.hug_wall = 1;

            player->setVelX(0);
            player->setX(getX() + hit_dist_x - 3);
            state.hugged = 1;
        }
        else
        {
            player->setX(getX() + 3 +
                (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
            );
            if (player->a_dash.frame || player->g_dash.frame)
            {
                map->appendParticle(new ParticleEffect(
                    CFG->loadTexture(
                        "assets/ParticleSheet/NakuEffect/WallBangLeft.png"),
                    player->getX(), player->getY(), 128, 128,
                    64, 64, 8, 4, 0
                ));

                if (player->g_dash.frame)
                    player->sprite.right = 1;
                if (player->a_dash.frame)
                    player->a_dash.frame = 0;
            }
        }

        return;
    }

    // Ceiling logic
    if ((p_hit_x < getX() + hit_dist_x) &&
        (p_hit_x > getX() - hit_dist_x))
    {
        if (p_vel_y > 0 &&
            p_hit_y < getY() + p_vel_y + 4 &&
            colli_y < hit_dist_y)
        {
            map->appendParticle(new ParticleEffect(
                CFG->loadTexture(
                    "assets/ParticleSheet/NakuEffect/WallBangDown.png"),
                player->getX(), player->getY(), 70, 70,
                64, 64, 8, 4, 0
            ));

            player->jump.knockout = 50;
            player->setY(getY() - getHeight() / 2 - 40 - p_vel_y);
            player->setVelY(-p_vel_y * .1);
            return;
        }

        if (player->state.on_ground &&
            player->getY() < getY() &&
            colli_y_stand < hit_dist_y_stand)
            pState.crawl_lock = 1;
    }

    // Stand on block
    if (!pState.on_ground &&
        p_hit_y > getY() &&
        colli_y < hit_dist_y &&
        (p_hit_x < getX() + hit_dist_x) &&
        (p_hit_x > getX() - hit_dist_x))
    {
        if (getVelX())
            player->setX(player->getX() + getVelX());
        if (getVelY())
            player->setY(player->getY() + getVelY());

        if (!player->move.crawl && !player->g_dash.frame)
            player->setY(getY() + (getHeight() + p_hit_h) / 2 - 1);

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
    SDL_Rect highlightRect = {drawX, drawY, getWidth(), getHeight()};
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

    rects.resize(getGridHeight(1));
    textures.resize(getGridHeight(1));
    for (int i = 0; i < getGridHeight(1); i++)
    for (int j = 0; j < getGridWidth(1); j++)
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
    if (olapWidth > getGridWidth() || 
        olapWidth > getGridHeight()) return;

    for (int r = 0; r < olapHeight; r++)
        for (int c = 0; c < olapWidth; c++)
            indexs[offY + r][offX + c] = overlap[r][c];

    refreshTexture();
}