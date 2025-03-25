#include "GameActor.h"
#include "BulletActionComponent.h"
#include "CollisionCOmponent.h"

BulletActionComponent::BulletActionComponent(GameActor * _gActor) :
	Component(_gActor, "BulletActionComponent")

{
	gActor_->drawfunc = std::bind(&BulletActionComponent::draw, this);
}

BulletActionComponent::~BulletActionComponent()
{
}


void BulletActionComponent::update() {}

void BulletActionComponent::draw() {
	ofSetColor(ofColor::white);
	ofDrawRectangle(-6, -3, 12, 6);
	ofDrawCircle(6, 0, 0, 2);
}

void BulletActionComponent::onCollision(CollisionComponent* _other)
{
	gActor_->waitforErase_ = true;
}