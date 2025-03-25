#pragma once
#include "CollisionObj.h"

enum CollisionType {
	DEFAULT,
	PLAYER_OBJECT,
	PLAYER_BULLET,
	ENEMY_OBJECT,
	ENEMY_BULLET,
	CollisionTypeMax
};

#define IS_DEBUG  false

class CollisionManager
{
public:
	vector<unique_ptr<CollisionObj>> objpool_;
	bool  isDebug_;		// true = デバッグ描画する

	CollisionManager();
	virtual ~CollisionManager();

	CollisionObj* getObj(CollisionComponent* _ccpnt);
	void releaseObj(CollisionObj* _target);
	void CaluculateCollide();

	// コリジョン・マトリクス・テーブル
	static bool CollisionMatrix[CollisionTypeMax][CollisionTypeMax];

	// デバッグ描画
	void drawDebug();
};

