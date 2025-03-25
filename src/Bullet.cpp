#include "Bullet.h"


Bullet::Bullet() : GameActor("Bullet"){}

Bullet::~Bullet() {}

#pragma region Comment out

//#include "MovementComponent.h"
//#include "OutScreenCheckComponent.h"
//#include "CollisionComponent.h"
//#include "BulletActionComponent.h"
//#include "CollisionManager.h"

//void Bullet::initialize(ofVec3f _pos, float _angle)
//{
//	__super::initialize(_pos, "EnemyBullet");
//	movementComponent_ = addComponent<MovementComponent>();
//	outScreenCheckComponent_ = addComponent<OutScreenCheckComponent>();
//	auto coli = addComponent<CollisionComponent>();
//	action_ = addComponent<BulletActionComponent>();
//	
//	coli->initialize({ 0,0 }, 10,10, CollisionType::ENEMY_BULLET);
//	coli->onCollisionFunc_ = std::bind(&BulletActionComponent::onCollision,
//		action_, std::placeholders::_1);
//
//	setAngle(_angle, 1);
//}
//
//void Bullet::initializeForPLayerBullet(ofVec3f _pos, float _angle, float _speed)
//{
//	__super::initialize(_pos, "PlayerBullet");
//	movementComponent_ = addComponent<MovementComponent>();
//	outScreenCheckComponent_ = addComponent<OutScreenCheckComponent>();
//	auto coli = addComponent<CollisionComponent>();
//	action_ = addComponent<BulletActionComponent>();
//	
//	coli->initialize({ 0,0 }, 10,10, CollisionType::PLAYER_BULLET);
//	coli->onCollisionFunc_ = std::bind(&BulletActionComponent::onCollision,
//		action_, std::placeholders::_1);
//
//	setAngle(_angle, _speed);
//}



//void Bullet::setAngle(float _degree, float _speed) {
//	rotAngle_ = _degree;
//	movementComponent_->setMoveVec(
//		{ cosf(ofDegToRad(_degree)) * _speed,-sinf(ofDegToRad(_degree)) * _speed,0 }
//	);
//}

#pragma endregion
