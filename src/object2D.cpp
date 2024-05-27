#include <object2D.h>

// ========================== OBJECT HITBOX ==========================
ObjectHitbox ObjectHitbox::hitboxGrid(int gr)
{ return {x * gr, y * gr, w * gr, h * gr, hw * gr, hh * gr}; }
void ObjectHitbox::grid(int gr)
{
    x *= gr; y *= gr;
    w *= gr; h *= gr;
    hw *= gr; hh *= gr;
}
int ObjectHitbox::gridX() { return x / 64; }
int ObjectHitbox::gridY() { return y / 64; }
int ObjectHitbox::gridLX() { return (x - w/2) / 64; }
int ObjectHitbox::gridRX() { return (x + w/2) / 64; }
int ObjectHitbox::gridBY() { return (y - h/2) / 64; }
int ObjectHitbox::gridTY() { return (y + h/2) / 64; }
int ObjectHitbox::gridW(bool getExtend) { 
    return (int(w / 64) < h / 64) && getExtend ?
            int(w / 64) + 1 : int(w / 64);
}
int ObjectHitbox::gridH(bool getExtend) {
    return (int(h / 64) < h / 64) && getExtend ?
            int(h / 64) + 1 : int(h / 64);
}

// ========================== OBJECT BOX ==========================

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
{ 
    return {
        float(right + left) / 2, float(up + down) / 2,
        float(right - left) / 2, float(up - down) / 2,
        (right - left) / 2, (up - down) / 2
    };
}

// ========================== OBJECT ==============================

Object2D::~Object2D() {
    // std::cout << "memory freed :D" << "\n";
}

Object2D::Object2D() {}
Object2D::Object2D(ObjectHitbox box, ObjectSprite spr, ObjectVel v, ObjectAccel a) :
    hitbox(box), sprite(spr), vel(v), accel(a)
{}

// BOX
ObjectBox Object2D::getBox()
{ return {
    int(hitbox.y + hitbox.h / 2),
    int(hitbox.y - hitbox.h / 2),
    int(hitbox.x - hitbox.w / 2),
    int(hitbox.x + hitbox.w / 2)
}; }
bool Object2D::insideBox(ObjectBox box)
{
    return  (hitbox.y <= box.up || box.up == -1) &&
            (hitbox.y >= box.down || box.down == -1) &&
            (hitbox.x >= box.left || box.left == -1) &&
            (hitbox.x <= box.right || box.right == -1);
}
bool Object2D::insideGridBox(ObjectBox gridbox)
{ return !(
    (hitbox.gridY() > gridbox.up && gridbox.up > -1) ||
    (hitbox.gridY() < gridbox.down && gridbox.down > -1) ||
    (hitbox.gridX() < gridbox.left && gridbox.left > -1) ||
    (hitbox.gridX() > gridbox.right && gridbox.right > -1)
); }

// ======================== VERY HELPFUL METHOD ========================

// Distance
int Object2D::distX(Object2D *obj1, Object2D *obj2, bool absolute)
{   
    int distX = obj1->hitbox.x - obj2->hitbox.x;
    return absolute ? abs(distX) : distX;
}
int Object2D::distY(Object2D *obj1, Object2D *obj2, bool absolute)
{
    int distY = obj1->hitbox.y - obj2->hitbox.y;
    return absolute ? abs(distY) : distY;
}
int Object2D::distBorderX(Object2D *obj1, Object2D *obj2)
{
    int dist_x = distX(obj1, obj2, 1);
    int dist_border_x = dist_x - obj1->hitbox.w/2 - obj2->hitbox.w/2;
    return dist_border_x;
}
int Object2D::distBorderY(Object2D *obj1, Object2D *obj2)
{
    int dist_y = distY(obj1, obj2, 1);
    int dist_border_y = dist_y - obj1->hitbox.h/2 - obj2->hitbox.h/2;
    return dist_border_y;
}
int Object2D::distR(Object2D *obj1, Object2D *obj2)
{
    int sqrX = pow(distX(obj1, obj2), 2);
    int sqrY = pow(distY(obj1, obj2), 2);
    return sqrt(sqrX + sqrY);
}

ObjectBox Object2D::SDLRectToBox(SDL_Rect rect)
{
    return {
        rect.y + rect.h, rect.y, rect.x, rect.x + rect.w
    };
}
SDL_Rect Object2D::BoxToSDLRect(ObjectBox box)
{
    return {
        box.left, box.down, box.right - box.left, box.up - box.down
    };
}

bool Object2D::objectIgnore(Object2D *objMain, Object2D *objSub)
{
    int dist_x = Object2D::distX(objMain, objSub);
    int dist_y = Object2D::distY(objMain, objSub);

    return (dist_x - objSub->hitbox.w > CFG->WIDTH ||
            dist_y - objSub->hitbox.h > CFG->HEIGHT);
};

void Object2D::deleteTextures(SDLTexture1D textures)
{ for (SDL_Texture *tex : textures) SDL_DestroyTexture(tex); }

void Object2D::objectStandardMovement(bool lock_vel)
{
    hitbox.x += vel.x;
    hitbox.y += vel.y;

    if (lock_vel) return;
    vel.x += accel.x;
    vel.y += accel.y;
};

float1D Object2D::objectPredictMovement()
{ return {hitbox.x + vel.x, hitbox.y + vel.y}; }

bool Object2D::setSprite(bool end_lock)
{
    if (!sprite.sim) return false;

    if (sprite.sf < sprite.sfm)
        sprite.sf++;
    else
    {
        sprite.sf = 0;
        sprite.si++;
    }

    if (sprite.si >= sprite.sim)
    {
        if (end_lock)
            sprite.si = sprite.sim - 1;
        else
            sprite.si = 0;

        if (sprite.srm)
        {
            sprite.sr++;
            if (sprite.sr >= sprite.srm)
            {
                sprite.sr = sprite.srr - 1;
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