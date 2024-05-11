#include <map.h>

Decoration::~Decoration() {
    for (SDL_Texture *txt : decor_textures)
        SDL_DestroyTexture(txt);
    SDL_DestroyTexture(decor_texture);
}

Decoration::Decoration(DecorObject decor_obj) :
    Object2D(decor_obj.box, decor_obj.sprite),
    decor_path(decor_obj.path), decor_frame(decor_obj.isFolder ? "Yes" : ""),
    absolute(decor_obj.absolute), alpha(decor_obj.alpha)
{}

// Background
Decoration::Decoration( string0D dPath, float whRatio,
                        float scaleVelX, float scaleVelY, float velX) :
    decor_path(dPath), w_h_ratio(whRatio),
    scale_vel_x(scaleVelX), scale_vel_y(scaleVelY)
{ setVelX(velX); }

// Static Decoration
Decoration::Decoration(string0D dPath, float X, float Y, float w, float h, bool abs) :
    Object2D((X + w/2)*64, (Y + h/2)*64, w*64, h*64,
            0, 0, w, h, 0, 0, 0, 0),
    decor_path(dPath), absolute(abs)
{}

// Standard Animated Decoration
Decoration::Decoration(string0D dPath,
                        float X, float Y, float w, float h,
                        int sw, int sh, int sim, int sfm) :
    Object2D((X + w/2)*64, (Y + h/2)*64, w*64, h*64,
            0, 0, sw, sh, sim, sfm, 0, 0),
    decor_path(dPath)
{}

// Advanced Animated Decoration
Decoration::Decoration(string0D dPath, string0D fPath,
                        float X, float Y, float w, float h,
                        int sim, int sfm) :
    Object2D((X + w/2)*64, (Y + h/2)*64, w*64, h*64,
            0, 0, 0, 0, sim, sfm, 0, 0),
    decor_path(dPath), decor_frame("Yes")
{}

// Getter/setter
float Decoration::getAddX() { return add_x; }
float Decoration::getSclVelX() { return scale_vel_x; }
float Decoration::getSclVelY() { return scale_vel_y; }

// Helpful
string0D convertDigit(int number, int maxNumber)
{
    // Calculate the number of digits in the maximum number
    int numDigits = 1;
    int temp = maxNumber;
    while (temp /= 10) numDigits++;

    // Format the number with leading zeros based on the number of digits
    std::ostringstream oss;
    oss << std::setw(numDigits) << std::setfill('0') << number;
    return oss.str();
}

void Decoration::initDecoration()
{
    if (decor_frame != "")
        for (int i = 0; i < getSprIndexMax(); i++)
        {
            string0D frame_path = decor_path + "frame_" +
                                    convertDigit(i, getSprIndexMax()) +
                                    ".png";
            decor_textures.push_back(loadTexture(frame_path.c_str()));
        }
    else
    {
        decor_texture = loadTexture(decor_path);
        SDL_SetTextureBlendMode(decor_texture, SDL_BLENDMODE_BLEND);
        setAlpha(alpha);
    }
}

void Decoration::setAbs(bool ab) { absolute = ab; }
void Decoration::setAlpha(int a)
{
    alpha = a;
    SDL_SetTextureAlphaMod(decor_texture, a);
}

void Decoration::drawDecoration(Player *player)
{
    // Only render if box is in sight
    if (!absolute && Camera::renderIgnore(player, this))
        return;
    // Frame index shitty bang bang stuff handler
    objectSetSprite();

    // Draw
    SDL_Rect desRect;
    if (absolute) desRect = {
        int(getX() - getWidth() / 2),
        int(getY() - getHeight() / 2),
        getWidth(), getHeight()
    };
    else desRect = {
        Camera::objectDrawX(player, this),
        Camera::objectDrawY(player, this),
        getWidth(), getHeight()
    };

    if (!getSprIndexMax())
        SDL_RenderCopy(CFG->RENDERER, decor_texture, NULL, &desRect);
    else if (decor_frame == "")
    {
        SDL_Rect srcRect = {getSprIndex() * getSprWidth(), 0, getSprWidth(), getSprHeight()};
        SDL_RenderCopy(CFG->RENDERER, decor_texture, &srcRect, &desRect);
    }
    else
        SDL_RenderCopy(CFG->RENDERER, decor_textures[getSprIndex()], NULL, &desRect);
}

void Decoration::updateBackground(Player *player, bool left_prlx)
{
    // Resize
    if (CFG->WIDTH > CFG->HEIGHT * w_h_ratio)
    {
        setWidth(CFG->WIDTH);
        setHeight(CFG->WIDTH / w_h_ratio);
    }
    else
    {
        setWidth(CFG->HEIGHT * w_h_ratio);
        setHeight(CFG->HEIGHT);
    }

    int bg_shift = left_prlx ? getWidth()/2 : getWidth()*3/2;

    ObjectXY center_offset = player->camera.getCenterOffset();

    // ==================== Parallax X ====================
    // Automatic scroll
    if (getVelX())
    {
        add_x += getVelX();
        if (add_x > getWidth()) add_x = 0;
        if (add_x < 0) add_x = getWidth();
        setX(bg_shift - getAddX());
    }
    // Parallax stop (player unfocus)
    else if (player->camera.unfocus_x)
        setX(bg_shift - int(
            (player->camera.unfocus_offset_x) * scale_vel_x
        ) % getWidth());
    // Parallax moving (player focus)
    else
        setX(bg_shift - int((player->getX() - center_offset.x) * scale_vel_x) % getWidth());

    // ==================== Parallax Y ====================
    // Parallax stop (player unfocus)
    if (player->camera.unfocus_y)
        setY(CFG->HEIGHT/2 + int(player->camera.unfocus_offset_y * scale_vel_y));
    // Parallax moving (player focus)
    else
        setY(CFG->HEIGHT/2 + int((player->getY() - center_offset.y) * scale_vel_y));
}

void Decoration::drawBackground()
{
    SDL_Rect desRect = {
        int(getX() - getWidth() / 2),
        int(getY() - getHeight() / 2),
        getWidth(), getHeight()
    };

    SDL_RenderCopy(CFG->RENDERER, decor_texture, NULL, &desRect);
}

// ============================ FILE MANIPULATION ===================================

Decoration *Decoration::codeToDecorInfo(string0D str)
{
    std::stringstream ss(str);
    char cm = ',';

    string0D decor_type; // 0: static, 1: sprite sheet, 2: sprite folder
    string0D path;
    float x, y, w, h;
    int sw = 0, sh = 0, sim = 0, sfm = 0;
    bool abs = 0;
    int alpha = 255;

    std::getline(ss, decor_type, ',');
    std::getline(ss, path, ',');
    ss  >>  x >> cm >> y >> cm >>
            w >> cm >> h >> cm;

    if (decor_type == "1")
        ss >> sw >> cm >> sh >> cm >> sim >> cm >> sfm >> cm;
    if (decor_type == "2")
        ss >> sim >> cm >> sfm >> cm;

    ss >> abs >> cm >> alpha;

    DecorObject decor_obj = {
        path, {(x+w/2)*64 , (y+h/2)*64, w*64, h*64}, {sw, sh, sim, sfm},
        decor_type == "2", abs, alpha
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
        if (line == "" ||
            line.back() == '#' ||
            line[0] ==  '#') continue;

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
        if (line == "" ||
            line.back() == '#' ||
            line[0] == '#') continue;

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

        map->BackgroundVec.push_back(new Decoration(bg_path, w_h_ratio, scale_vel_x, scale_vel_y, vel_x));
        map->BackgroundVec.back()->initDecoration();
        map->BackgroundVec.push_back(new Decoration(bg_path, w_h_ratio, scale_vel_x, scale_vel_y, vel_x));
        map->BackgroundVec.back()->initDecoration();
    }
}