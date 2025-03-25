#pragma once
#include "GameActor.h"

//class MovementComponent;
//class OutScreenCheckComponent;
//class CollisionComponent;
//class BulletActionComponent;

class Bullet : public GameActor
{
private:
	/*MovementComponent* movementComponent_;
	OutScreenCheckComponent* outScreenCheckComponent_;
	CollisionComponent* collisionComponent_;
	BulletActionComponent* action_;*/

public:
	Bullet();
	virtual ~Bullet();

	//void initialize(ofVec3f _pos, float _angle);
	//void initializeForPLayerBullet(ofVec3f _pos, float _angle, float _speed);
	//void setAngle(float _degree, float _speed = 1);
};

