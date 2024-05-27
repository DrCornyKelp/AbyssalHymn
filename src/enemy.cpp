#include <enemy.h>
#include <player.h>
#include <map.h>

Enemy::Enemy(float X, float Y, float w, float h, int hw, int hh,
			int sw, int sh, int sim, int sfm) :
    Object2D({X, Y, w, h, hw, hh}, {sw, sh, sim, sfm})
{}

void Enemy::initEnemy() {}
void Enemy::draw(Player *player) {}
void Enemy::enemyAI(Map *map) {}
void Enemy::enemyGetHit(int dmg) {}

void Enemy::updateEnemy(Map *map) { enemyAI(map); }

// Getter
int Enemy::getHp() { return hp; };
bool Enemy::getDead() { return dead; };
int Enemy::getInvinTime() { return invincible_time; };
int Enemy::getCollideDamage() { return collide_damage; };

// Setter
void Enemy::setHp(int h) { hp = h; };
void Enemy::setDead(bool d) { dead = d; };
void Enemy::setInvinTime(int time) { invincible_time = time; };
void Enemy::setCollideDamage(int dmg) { collide_damage = dmg; };