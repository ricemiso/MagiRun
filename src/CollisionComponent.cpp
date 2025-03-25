#include "CollisionComponent.h"
#include "ofApp.h"

CollisionComponent::CollisionComponent(GameActor* _gactor)
	: Component(_gactor, "CollisionComponent")
	, cobj_(ofApp::getInstance()->collisionManager_->getObj(this))
	, offset_(0)
	, onCollisionFunc_([](CollisionComponent*){})
{}

CollisionComponent::~CollisionComponent()
{
	ofApp::getInstance()->collisionManager_->releaseObj(cobj_);
}

void CollisionComponent::initialize(ofVec3f _offset, float _width, float _height, CollisionType _ctype)
{
	offset_ = _offset;
	width_ = _width;
	height_ = _height;
	cobj_->ctype_ = _ctype;
	auto centerOfs = ofVec3f(width_ * 0.5f, height_ * 0.5f);

	cobj_->setCollisionParam(ofRectangle(gActor_->WorldPos() + offset_ - centerOfs, width_, height_));
}

void CollisionComponent::update()
{
	cobj_->setCollisionParam(calcRect());
}


ofRectangle CollisionComponent::calcRect()
{
	gActor_->caluclateWorldTransform();

	auto centerOfs = ofVec3f(width_ * 0.5f, height_ * 0.5f);
	return ofRectangle(gActor_->WorldPos() + offset_ - centerOfs, width_, height_);
}
