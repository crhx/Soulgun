

#include "humanoid.h"


using namespace std;

Humanoid::Humanoid() :
    Entity(),
    shootCooldown(0),
    shootTimer(10)
{
}

Humanoid::Humanoid(const Humanoid &humanoid) :
    Entity(humanoid),
    shootCooldown(0),
    shootTimer(shootTimer)
{
}

Humanoid::Humanoid(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID) :
    Entity(health, entityType, x, y, speed, entityMove, projectileMove, textureID),
    shootCooldown(0),
    shootTimer(shootTimer) 
{
}

Humanoid::~Humanoid()
{
    //todo
}

//slightly unfinished, may not need to be finished
Projectile ** Humanoid::shoot(int targetx, int targety, bool soulBullet)
{
    double aimDirection = atan2((targety-posy), (targetx-posx));
    int texture = (soulBullet ? TX_BULLET : TX_BULLET);
    int lifetime = 100;
    int power = 1;
    Projectile ** proj = nullptr;
    if (shootCooldown <= 0)
    {
        switch (shootStyle)
        {
            case SS_SINGLESHOT:
                proj = new Projectile*[1];
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_DOUBLESHOT:
                proj = new Projectile*[2];
                aimDirection -= M_PI/8;
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/4;
                proj[1] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_TRIPLESHOT:
                proj = new Projectile*[3];
                aimDirection -= M_PI/6;
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/6;
                proj[1] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/6;
                proj[2] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_4WAY:
                break;
            case SS_4WAYTILT:
                break;
            case SS_8WAY:
                break;
            case SS_SPIRAL:
                break;
            default:
                break;
        }
        shootCooldown = shootTimer;
    }
    return proj;
}




