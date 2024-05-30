#include <map.h>

Decoration::~Decoration() {
    // Single Texture
    SDL_DestroyTexture(decor_texture);
    // Folder Textures
    for (SDL_Texture *txt : decor_textures)
        SDL_DestroyTexture(txt);
}

Decoration::Decoration(DecorObject decor_obj) :
    Object2D(decor_obj.box, decor_obj.sprite),
    type(decor_obj.type), decor_path(decor_obj.path),
    alpha(decor_obj.alpha)
{}

// Background
Decoration::Decoration( string0D dPath,
                        float whRatio, float scaleVelX,
                        float scaleVelY, float velX, bool bg) :
    type(0), decor_path(dPath), w_h_ratio(whRatio),
    scale_vel_x(scaleVelX), scale_vel_y(scaleVelY)
{ vel.x = velX; }

// Getter/setter
float Decoration::getAddX() { return add_x; }
float Decoration::getSclVelX() { return scale_vel_x; }
float Decoration::getSclVelY() { return scale_vel_y; }

void Decoration::initDecoration()
{
    if (type == 2)
        decor_textures = CFG->loadTextures(decor_path, sprite.sim);
    else
    {
        decor_texture = CFG->loadTexture(decor_path);
        setAlpha(alpha);
    }
}

void Decoration::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(decor_texture, a);
}

void Decoration::drawProp(Player *player)
{
    setSprite();

    desRect = {
        Camera::objectDrawX(player, this),
        Camera::objectDrawY(player, this),
        hitbox.w, hitbox.h
    };

    srcRect = {
        sprite.si * sprite.sw, 0,
        sprite.sw, sprite.sh
    };
}

void Decoration::draw(Player *player)
{
    if (Camera::outOfBound(desRect) ||
        Camera::outOfCam(player, this))
        return;

    switch (type)
    {
        case 0:
            SDL_RenderCopy(CFG->RENDERER, decor_texture, NULL, &desRect);
            break;

        case 1:
            SDL_RenderCopy(CFG->RENDERER, decor_texture, &srcRect, &desRect);
            break;

        case 2:
            SDL_RenderCopy(CFG->RENDERER, decor_textures[sprite.si], NULL, &desRect);
            break;
    }
}

void Decoration::updateBackground(Player *player, bool left_prlx)
{
    // Resize
    if (CFG->WIDTH > CFG->HEIGHT * w_h_ratio)
    {
        hitbox.w = CFG->WIDTH;
        hitbox.h = CFG->WIDTH / w_h_ratio;
    }
    else
    {
        hitbox.w = CFG->HEIGHT * w_h_ratio;
        hitbox.h = CFG->HEIGHT;
    }

    int bg_shift = left_prlx ? hitbox.w/2 : hitbox.w*3/2;

    // ==================== Parallax X ====================
    // Automatic scroll
    if (vel.x)
    {
        add_x += vel.x;
        if (add_x > hitbox.w) add_x = 0;
        if (add_x < 0) add_x = hitbox.w;
        hitbox.x = bg_shift - add_x;
    }
    // Parallax stop (player unfocus)
    else if (player->camera.unfocus.x)
        hitbox.x = (bg_shift - int(
            player->camera.unfocus_offset.x * scale_vel_x
        ) % hitbox.w);
    // Parallax moving (player focus)
    else
        hitbox.x = (bg_shift - int(
            (player->hitbox.x - player->camera.offset.x) * scale_vel_x
        ) % hitbox.w);

    // ==================== Parallax Y ====================
    // Parallax stop (player unfocus)
    if (player->camera.unfocus.y)
        hitbox.y = (CFG->HEIGHT/2 + int(
            player->camera.unfocus_offset.y * scale_vel_y
        ));
    // Parallax moving (player focus)
    else
        hitbox.y = (CFG->HEIGHT/2 + int(
            (player->hitbox.y - player->camera.offset.y) * scale_vel_y
        ));

    // Update Rect
    desRect = {
        int(hitbox.x - hitbox.w / 2),
        int(hitbox.y - hitbox.h / 2),
        hitbox.w, hitbox.h
    };
}

void Decoration::drawBackground()
{
    SDL_RenderCopy(CFG->RENDERER, decor_texture, NULL, &desRect);
}

// ============================ FILE MANIPULATION ===================================

Decoration *Decoration::codeToDecorInfo(string0D str)
{
    std::stringstream ss(str);
    char cm = ',';

    string0D decor_type; // 0: static, 1: sprite sheet, 2: sprite folder
    string0D path;
    float x, y;
    int w, h;
    int sw = 0, sh = 0,
        sim = 0, sfm = 0;
    int alpha = 255;

    std::getline(ss, decor_type, ',');
    short dtype = std::stoi(decor_type);

    std::getline(ss, path, ',');
    ss  >>  x >> cm >> y >> cm >>
            w >> cm >> h >> cm;

    if (dtype == 1)
        ss >> sw >> cm >> sh >> cm >> sim >> cm >> sfm >> cm;
    if (dtype == 2)
        ss >> sim >> cm >> sfm >> cm;

    ss >> alpha;

    DecorObject decor_obj = {
        dtype, path,
        {(x+w/2)*64 , (y+h/2)*64, w*64, h*64},
        {sw, sh, sim, sfm},
        alpha
    };

    return new Decoration(decor_obj);
}

void Decoration::appendDecor(Map *map, string0D decor_dir, bool front)
{
    std::ifstream inputFile(decor_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {   
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        if (front)
        {
            map->DecorFrontVec.push_back(codeToDecorInfo(line));
            map->DecorFrontVec.back()->initDecoration();
        }
        else
        {
            map->DecorBackVec.push_back(codeToDecorInfo(line));
            map->DecorBackVec.back()->initDecoration();
        }
    }
}

void Decoration::appendBackground(Map *map, string0D bg_dir)
{
    std::ifstream inputFile(bg_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        std::stringstream ss(line);
        char cm = ',';

        string0D bg_path;

        // Background Color
        if (line[0] == '*')
        {
            std::getline(ss, bg_path, ',');
            int r = 0, g = 0, b = 0;
            ss >> r >> cm >> g >> cm >> b;
            map->MapColor = {r, g ,b};
            return;
        }

        // Background Layers
        float w_h_ratio;
        float scale_vel_x, scale_vel_y;
        float vel_x;

        std::getline(ss, bg_path, ',');
        ss >> w_h_ratio >> cm >> scale_vel_x >> cm >> scale_vel_y >> cm >> vel_x;

        map->BackgroundVec.push_back(new Decoration(bg_path, w_h_ratio, scale_vel_x, scale_vel_y, vel_x, 1));
        map->BackgroundVec.back()->initDecoration();
        map->BackgroundVec.push_back(new Decoration(bg_path, w_h_ratio, scale_vel_x, scale_vel_y, vel_x, 1));
        map->BackgroundVec.back()->initDecoration();
    }
}