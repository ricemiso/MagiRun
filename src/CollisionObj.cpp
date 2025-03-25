#include "CollisionManager.h"
#include "CollisionObj.h"
#include "CollisionComponent.h"

CollisionObj::CollisionObj(CollisionComponent* _ccpnt)
	: rect_(ofRectangle())
	, ccpnt_(_ccpnt)
	, ctype_(CollisionType::DEFAULT)
{}

bool CollisionObj::checkCollide(const CollisionObj& _other) const
{
	return rect_.intersects(_other.rect_);
}


void CollisionObj::setCollisionParam(ofRectangle _rect)
{
	rect_ = _rect;
}

// デバッグ描画
void CollisionObj::draw()
{
	ofSetColor(ofColor::red);
	ofNoFill();
	ofDrawRectangle(rect_);
	ofFill();
}