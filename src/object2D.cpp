#include <object2D.h>

// ========================== OBJECT BOX ==========================
ObjectHitbox ObjectHitbox::hitboxGrid(int gr)
{ return {x * gr, y * gr, w * gr, h * gr, hw * gr, hh * gr}; }
void ObjectHitbox::grid(int gr)
{
    x *= gr; y *= gr;
    w *= gr; h *= gr;
    hw *= gr; hh *= gr;
}

ObjectBox ObjectBox::boxGrid(int gr)
{ return {up * gr, down * gr, left * gr, right * gr}; }
void ObjectBox::grid(int gr)
{
    up *= gr; down *= gr;
    left *= gr; right *= gr;
}
void ObjectBox::reorder()
{
    if (up < down)
    { int d = down; down = up; up = d; }
    if (right < left)
    { int l = left; left = right; right = l; }
}
void ObjectBox::copy(ObjectBox box)
{
    up = box.up; down = box.down;
    left = box.left; right = box.right;
}
bool ObjectBox::compare(ObjectBox box)
{
    return (up == box.up && down == box.down &&
            left == box.left && right == box.right);
}
bool ObjectBox::contain(int x, int y)
{
    return (x >= left && x <= right &&
            y >= down && y <= up);
}
ObjectHitbox ObjectBox::hitbox()
{ return {
    float(right + left) / 2, float(up + down) / 2,
    float(right - left) / 2, float(up - down) / 2,
    (right - left) / 2, (up - down) / 2
}; }

// ========================== OBJECT ==============================

Object2D::~Object2D() {
    // std::cout << "memory freed :D" << "\n";
}

Object2D::Object2D() {}
Object2D::Object2D(ObjectHitbox box, ObjectSprite sprite, ObjectMovement movement) :
    x(box.x), y(box.y), width(box.w), height(box.h), hit_w(box.hw), hit_h(box.hh),
    sprite_width(sprite.sw), sprite_height(sprite.sh),
    sprite_index_max(sprite.sim), sprite_frame_max(sprite.sfm),
    sprite_index(sprite.si), sprite_frame(sprite.sf)
{}
Object2D::Object2D(float X, float Y, int w, int h) :
    x(X), y(Y), width(w), height(h)
{}
Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh) : 
    x(X), y(Y), width(w), height(h), hit_w(hw), hit_h(hh)
{}
Object2D::Object2D(float X, float Y, int w, int h, int hw, int hh, int sw, int sh, int sim, int sfm, int si, int sf) : 
    x(X), y(Y), width(w), height(h), hit_w(hw), hit_h(hh),
    sprite_width(sw), sprite_height(sh),
    sprite_index_max(sim), sprite_frame_max(sfm),
    sprite_index(si), sprite_frame(sf)
{}

// Ignore drawing
bool Object2D::getIgnore() { return ignore; }
void Object2D::setIgnore(bool ig) { ignore = ig; }

// Camera Independent
bool Object2D::getCamDepend() { return cam_depend; }
void Object2D::setCamDepend(bool depend) { cam_depend = depend; }

// Position
void Object2D::setX(float X) { x = X; }
void Object2D::setY(float Y) { y = Y; }
float Object2D::getX() { return x; }
float Object2D::getY() { return y; }
int Object2D::getGridX() { return x / 64; }
int Object2D::getGridY() { return y / 64; }
int Object2D::getGridLX() { return (x - float(width)/2) / 64; }
int Object2D::getGridRX() { return (x + float(width)/2) / 64; }
int Object2D::getGridBY() { return (y - float(height)/2) / 64; }
int Object2D::getGridTY() { return (y + float(height)/2) / 64; }

// Size / hitbox
void Object2D::setWidth(int w) { width = w; }
void Object2D::setHeight(int h) { height = h; }
void Object2D::setHitWidth(int hw) { hit_w = hw; }
void Object2D::setHitHeight(int hh) { hit_h = hh; }
int Object2D::getWidth() { return width; }
int Object2D::getHeight() { return height; }
int Object2D::getGridWidth(bool getExtend) 
{return (int(width / 64) < width / 64) && getExtend ?
        int(width / 64) + 1 : int(width / 64); }
int Object2D::getGridHeight(bool getExtend)
{return (int(height / 64) < height / 64) && getExtend ?
        int(height / 64) + 1 : int(height / 64); }
int Object2D::getHitWidth() { return hit_w; }
int Object2D::getHitHeight() { return hit_h; }

// Combat hitbox
void Object2D::setCombatHit(ObjectCombatHit c_hit)
{
    combat_hit_up = c_hit.up;
    combat_hit_down = c_hit.down;
    combat_hit_left = c_hit.left;
    combat_hit_right = c_hit.right;
    combat_damage = c_hit.dmg;
}
void Object2D::setCombatHitU(int hit) { combat_hit_up = hit; }
void Object2D::setCombatHitD(int hit) { combat_hit_down = hit; }
void Object2D::setCombatHitL(int hit) { combat_hit_left = hit; }
void Object2D::setCombatHitR(int hit) { combat_hit_right = hit; }
void Object2D::setCombatDamage(int dmg) { combat_damage = dmg; }
ObjectCombatHit Object2D::getCombatHit() { return {
    combat_hit_up, combat_hit_down,
    combat_hit_left, combat_hit_right,
    combat_damage
}; }
int Object2D::getCombatHitU() { return combat_hit_up; }
int Object2D::getCombatHitD() { return combat_hit_down; }
int Object2D::getCombatHitL() { return combat_hit_left; }
int Object2D::getCombatHitR() { return combat_hit_right; }
int Object2D::getCombatDamage() { return combat_damage; }

// Draw
void Object2D::setSprWidth(int sw) { sprite_width = sw; }
void Object2D::setSprHeight(int sh) { sprite_height = sh; }
void Object2D::setSprIndex(int si) { sprite_index = si; }
void Object2D::setSprIndexMax(int sim) { sprite_index_max = sim; }
void Object2D::setSprRow(int sr) { sprite_row = sr; }
void Object2D::setSprRowMax(int srm) { sprite_row_max = srm; }
void Object2D::setSprRowRepeat(int srr) { sprite_row_repeat = srr; }
void Object2D::setSprFrame(int sf) { sprite_frame = sf; }
void Object2D::setSprFrameMax(int sfm) { sprite_frame_max = sfm; }
int Object2D::getSprWidth() { return sprite_width; }
int Object2D::getSprHeight() { return sprite_height; }
int Object2D::getSprIndex() { return sprite_index; }
int Object2D::getSprIndexMax() { return sprite_index_max; }
int Object2D::getSprRow() { return sprite_row; }
int Object2D::getSprRowMax() { return sprite_row_max; }
int Object2D::getSprRowRepeat() { return sprite_row_repeat; }
int Object2D::getSprFrame() { return sprite_frame; }
int Object2D::getSprFrameMax() { return sprite_frame_max; }

// Speed / Accelaration
void Object2D::setVelX(float velX) { vel_x = velX; }
void Object2D::setVelY(float velY) { vel_y = velY; }
void Object2D::setAccelX(float accX) { accel_x = accX; }
void Object2D::setAccelY(float accY) { accel_y = accY; }
float Object2D::getVelX() { return vel_x; }
float Object2D::getVelY() { return vel_y; }
float Object2D::getAccelX() { return accel_x; }
float Object2D::getAccelY() { return accel_y; }

// Special Key
void Object2D::setSpecialKey(int key) { special_key = key; }
int Object2D::getSpecialKey() { return special_key; }

// BOX
ObjectBox Object2D::getBox()
{ return {
    int(getY() + getHeight() / 2),
    int(getY() - getHeight() / 2),
    int(getX() - getWidth() / 2),
    int(getX() + getWidth() / 2)
}; }
bool Object2D::insideBox(ObjectBox box)
{
    return  (getY() <= box.up || box.up == -1) &&
            (getY() >= box.down || box.down == -1) &&
            (getX() >= box.left || box.left == -1) &&
            (getX() <= box.right || box.right == -1);
}
bool Object2D::insideGridBox(ObjectBox gridbox)
{ return !(
    (getGridY() > gridbox.up && gridbox.up > -1) ||
    (getGridY() < gridbox.down && gridbox.down > -1) ||
    (getGridX() < gridbox.left && gridbox.left > -1) ||
    (getGridX() > gridbox.right && gridbox.right > -1)
); }

// ======================== VERY HELPFUL METHOD ========================

// Distance
int Object2D::distX(Object2D *obj1, Object2D *obj2, bool absolute)
{   
    int distX = obj1->getX() - obj2->getX();
    return absolute ? abs(distX) : distX;
}
int Object2D::distY(Object2D *obj1, Object2D *obj2, bool absolute)
{
    int distY = obj1->getY() - obj2->getY();
    return absolute ? abs(distY) : distY;
}
int Object2D::distBorderX(Object2D *obj1, Object2D *obj2)
{
    int dist_x = distX(obj1, obj2, 1);
    int dist_border_x = dist_x - obj1->getWidth()/2 - obj2->getWidth()/2;
    return dist_border_x;
}
int Object2D::distBorderY(Object2D *obj1, Object2D *obj2)
{
    int dist_y = distY(obj1, obj2, 1);
    int dist_border_y = dist_y - obj1->getHeight()/2 - obj2->getHeight()/2;
    return dist_border_y;
}
int Object2D::distR(Object2D *obj1, Object2D *obj2)
{
    int sqrX = pow(distX(obj1, obj2), 2);
    int sqrY = pow(distY(obj1, obj2), 2);
    return sqrt(sqrX + sqrY);
}

bool Object2D::objectIgnore(Object2D *objMain, Object2D *objSub)
{
    int dist_x = Object2D::distX(objMain, objSub);
    int dist_y = Object2D::distY(objMain, objSub);

    return (dist_x - objSub->getWidth() > CFG->WIDTH ||
            dist_y - objSub->getHeight() > CFG->HEIGHT);
};

// Texture

SDL_Texture *Object2D::loadTexture(string0D path)
{
    if (path == "") return NULL;

    SDL_Surface *surface = IMG_Load(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(CFG->RENDERER, surface);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surface);

    return texture;
}
SDLTexture1D Object2D::loadTextures(string0D path, int max)
{
    if (path == "") return {};

    SDLTexture1D textures;
    for (int i = 0; i < max; i++)
    {
        string0D frame_path = 
            path + "frame_" + CFG->convertDigit(i, max) + ".png";
        textures.push_back(loadTexture(frame_path));
    }

    return textures;
}

void Object2D::deleteTextures(SDLTexture1D textures)
{ for (SDL_Texture *tex : textures) SDL_DestroyTexture(tex); }

void Object2D::objectStandardMovement(bool lock_vel)
{
    x += vel_x;
    y += vel_y;

    if (lock_vel) return;
    vel_x += accel_x;
    vel_y += accel_y;
};

float1D Object2D::objectPredictMovement()
{ return {x + vel_x, y + vel_y}; }

bool Object2D::setSprite(bool end_lock)
{
    if (!sprite_index_max) return false;

    if (sprite_frame < sprite_frame_max)
        sprite_frame++;
    else
    {
        sprite_frame = 0;
        sprite_index++;
    }

    if (sprite_index >= sprite_index_max)
    {
        if (end_lock)
            sprite_index = sprite_index_max - 1;
        else
            sprite_index = 0;

        if (sprite_row_max)
        {
            sprite_row++;
            if (sprite_row >= sprite_row_max)
            {
                sprite_row = sprite_row_repeat - 1;
                return true;
            }
        }
        else
            return true;
    }

    return false;
}

void Object2D::objectSetSprite(ObjectSprite &sprite)
{
    if (sprite.sf < sprite.sfm)
        sprite.sf++;
    else
    {
        sprite.sf = 0;
        sprite.si++;
    }

    if (sprite.si >= sprite.sim)
        sprite.si = 0;
}