#ifndef MAP_H
#define MAP_H

#include <audio.h>
#include <input.h>
#include <collision.h>
#include <block_template.h>
#include <multiplayer.h>

#include <door.h>
#include <item.h>
#include <block.h>
#include <bubble.h>
#include <decoration.h>
#include <projectile.h>
#include <audio_object.h>
#include <particle_effect.h>

#include <enemy/all_enemies.h>

typedef void(*ExclusiveUpdate)(Map *);

#define MapTransit1D std::vector<MapTransit>

class Map;

struct MapBgColor
{ int R = 0, G = 0, B = 0; };

struct MapComponent
{
    Map *map;
    // Directory
    string0D 
        map_dir = "",
        playlist = "",

        block_path = "",
        block_main = "",
        block_back = "",
        block_hidden = "",

        background = "",
        decor_back = "",
        decor_front = "",

        door = "",
        bubble = "",
        enemy = "",
        item = "",
        audio_obj = "",
    
        camera_box = "",
        transit_map = "";

    void appendDirectory();
    void appendComponent();
    void clearComponent();

    // Append specific
    void appendPlaylist();
    void appendBlockPath();
    void appendBlockMain();
    void appendBlockHidden();
    void appendBlockBack();
    void appendBackground();
    void appendDecorBack();
    void appendDecorFront();
    void appendDoor();
    void appendBubble();
    void appendEnemy();
    void appendItem();
    void appendAudioObj();
    void appendCameraBox();
    void appendTransitMap();

    // Clear specific
    void clearPlaylist();
    void clearBlockPath();
    void clearBlockMain();
    void clearBlockHidden();
    void clearBlockBack();
    void clearBackground();
    void clearDecorBack();
    void clearDecorFront();
    void clearDoor();
    void clearBubble();
    void clearEnemy();
    void clearItem();
    void clearAudioObj();
    void clearCameraBox();
    void clearTransitMap();

    // Delete specific
    void eraseBlockMain(int i);
    void eraseBlockBack(int i);
    void eraseBlockHidden(int i);
    void eraseBackground(int i);
    void eraseDecorBack(int i);
    void eraseDecorFront(int i);
    void eraseDoor(int i);
    void eraseBubble(int i);
    void eraseEnemy(int i);
    void eraseItem(int i);
    void eraseAudioObj(int i);
    void eraseCameraBox(int i);
    void eraseTransitMap(int i);

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
    Collision *MapCollision;
    Multiplayer *MapMulti;

    string0D MapName = "";
    string0D MapDirectory = "";
    
    MapComponent MapComp;

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
    MapBgColor MapColor;
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
    Map(string0D mapname);

    void initMapStandard();
    void initMap(World *world, Multiplayer *multi, Audio *audio,
                Input *input, Collision *collision, int id = -1);

    void updateMapActive();
    void updateMapGlobal();

    // ================== MAP ... IDK WHAT ALGORITHM =====================
    
    void loadCheckpoint(WorldLocation location);
    void appendTransitMap(string0D trans_dir);
    void appendCameraBox(string0D cam_dir);

    void appendParticle(ParticleEffect *particle, bool front = 0);

};

#endif