#include "ofApp.h"
#include "Enemy.h"

Enemy::Enemy() : GameActor("Enemy"){}

Enemy::~Enemy(){}

#pragma region Comment out
//#include "GameActor.h"
//#include "Bullet.h"
//#include "EnemyActionComponent.h"
//#include "CollisionCOmponent.h"
//#include "GameMainCtrlComponent.h"

//void Enemy::initialize(ofVec3f _pos)
//{
//	__super::initialize(_pos,"Enemy");
//	enemyActionComponent_ = addComponent<EnemyActionComponent>();
//	auto coli = addComponent<CollisionComponent>();
//	coli->initialize({ 0,0 }, 10, 10, CollisionType::ENEMY_OBJECT);
//	coli->onCollisionFunc_ = std::bind(&EnemyActionComponent::onCollision,
//		enemyActionComponent_, std::placeholders::_1);
//
//}

#pragma endregion