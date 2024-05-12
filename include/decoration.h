#ifndef DECORATION_H
#define DECORATION_H

#include <object2D.h>

#define Decoration1D std::vector<Decoration*>

struct DecorObject
{
    string0D path;
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

    string0D decor_path;
    string0D decor_frame = "";

    SDL_Texture *decor_texture;
    SDLTexture1D decor_textures;

    SDL_Rect des_rect, src_rect;

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
    Decoration(string0D dPath, float whRatio, float scaleVelX = .1, float scaleVelY = .1, float velX = 0);
    // Static Decoration
    Decoration(string0D dPath, float X, float Y, float w, float h, bool abs);
    // Standard Animated Decoration
    Decoration(string0D dPath, float X, float Y, float w, float h, int sw, int sh, int sim, int sfm);
    // Advance Animated Decoration
    Decoration(string0D dPath, string0D fPath, float X, float Y, float w, float h, int sim, int sfm);

    float getAddX();
    float getSclVelX();
    float getSclVelY();

    void setAbs(bool ab);
    void setAlpha(int a);
    void initDecoration();

    // Decoration
    void draw(Player *player);
    // Background
    void updateBackground(Player *player, bool left_prlx = 0);
    void drawBackground();

    // File manip
    static Decoration *codeToDecorInfo(string0D str);
    static void appendDecor(Map *map, string0D decor_dir, bool front = 0);
    static void appendBackground(Map *map, string0D bg_dir);
};

#endif