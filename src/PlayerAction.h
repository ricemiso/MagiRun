#pragma once
#include "Component.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "MapCollideComponent.h"

class PlayerAction : public Component
{
protected:
	AnimationComponent* animCpnt_;
	MovementComponent* moveCpnt_;
	MapCollideComponent* mapCollide_;

	int  shootInterval_;
	int delayCounter_;
	std::chrono::steady_clock::time_point lastcomeSceneTime_;

public:
	PlayerAction(GameActor* _gActor);
	virtual ~PlayerAction() {};
	virtual void update();

	void initialize(GameActor* _parent);

	virtual void onCollision(CollisionComponent* _other);
	void resetAnimation();
	void deleteBullet();
	void changeMainRPGScene();
	void powerup();

	bool hitState_;
	bool isscale_;
	float jumpTimer;
	bool hasJumped;
	

};

