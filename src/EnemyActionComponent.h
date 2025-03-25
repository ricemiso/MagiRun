#pragma once
#include "Component.h"
#include "EnemyAction01State.h"
#include "CollisionCOmponent.h"

class GameActor;

class EnemyActionComponent : public Component
{
	friend class EnemyAct01StateIncoming;
	friend class EnemyAct01StateShooting;
	friend class EnemyAct01StateOutgoing;
private:
	EnemyAct01StateIncoming incoming_;
	EnemyAct01StateShooting shooting_;
	EnemyAct01StateOutgoing outgoing_;

	EnemyAction01State* state_;
	std::chrono::steady_clock::time_point lastCollisionTime_;
	int levelupcuntup_;

public:
	EnemyActionComponent(GameActor* _gactor);
	virtual ~EnemyActionComponent();
	virtual void update();
	void shot(float _angle);
	void dead();
	virtual void onCollision(CollisionComponent* _other);

};

