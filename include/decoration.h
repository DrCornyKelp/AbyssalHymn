#ifndef DECORATION_H
#define DECORATION_H

#include <object2D.h>

#define Decoration1D std::vector<Decoration*>

struct DecorObject
{
    std::string path;
    ObjectHitbox box;
    ObjectSprite sprite;
    bool isFolder = 0;
    bool absolute = 0;
    int alpha = 255;
};

class Map;
class Player;
class Decoration : public Object2D
{
private:
    bool absolute = 0;
    int alpha = 255;

    std::string decor_path;
    std::string decor_frame = "";

    SDL_Texture *decor_texture;
    SDLTexture1D decor_textures;

    float   w_h_ratio = 1;
    float   add_x = 0;
    float   scale_vel_x = 0,
            scale_vel_y = 0;
public:
    // Destructor
    ~Decoration();
    // File Manip Decoration
    Decoration(DecorObject decor_obj);
    // Background
    Decoration(std::string dPath, float whRatio, float scaleVelX = 0.1, float scaleVelY = 0.1, float velX = 0);
    // Static Decoration
    Decoration(std::string dPath, float X, float Y, float w, float h, bool abs);
    // Standard Animated Decoration
    Decoration(std::string dPath, float X, float Y, float w, float h, int sw, int sh, int sim, int sfm);
    // Advance Animated Decoration
    Decoration(std::string dPath, std::string fPath, float X, float Y, float w, float h, int sim, int sfm);

    float getAddX();
    float getSclVelX();
    float getSclVelY();

    void setAbs(bool ab);
    void setAlpha(int a);
    void initDecoration();

    // Decoration
    void drawDecoration(Player *player);
    // Background
    void updateBackground(Player *player, bool left_prlx = 0);
    void drawBackground();

    // File manip
    static Decoration *codeToDecorInfo(std::string str);
    static void appendDecor(Map *map, std::string decor_dir, bool front = 0);
    static void appendBackground(Map *map, std::string bg_dir);
};

#endif