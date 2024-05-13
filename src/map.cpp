#include <world.h>
#include <exclusive_all.h>

// ========================= MAP COMPONENT ==========================

void MapComponent::appendDirectory(string0D MapDirectory)
{
    map_dir = MapDirectory;
    playlist = MapDirectory + "/playlist.csv";
    block_path = MapDirectory + "/block_path.csv";
    block_main = MapDirectory + "/block_main.csv";
    block_back = MapDirectory + "/block_back.csv";
    block_hidden = MapDirectory + "/block_hidden.csv";
    background = MapDirectory + "/background.csv";
    decor_back = MapDirectory + "/decoration_back.csv";
    decor_front = MapDirectory + "/decoration_front.csv";
    bubble = MapDirectory + "/bubble.csv";
    door = MapDirectory + "/door.csv";
    audio_obj = MapDirectory + "/audio_obj.csv";
    camera_box = MapDirectory + "/camera_box.csv";
    transit_map = MapDirectory + "/transit_map.csv";
}

void MapComponent::appendComponent(Map *map)
{
    // ======================= DELETE PREVIOUS ===================
    clearComponent(map);

    // ======================= TRACKS ============================
    Audio::appendMapPlaylist(map, playlist);

    // ======================= BACKGROUND ========================
    Decoration::appendBackground(map, background);

    // ======================= BLOCKS ============================
    map->BlockPath = CFG->convertStrVec(block_path);

    // PREVIEWER
    for (string0D path : map->BlockPath)
        map->BlockPreview.push_back(
            Object2D::loadTexture(path)
        );
    map->BlockPreview.push_back(
        Object2D::loadTexture("res/BlockTile/Null.png")
    );

    // GAMEPLAY
    BlockTemplate::appendBlock(map, block_main);
    BlockTemplate::appendBlock(map, block_back, 1);
    BlockTemplate::appendBlock(map, block_hidden, 2);

    // ======================= DECORATION ========================
    Decoration::appendDecor(map, decor_back);
    Decoration::appendDecor(map, decor_front, 1);

    // ======================= DIALOGUE BUBBLE ===================
    Bubble::appendBubble(map, bubble);

    // ======================= DOOR ==============================
    Door::appendDoor(map, door);

    // ======================= AUDIO OBJECT ======================
    AudioObject::appendAudioObject(map, audio_obj);

    // ======================= CAMERA BOX ========================
    Map::appendCameraBox(map, camera_box);

    // ======================= MAP TRANSIT =======================
    Map::appendTransitMap(map, transit_map);
}

void MapComponent::clearComponent(Map *map)
{
    clearPlaylist(map);
    clearBlockPath(map);
    clearBlockMain(map);
    clearBlockBack(map);
    clearBlockHidden(map);
    clearBackground(map);
    clearDecorBack(map);
    clearDecorFront(map);
    clearDoor(map);
    clearBubble(map);
    clearEnemy(map);
    clearItem(map);
    clearAudioObj(map);
    clearCameraBox(map);
    clearTransitMap(map);
}

void MapComponent::clearPlaylist(Map *map) { map->MapPlaylist = {}; }
void MapComponent::clearBlockPath(Map *map) {
    map->BlockPath = {};
    for (SDL_Texture *preview : map->BlockPreview)
        SDL_DestroyTexture(preview);
    map->BlockPreview = {};
}
void MapComponent::clearBlockMain(Map *map)
{ for (Block *block : map->BlockMainVec) delete block; map->BlockMainVec = {}; }
void MapComponent::clearBlockBack(Map *map)
{ for (Block *block : map->BlockBackVec) delete block; map->BlockBackVec = {}; }
void MapComponent::clearBlockHidden(Map *map)
{ 
    for (Block1D block1d : map->BlockHiddenVec)
    for (Block *block : block1d) delete block;
    map->BlockHiddenVec = {};
}
void MapComponent::clearBackground(Map *map)
{ for (Decoration *bg : map->BackgroundVec) delete bg; map->BackgroundVec = {}; }
void MapComponent::clearDecorBack(Map *map)
{ for (Decoration *decor : map->DecorBackVec) delete decor; map->DecorBackVec = {}; }
void MapComponent::clearDecorFront(Map *map)
{ for (Decoration *decor : map->DecorFrontVec) delete decor; map->DecorFrontVec = {}; }
void MapComponent::clearDoor(Map *map)
{ for (Door *door : map->DoorVec) delete door; map->DoorVec = {}; }
void MapComponent::clearBubble(Map *map)
{ for (Bubble *bubble : map->BubbleVec) delete bubble; map->BubbleVec = {}; }
void MapComponent::clearEnemy(Map *map)
{ for (Enemy *enemy : map->EnemyVec) delete enemy; map->EnemyVec = {}; }
void MapComponent::clearItem(Map *map)
{ for (Item *item : map->ItemVec) delete item; map->ItemVec = {}; }
void MapComponent::clearAudioObj(Map *map)
{ for (AudioObject *aObj : map->AudioObjVec) delete aObj; map->AudioObjVec = {}; }
void MapComponent::clearCameraBox(Map *map) { map->CameraBox = {}; }
void MapComponent::clearTransitMap(Map *map) { map->TransitMap = {}; }

void MapComponent::eraseBlockMain(Map *map, int i)
{
    delete map->BlockMainVec[i];
    map->BlockMainVec.erase(map->BlockMainVec.begin() + i);
}
void MapComponent::eraseBlockBack(Map *map, int i)
{
    delete map->BlockBackVec[i];
    map->BlockBackVec.erase(map->BlockBackVec.begin() + i);
}
void MapComponent::eraseBlockHidden(Map *map, int i)
{
    for (Block *block : map->BlockHiddenVec[i]) delete block;
    map->BlockHiddenVec.erase(map->BlockHiddenVec.begin() + i);
}
void MapComponent::eraseBackground(Map *map, int i)
{
    delete map->BackgroundVec[i];
    map->BackgroundVec.erase(map->BackgroundVec.begin() + i);
}
void MapComponent::eraseDecorBack(Map *map, int i)
{
    delete map->DecorBackVec[i];
    map->DecorBackVec.erase(map->DecorBackVec.begin() + i);
}
void MapComponent::eraseDecorFront(Map *map, int i)
{
    delete map->DecorFrontVec[i];
    map->DecorFrontVec.erase(map->DecorFrontVec.begin() + i);
}
void MapComponent::eraseDoor(Map *map, int i)
{
    delete map->DoorVec[i];
    map->DoorVec.erase(map->DoorVec.begin() + i);
}
void MapComponent::eraseBubble(Map *map, int i)
{
    delete map->BubbleVec[i];
    map->BubbleVec.erase(map->BubbleVec.begin() + i);
}
void MapComponent::eraseEnemy(Map *map, int i)
{
    delete map->EnemyVec[i];
    map->EnemyVec.erase(map->EnemyVec.begin() + i);
}
void MapComponent::eraseItem(Map *map, int i)
{
    delete map->ItemVec[i];
    map->ItemVec.erase(map->ItemVec.begin() + i);
}
void MapComponent::eraseAudioObj(Map *map, int i)
{
    delete map->AudioObjVec[i];
    map->AudioObjVec.erase(map->AudioObjVec.begin() + i);
}
void MapComponent::eraseCameraBox(Map *map, int i)
{ map->CameraBox.erase(map->CameraBox.begin() + i); }
void MapComponent::eraseTransitMap(Map *map, int i)
{ map->TransitMap.erase(map->TransitMap.begin() + i); }

// ========================= MAP ==============================

Map::~Map() { MapComp.clearComponent(this); }
Map::Map(string0D mapname) :
    MapName(mapname),
    MapDirectory("src/map_data/" + mapname)
{}

void Map::initMapStandard()
{
    MapComp.appendDirectory(MapDirectory);
    MapComp.appendComponent(this);
}

void Map::initMap(World *world, Multiplayer *multi, Audio *audio,
                Input *input, Collision *collision, int id)
{
    MapId = id;
    MapAudio = audio;
    MapInput = input;
    MapWorld = world;
    MapCollision = collision;

    MapMulti = multi;

    if (MapEmpty) return;

    initMapStandard();
    applyExclusive(this);
}

// ========================= UPDATE MAP ==============================

void Map::updateMapGlobal()
{
    // ====================== UPDATE PROJECTILE ========================
    for (Projectile *projectile : ProjectileVec)
        projectile->updateProjectile(this);

    // Erase Dead Bullet
    ProjectileVec.erase(std::remove_if(ProjectileVec.begin(), ProjectileVec.end(),
    [](Projectile* projectile) {
        if (projectile->getBulletDead())
        { delete projectile; return true; }
        return false;
    }), ProjectileVec.end());

    // ====================== UPDATE PARTICLE ==========================
    ParticleBackVec.erase(std::remove_if(ParticleBackVec.begin(), ParticleBackVec.end(),
    [](ParticleEffect* particle_fx) {
        if (particle_fx->getIsGone())
        { delete particle_fx; return true; }
        return false;
    }), ParticleBackVec.end());

    ParticleFrontVec.erase(std::remove_if(ParticleFrontVec.begin(), ParticleFrontVec.end(),
    [](ParticleEffect* particle_fx) {
        if (particle_fx->getIsGone())
        { delete particle_fx; return true; }
        return false;
    }), ParticleFrontVec.end());

    // ====================== ERASE DEAD ENEMY =========================
    EnemyVec.erase(std::remove_if(EnemyVec.begin(), EnemyVec.end(),
    [](Enemy* enemy) {
        // The other condition is to ensure enemy play dead animation
        return enemy->getDead() &&
        enemy->getSprIndex() >= enemy->getSprIndexMax() - 1;
    }), EnemyVec.end());

    // ====================== UPDATE SEETHOUGH BLOCK ===================

    for (Player *player : MapMulti->Players)
    {
        for (Bubble *bubble : BubbleVec)
            bubble->updateBubble(this, player);
    }

    for (Block1D blockSection : BlockHiddenVec)
    {
        bool seethru = 0;
        for (Block *block : blockSection)
            for (Player *player : MapMulti->Players)
                seethru = Collision::objectCollision(player, block) || seethru;
        seethru = seethru && MapActive;

        for (Block *block : blockSection)
            block->blockSeethrough(this, seethru);
    }

    // ====================== UPDATE EXCLUSIVE =========================
    UpdateExclusive(this);

    // ====================== UPDATE AUDIO OBJECT ======================
    // Note: Theres a really good reason why this is after UpdateExclusive
    for (AudioObject *a_obj : AudioObjVec)
        a_obj->updateProximity(this);
}

void Map::updateMapActive()
{
    // ================= In the middle of a transition =================
    if (MapWorld->map_transition)
        for (Player *player : MapMulti->Players)
            player->setStatic();

    if (MapWorld->map_transition > MapWorld->map_transition_mid)
    {
        for (Player *player : MapMulti->Players)
            player->INPUT.delay = MapWorld->map_transition_mid + 10;
        return;
    };

    MapMulti->update(this);
    for (Player *player : MapMulti->Players)
    {
        // Collision
        MapCollision->playerUpdateCollision(this, player);
        // Door
        for (Door *door : DoorVec) door->enterDoor(this, player);
        // Map Transitor
        for (MapTransit m_trans : TransitMap)
        if (player->insideGridBox(m_trans.box))
        {
            MapWorld->setTransit(m_trans.location);
            break;
        }
    }

    // ====================== UPDATE ENEMIES ===========================
    for (Enemy *enemy : EnemyVec) enemy->updateEnemy(this);

    // ====================== UPDATE PARALLAX BG =======================
    for (int i = 0; i < BackgroundVec.size(); i += 2)
    {
        BackgroundVec[i]->updateBackground(MapMulti->MAIN, 1);
        BackgroundVec[i+1]->updateBackground(MapMulti->MAIN);
    }

    // ====================== UPDATE CAMERA ============================
    MapMulti->MAIN->camera.outside_render = OutsideRender;
    for (PlayerCameraBox f_cam_box : CameraBox)
    if (MapMulti->MAIN->insideGridBox(f_cam_box.box))
    {
        MapMulti->MAIN->camera.setCameraBorder({1, 1, 1, 1}, f_cam_box.cam);
        break;
    }
}

// ================== MAP ... IDK WHAT ALGORITHM =====================

void Map::loadCheckpoint(WorldLocation location)
{
    for (Player *player : MapMulti->Players)
    {
        player->setStatic();
        player->setX(location.sX*64 + 35);
        player->setY(location.sY*64 + 51);
        player->camera.resetCamera();
        player->camera.focus_snap = location.snap;
    }
}

void Map::appendTransitMap(Map *map, string0D trans_dir)
{
    std::ifstream inputFile(trans_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] == '#') continue;

        int1D mtr = CFG->convertStrInt1D(line);
        bool snap = mtr.size() == 8 ? 1 : 0;

        map->TransitMap.push_back({
            {mtr[0], mtr[1], mtr[2], mtr[3]},
            {mtr[4], mtr[5], mtr[6], snap}
        });
    }
}

void Map::appendCameraBox(Map *map, string0D cam_dir)
{
    std::ifstream inputFile(cam_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (line == "" ||
            line.back() == '#' ||
            line[0] == '#') continue;

        if (line == "*")
        { map->OutsideRender = true; return; }

        int1D cb = CFG->convertStrInt1D(line);

        map->CameraBox.push_back({
            {cb[0], cb[1], cb[2], cb[3]},
            {cb[4], cb[5], cb[6], cb[7]}
        });
    }
}

void Map::appendParticle(ParticleEffect *particle, bool front)
{
    if (front)
        if (ParticleFrontVec.size() < 128)
            ParticleFrontVec.push_back(particle);
        else delete particle;
    else
        if (ParticleBackVec.size() < 128)
            ParticleBackVec.push_back(particle);
        else delete particle;
}

// ================== MAP MANIPULATION ALGORITHM =====================