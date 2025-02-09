//implementation of the entity class

#include "entity.h"

using namespace std;

Entity::Entity() :
    maxHealth(10),
    health(maxHealth),
    entityType(ET_ROBOT),
    posx(0),
    posy(0),
    speed(1),
    entityMove(moveLeft),
    projectileMove(moveLeft),
    textureID(TX_ROBOT),
    moveStartTime(0),
    moveAway(false)

{
		setHitbox(ET_ROBOT);
#ifdef ENTITYDEBUG
    cout << "Created default entity." << endl;
#endif
}

Entity::Entity(const Entity &entity) :
    maxHealth(maxHealth),
    health(maxHealth),
    entityType(ET_PLAYER),
    posx(posx),
    posy(posy),
    speed(speed),
    entityMove(entityMove),
    projectileMove(projectileMove),
    textureID(textureID)
{
		setHitbox(entityType);
#ifdef ENTITYDEBUG
    cout << "Created entity from copy." << endl;
#endif
}

Entity::~Entity(void) {
    // todo
}

Entity::Entity(int health, EntityType entityType,
                double x, double y, double speed, moveEntityFunc entityMove,
                moveProjectileFunc projectileMove,
                TextureID textureID) :
    maxHealth(health),
    health(health),
    entityType(entityType),
    posx(x),
    posy(y),
    speed(speed),
    entityMove(entityMove),
    projectileMove(projectileMove),
    textureID(textureID)
{
		setHitbox(entityType);
#ifdef ENTITYDEBUG
    cout << "Created entity with custom stats." << endl;
    cout << "Type is: " << (entityType == ET_PLAYER ? "player" : "npc") << endl;
    cout << "Position: " << posx << ", " << posy << endl;
    cout << "speed: " << speed << endl;
#endif
}


Position Entity::getPosition()
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    return pos;
}

int Entity::getHealth()
{
    return health;
}

TextureID Entity::getImage()
{
    return textureID;
}

EntityType Entity::getType()
{
    return entityType;
}

void Entity::setHitbox(EntityType ID){

    if(ID == ET_PROJECTILE){
			hitbox.h = 5;
			hitbox.w = 5;
		}
		else{
			hitbox.h = 25;
			hitbox.w = 25;
		}
}
void Entity::setHitboxPos(Position entity){

			hitbox.x = entity.x;
			hitbox.y = entity.y;
}

SDL_Rect * Entity::getHitbox(){
	return &hitbox;
}
bool Entity::entityCollision(SDL_Rect * a){
	return SDL_HasIntersection(a, &this->hitbox);
}
/*
void Entity::move(Movement &dir)
{
#ifdef ENTITYDEBUG
    bool printSecondHalfOfDebug;
    if (dir.right || dir.left || dir.up || dir.down)  //only print if its going to move
    {
        cout << "Moved entity from (" << posx << ", " << posy;
        printSecondHalfOfDebug = true;
    }
#endif
    Position pos = entityMove(posx, posy, dir, speed);
    posx = pos.x;
    posy = pos.y;

    moveDirection = dir;
#ifdef ENTITYDEBUG
    if (printSecondHalfOfDebug)
        cout << ") to (" << posx << ", " << posy << ") \n";
#endif
}
*/

Position Entity::testMove(Movement &dir)
{
    return entityMove(posx, posy, dir, speed);
}

bool Entity::damage(int amount)
{
    health -= amount;
#ifdef ENTITYDEBUG
        cout << "Entity took " << amount << " damage. " << endl;
#endif
    if (health <= 0)
    {
#ifdef ENTITYDEBUG
        cout << "Entity died." << endl;
#endif
        return true;
    }
    else
        return false;
}

void Entity::setLocation(Position &newPos){
    posx = newPos.x;
    posy = newPos.y;
}
