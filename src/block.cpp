#include <map.h>

// Destructor
Block::~Block()
{
    for (SDLTexture1D btx1D : block_textures)
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
    block_indexs(b_index), type(t)
{}

// ====================== PRETTY FUCKING ADVANCED ===========================

void Block::blockEngine(string1D sPath, int2D bIndex)
{
    // Just for block editor and stuff
    highlight_texture = loadTexture("res/BoxTile.png");

    // Type 6 block (Texturing and Decoration)
    // can be render outside of camera border
    setCamDepend(type != 6);

    block_paths = sPath;
    // Already Predefined Block Index
    if (block_indexs.size())
    {
        setWidth(block_indexs[0].size() * grid);
        setHeight(block_indexs.size() * grid);
        setX((getX() + getWidth() / 2));
        setY((getY() + getHeight() / 2));
    }
    else
    {
        block_indexs.resize(getGridHeight(1));

        for (int i = 0; i < getGridHeight(1); i++)
        for (int j = 0; j < getGridWidth(1); j++)
            block_indexs[i].push_back(bIndex[i][j]);
    }

    // Some how this mf is still important lmao
    setHitWidth(getWidth());
    setHitHeight(getHeight());

    // Init Texture
    block_textures.resize(getGridHeight(1));
    for (int i = 0; i < getGridHeight(1); i++)
            for (int j = 0; j < getGridWidth(1); j++)
                block_textures[i].push_back(NULL);

    refreshTexture();
}

void Block::setType(short t) { type = t; }
void Block::setSeeAlpha(int alpha) { seeAlpha = alpha; }
void Block::setStepOn(bool step) { isStepOn = step; }
void Block::setHugged(short hug) { isHugged = hug; }

short Block::getType() { return type; }
bool Block::isType(short t) { return type == t; }
int Block::getSeeAlpha() { return seeAlpha; }
bool Block::getStepOn() { return isStepOn; }
short Block::getHugged() { return isHugged; }
bool Block::getCanHug() { return can_hug; }

BlockGrid Block::getGrid()
{   
    return {getGridLX(), getGridBY(),
            int(getBlockIndexs()[0].size()),
            int(getBlockIndexs().size()),
            getBlockIndexs() };
}

SDLTexture2D Block::getBlockTextures() { return block_textures; }
int2D Block::getBlockIndexs() { return block_indexs; }

// Block Highlighter
bool Block::getHighlight() { return highlight; }
void Block::setHighlight(short hl)
{ highlight = (!hl) ? false : (hl == 1) ? true : (!highlight); }

void Block::blockSeethrough(Map *map, bool yes)
{
    if (seeAlpha > 0 && yes) seeAlpha -= 5;
    else if (seeAlpha < 255) seeAlpha += 5;
}

void Block::blockCollision(Map *map, Player *player, PlayerState &pState)
{
    if (Camera::objectIgnore(player, this, 1))
        return;

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

    isHugged = false;
    isStepOn = false;

    player;

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

        setStepOn(true);

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
            isHugged = -1;
        }
        else
        {
            player->setX(getX() - 3 -
                (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
            );
            if (player->a_dash.frame || player->g_dash.frame)
            {
                map->appendParticle(new ParticleEffect(
                    Object2D::loadTexture(
                        "res/ParticleSheet/NakuEffect/WallBangRight.png"),
                    player->getX(), player->getY(), 128, 128,
                    64, 64, 8, 4, 0
                ));

                if (player->g_dash.frame)
                    player->draw_prop.right = 0;
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
            isHugged = 1;
        }
        else
        {
            player->setX(getX() + 3 +
                (player->move.crawl ? hit_dist_x_crawl : hit_dist_x)
            );
            if (player->a_dash.frame || player->g_dash.frame)
            {
                map->appendParticle(new ParticleEffect(
                    Object2D::loadTexture(
                        "res/ParticleSheet/NakuEffect/WallBangLeft.png"),
                    player->getX(), player->getY(), 128, 128,
                    64, 64, 8, 4, 0
                ));

                if (player->g_dash.frame)
                    player->draw_prop.right = 1;
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
                Object2D::loadTexture(
                    "res/ParticleSheet/NakuEffect/WallBangDown.png"),
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

        isStepOn = true;

        pState.on_ground = true;
        if (type == 1) pState.on_ice = true;
        pState.hug_wall = 0;
        return;
    }
}

void Block::draw(Player *player)
{
    if (getAccelX() || getAccelY() ||
        getVelX() || getVelY())
    {
        isMoving = true;
        objectStandardMovement();
    }
    else
        isMoving = false;

    if (Camera::objectIgnore(player, this))
        return;

    // Draw
    for (int i = 0; i < block_textures.size(); i++)
    for (int j = 0; j < block_textures[i].size(); j++)
    {
        // If a grid x grid texture is out of bound
        // Ignore the rendering process
        int colli_x = abs(distX(player, this) - player->camera.offset_mid_x + getWidth() / 2 - j*grid);
        int colli_y = abs(distX(player, this) - player->camera.offset_mid_y - getHeight() / 2 + i*grid);
        if (block_indexs[i][j] == -1 ||
            colli_x - grid / 2 > CFG->WIDTH ||
            colli_y - grid / 2 > CFG->HEIGHT)
            continue;

        if (type == -1)
            SDL_SetTextureAlphaMod(block_textures[i][j], seeAlpha);

        SDL_Rect desRect = {Camera::objectDrawX(player, this) + j*grid,
                            Camera::objectDrawY(player, this) + i*grid,
                            grid, grid};

        SDL_RenderCopy(CFG->RENDERER, block_textures[i][j], NULL, &desRect);        
    }

    // Highlighter
    if (highlight)
    {
        int drawX = Camera::objectDrawX(player, this);
        int drawY = Camera::objectDrawY(player, this);

        SDL_SetRenderDrawColor(CFG->RENDERER, 0, 255, 0, 150);
        SDL_Rect highlightRect = {drawX, drawY, getWidth(), getHeight()};
        SDL_RenderCopy(CFG->RENDERER, highlight_texture, NULL, &highlightRect);
    }
}

// ============================ BLOCK MANIPULATION =============================

void Block::setBlockIndexs(int2D newIndex)
{
    block_indexs = newIndex;
    refreshTexture();
}

void Block::refreshTexture(string1D sPath)
{
    string1D bPath = sPath.size() ? sPath : block_paths;

    block_textures.resize(getGridHeight(1));
    for (int i = 0; i < getGridHeight(1); i++)
    for (int j = 0; j < getGridWidth(1); j++)
    { 
        if (block_indexs[i][j] >= bPath.size() ||
            block_indexs[i][j] < 0)
        {
            block_indexs[i][j] = -1;
            block_textures[i][j] = NULL;
        }
        else
        {
            // Delete old texture memory
            SDL_DestroyTexture(block_textures[i][j]);
            // Add new texture
            block_textures[i][j] = loadTexture(bPath[block_indexs[i][j]]);
        }
    }
}

void Block::tileEdit(string1D sPath, int1D tIndex, int bIndex)
{
    block_textures[tIndex[1]][tIndex[0]] = loadTexture( sPath[bIndex]);
    block_indexs[tIndex[1]][tIndex[0]] = bIndex;
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
            block_indexs[offY + r][offX + c] = overlap[r][c];

    refreshTexture();
}