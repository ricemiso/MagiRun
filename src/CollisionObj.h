#pragma once
#include "ofMain.h"

//class GameActor;
enum CollisionType;
class CollisionComponent;

class CollisionObj
{
private:
	ofRectangle		rect_;

public:
	CollisionObj(CollisionComponent* _ccpnt);
	virtual ~CollisionObj() {};

	bool checkCollide(const CollisionObj& _other) const;
	void setCollisionParam(ofRectangle _rect);

	CollisionType  ctype_;	// コリジョン種別
	CollisionComponent* ccpnt_;

	// デバッグ描画
	void draw();
};
