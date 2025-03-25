#pragma once
#include "Component.h"

class CollisionComponent;

class BulletActionComponent : public Component
{
private:
public:
	BulletActionComponent(GameActor* _gActor);
	virtual ~BulletActionComponent();
	virtual void update();
	void draw();

	void onCollision(CollisionComponent* _other);
};

