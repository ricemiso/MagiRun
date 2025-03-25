#pragma once
#include "Component.h"
#include "CollisionManager.h"

class GameActor;
class CollisionObj;

class CollisionComponent : public Component
{
private:
	CollisionObj* cobj_;
	float	width_, height_;
	ofVec3f	offset_;

public:
	CollisionComponent(GameActor* _gactor);
	virtual ~CollisionComponent();
	virtual void update();
	void initialize(ofVec3f _offset, float _width, float _height, CollisionType _ctype = CollisionType::DEFAULT);

	ofRectangle calcRect();

	std::function<void(CollisionComponent* _other)> onCollisionFunc_;
};

