#ifndef MAP_H
#define MAP_H

#include <audio.h>
#include <input.h>
#include <collision.h>
#include <block_template.h>

#include <door.h>
#include <item.h>
#include <block.h>
#include <player.h>
#include <bubble.h>
#include <decoration.h>
#include <projectile.h>
#include <audio_object.h>
#include <particle_effect.h>

#include <enemy/all_enemies.h>

typedef void(*ExclusiveUpdate)(Map *);

#define MapTransit1D std::vector<MapTransit>

struct MapBgColor
{ int R = 0, G = 0, B = 0; };

struct MapComponent
{
    // Directory
    std::string map_dir = "";
    std::string playlist = "";
    std::string block_path = "",
                block_main = "",
                block_back = "",
                block_hidden = "";
    std::string background = "",
                decor_back = "",
                decor_front = "";
    std::string door = "",
                bubble = "",
                enemy = "",
                item = "";
    std::string audio_obj = "";
    std::string camera_box = "",
                transit_map = "";

    void appendDirectory(std::string MapDirectory);
    void appendComponent(Map *map);
    void clearComponent(Map *map);

    // Clear all
    static void clearPlaylist(Map *map);
    static void clearBlockPath(Map *map);
    static void clearBlockMain(Map *map);
    static void clearBlockHidden(Map *map);
    static void clearBlockBack(Map *map);
    static void clearBackground(Map *map);
    static void clearDecorBack(Map *map);
    static void clearDecorFront(Map *map);
    static void clearDoor(Map *map);
    static void clearBubble(Map *map);
    static void clearEnemy(Map *map);
    static void clearItem(Map *map);
    static void clearAudioObj(Map *map);
    static void clearCameraBox(Map *map);
    static void clearTransitMap(Map *map);

    // Delete specific
    static void eraseBlockMain(Map *map, int i);
    static void eraseBlockBack(Map *map, int i);
    static void eraseBlockHidden(Map *map, int i);
    static void eraseBackground(Map *map, int i);
    static void eraseDecorBack(Map *map, int i);
    static void eraseDecorFront(Map *map, int i);
    static void eraseDoor(Map *map, int i);
    static void eraseBubble(Map *map, int i);
    static void eraseEnemy(Map *map, int i);
    static void eraseItem(Map *map, int i);
    static void eraseAudioObj(Map *map, int i);
    static void eraseCameraBox(Map *map, int i);
    static void eraseTransitMap(Map *map, int i);

};

class Map
{
public:
    // =============== ATTRIBUTE =================
    bool MapId = -1;
    bool MapEmpty = false;
    bool MapActive = 0;

    World *MapWorld;
    Audio *MapAudio;
    Input *MapInput;
    Player *MapPlayer;
    Collision *MapCollision;

    std::string MapName = "";
    std::string MapDirectory = "";
    MapComponent MapComp;
    MapBgColor MapColor;

    // ======== MAP ENTITY ========

    // Music Album
    AudioPlaylist MapPlaylist;
    // Block Path
    string1D BlockPath;
    // Block Preview Texture
    SDLTexture1D BlockPreview;
    // Enemy
    Enemy1D EnemyVec;
    // Npc
    Bubble1D BubbleVec;
    // Particle_Effect
    Particle1D ParticleBackVec;
    Particle1D ParticleFrontVec;
    // Block
    Block1D BlockMainVec;
    Block1D BlockBackVec;
    Block2D BlockHiddenVec;
    // Yuki Makoto
    Door1D DoorVec;
    // Item
    Item1D ItemVec;
    // Cosmetic
    Decoration1D BackgroundVec;
    Decoration1D DecorBackVec;
    Decoration1D DecorFrontVec;
    // Projectile
    Projectile1D ProjectileVec;
    // AUDIO SOURCE
    AudioObj1D AudioObjVec;
    // Exclusive update function
    ExclusiveUpdate UpdateExclusive;

    // ======== MAP INTERACTION ========
    bool OutsideRender = 0;
    CameraBox1D CameraBox;
    MapTransit1D TransitMap;

    // =================== Stage stuff idc ===================

    ~Map();
    Map(std::string mapname);

    void initMapStandard();
    void initMap(World *world, Player *player, Audio *audio,
                Input *input, Collision *collision, int id = -1);

    void updateMapActive();
    void updateMapGlobal();

    // ================== MAP ... IDK WHAT ALGORITHM =====================
    
    void loadCheckpoint(WorldLocation location);
    static void appendTransitMap(Map *map, std::string trans_dir);
    static void appendCameraBox(Map *map, std::string cam_dir);

    // ================== MAP MANIPULATION ALGORITHM ===================== ( HELPFUL :D)

    static string1D convertStrVec(std::string file_dir);

    static int2D resizeInt2D(int1D vec, int r, int c);
    static float2D resizeFloat2D(float1D vec, int r, int c);

    static float1D convertStrFloat1D(std::string str, char delimiter = ',');
    static int1D convertStrInt1D(std::string str, char delimiter = ',');

    static int1D convertFloat1DInt(float1D vec);
    static int2D convertFloat2DInt(float2D vec);
};

#endif