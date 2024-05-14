#include <world.h>
#include <exclusive_all.h>

// ========================= MAP COMPONENT ==========================

void MapComponent::appendDirectory()
{
    playlist = map->MapDirectory + "/playlist.csv";
    block_path = map->MapDirectory + "/block_path.csv";
    block_main = map->MapDirectory + "/block_main.csv";
    block_back = map->MapDirectory + "/block_back.csv";
    block_hidden = map->MapDirectory + "/block_hidden.csv";
    background = map->MapDirectory + "/background.csv";
    decor_back = map->MapDirectory + "/decoration_back.csv";
    decor_front = map->MapDirectory + "/decoration_front.csv";
    bubble = map->MapDirectory + "/bubble.csv";
    door = map->MapDirectory + "/door.csv";
    audio_obj = map->MapDirectory + "/audio_obj.csv";
    camera_box = map->MapDirectory + "/camera_box.csv";
    transit_map = map->MapDirectory + "/transit_map.csv";
}

void MapComponent::appendComponent()
{
    // ======================= DELETE PREVIOUS ===================
    clearComponent();

    // ======================= APPEND NEW ========================

    appendPlaylist();
    appendBlockPath();
    appendBlockMain();
    appendBlockBack();
    appendBlockHidden();
    appendBackground();
    appendDecorBack();
    appendDecorFront();
    appendDoor();
    appendBubble();
    appendEnemy();
    appendItem();
    appendAudioObj();
    appendCameraBox();
    appendTransitMap();

    // ======================= OTHER =============================

    // PREVIEWER
    for (string0D path : map->BlockPath)
        map->BlockPreview.push_back(
            Object2D::loadTexture(path)
        );
    map->BlockPreview.push_back(
        Object2D::loadTexture("res/BlockTile/Null.png")
    );
}

void MapComponent::appendPlaylist()
{ Audio::appendMapPlaylist(map, playlist); }
void MapComponent::appendBlockPath()
{ map->BlockPath = CFG->convertStrVec(block_path); }
void MapComponent::appendBlockMain()
{ BlockTemplate::appendBlock(map, block_main); }
void MapComponent::appendBlockBack()
{ BlockTemplate::appendBlock(map, block_back, 1); }
void MapComponent::appendBlockHidden()
{ BlockTemplate::appendBlock(map, block_hidden, 2); }
void MapComponent::appendBackground()
{ Decoration::appendBackground(map, background); }
void MapComponent::appendDecorBack()
{ Decoration::appendDecor(map, decor_back); }
void MapComponent::appendDecorFront()
{ Decoration::appendDecor(map, decor_front, 1); }
void MapComponent::appendDoor()
{ Door::appendDoor(map, door); }
void MapComponent::appendBubble()
{ Bubble::appendBubble(map, bubble); }
void MapComponent::appendEnemy()
{}
void MapComponent::appendItem()
{}
void MapComponent::appendAudioObj()
{ AudioObject::appendAudioObject(map, audio_obj); }
void MapComponent::appendCameraBox()
{ map->appendCameraBox(camera_box); }
void MapComponent::appendTransitMap()
{ map->appendTransitMap(transit_map); }

void MapComponent::clearComponent()
{
    clearPlaylist();
    clearBlockPath();
    clearBlockMain();
    clearBlockBack();
    clearBlockHidden();
    clearBackground();
    clearDecorBack();
    clearDecorFront();
    clearDoor();
    clearBubble();
    clearEnemy();
    clearItem();
    clearAudioObj();
    clearCameraBox();
    clearTransitMap();
}

void MapComponent::clearPlaylist() { map->MapPlaylist = {}; }
void MapComponent::clearBlockPath() {
    map->BlockPath = {};
    for (SDL_Texture *preview : map->BlockPreview)
        SDL_DestroyTexture(preview);
    map->BlockPreview = {};
}
void MapComponent::clearBlockMain()
{ for (Block *block : map->BlockMainVec) delete block; map->BlockMainVec = {}; }
void MapComponent::clearBlockBack()
{ for (Block *block : map->BlockBackVec) delete block; map->BlockBackVec = {}; }
void MapComponent::clearBlockHidden()
{ 
    for (Block1D block1d : map->BlockHiddenVec)
    for (Block *block : block1d) delete block;
    map->BlockHiddenVec = {};
}
void MapComponent::clearBackground()
{ for (Decoration *bg : map->BackgroundVec) delete bg; map->BackgroundVec = {}; }
void MapComponent::clearDecorBack()
{ for (Decoration *decor : map->DecorBackVec) delete decor; map->DecorBackVec = {}; }
void MapComponent::clearDecorFront()
{ for (Decoration *decor : map->DecorFrontVec) delete decor; map->DecorFrontVec = {}; }
void MapComponent::clearDoor()
{ for (Door *door : map->DoorVec) delete door; map->DoorVec = {}; }
void MapComponent::clearBubble()
{ for (Bubble *bubble : map->BubbleVec) delete bubble; map->BubbleVec = {}; }
void MapComponent::clearEnemy()
{ for (Enemy *enemy : map->EnemyVec) delete enemy; map->EnemyVec = {}; }
void MapComponent::clearItem()
{ for (Item *item : map->ItemVec) delete item; map->ItemVec = {}; }
void MapComponent::clearAudioObj()
{ for (AudioObject *aObj : map->AudioObjVec) delete aObj; map->AudioObjVec = {}; }
void MapComponent::clearCameraBox() { map->CameraBox = {}; }
void MapComponent::clearTransitMap() { map->TransitMap = {}; }

void MapComponent::eraseBlockMain(int i)
{
    delete map->BlockMainVec[i];
    map->BlockMainVec.erase(map->BlockMainVec.begin() + i);
}
void MapComponent::eraseBlockBack(int i)
{
    delete map->BlockBackVec[i];
    map->BlockBackVec.erase(map->BlockBackVec.begin() + i);
}
void MapComponent::eraseBlockHidden(int i)
{
    for (Block *block : map->BlockHiddenVec[i]) delete block;
    map->BlockHiddenVec.erase(map->BlockHiddenVec.begin() + i);
}
void MapComponent::eraseBackground(int i)
{
    delete map->BackgroundVec[i];
    map->BackgroundVec.erase(map->BackgroundVec.begin() + i);
}
void MapComponent::eraseDecorBack(int i)
{
    delete map->DecorBackVec[i];
    map->DecorBackVec.erase(map->DecorBackVec.begin() + i);
}
void MapComponent::eraseDecorFront(int i)
{
    delete map->DecorFrontVec[i];
    map->DecorFrontVec.erase(map->DecorFrontVec.begin() + i);
}
void MapComponent::eraseDoor(int i)
{
    delete map->DoorVec[i];
    map->DoorVec.erase(map->DoorVec.begin() + i);
}
void MapComponent::eraseBubble(int i)
{
    delete map->BubbleVec[i];
    map->BubbleVec.erase(map->BubbleVec.begin() + i);
}
void MapComponent::eraseEnemy(int i)
{
    delete map->EnemyVec[i];
    map->EnemyVec.erase(map->EnemyVec.begin() + i);
}
void MapComponent::eraseItem(int i)
{
    delete map->ItemVec[i];
    map->ItemVec.erase(map->ItemVec.begin() + i);
}
void MapComponent::eraseAudioObj(int i)
{
    delete map->AudioObjVec[i];
    map->AudioObjVec.erase(map->AudioObjVec.begin() + i);
}
void MapComponent::eraseCameraBox(int i)
{ map->CameraBox.erase(map->CameraBox.begin() + i); }
void MapComponent::eraseTransitMap(int i)
{ map->TransitMap.erase(map->TransitMap.begin() + i); }

// ========================= MAP ==============================

Map::~Map() { MapComp.clearComponent(); }
Map::Map(string0D mapname) :
    MapName(mapname),
    MapDirectory("map_data/" + mapname)
{}

void Map::initMapStandard()
{
    MapComp.map = this;
    MapComp.appendDirectory();
    MapComp.appendComponent();
}

void Map::initMap(World *world, Multiplayer *multi, Audio *audio,
                Collision *collision, int id)
{
    MapId = id;
    MapAudio = audio;
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

    // ================= Update Player ===================================
    MapMulti->update(this);
    // ================= Update Component logic for each Player ==========
    for (Player *player : MapMulti->Players)
    {
        // Collision
        MapCollision->playerUpdateCollision(this, player);
        // Door
        for (Door *door : DoorVec)
            door->update(this, player);
        // Map Transitor
        for (MapTransit m_trans : TransitMap)
        if (player->insideGridBox(m_trans.box))
        {
            MapWorld->setTransit(m_trans.location);
            break;
        }
    }

    // ==== Component that has function distinct from other component ======
    // (It has other player logic in mind)

    for (Bubble *bubble : BubbleVec)
        bubble->update(MapMulti);

    for (Enemy *enemy : EnemyVec)
        enemy->updateEnemy(this);

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

    // ============== UPDATE DRAW PROPERTIES =================

    /*
        == [Draw Prop] ==

        To make the drawing process even smoother, SDL_Rects used for
        render will now be updated seperate from draw functions

        Some Components have logic functions aside from drawing
        (E.X: Block need collision logic) so drawProp() will be included
        inside of those function instead of explicitly called down here
    */
    for (Decoration *background : DecorBackVec)
        background->drawProp(MapMulti->MAIN);
    for (Decoration *background : DecorFrontVec)
        background->drawProp(MapMulti->MAIN);
    for (ParticleEffect *particle_fx : ParticleBackVec)
        particle_fx->drawProp(MapMulti->MAIN);
    for (ParticleEffect *particle_fx : ParticleFrontVec)
        particle_fx->drawProp(MapMulti->MAIN);
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

void Map::appendTransitMap(string0D trans_dir)
{
    std::ifstream inputFile(trans_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        int1D mtr = CFG->convertStrInt1D(line);
        bool snap = mtr.size() == 8 ? 1 : 0;

        TransitMap.push_back({
            {mtr[0], mtr[1], mtr[2], mtr[3]},
            {mtr[4], mtr[5], mtr[6], snap}
        });
    }
}

void Map::appendCameraBox(string0D cam_dir)
{
    std::ifstream inputFile(cam_dir);
    string0D line;

    while (std::getline(inputFile, line))
    {
        // Empty or Comment => Skip
        if (CFG->isComment(line)) continue;

        if (line == "*")
        { OutsideRender = true; return; }

        int1D cb = CFG->convertStrInt1D(line);

        CameraBox.push_back({
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