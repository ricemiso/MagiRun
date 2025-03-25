#include "CollisionManager.h"
#include "GameActor.h"
#include "CollisionComponent.h"

bool CollisionManager::CollisionMatrix[CollisionTypeMax][CollisionTypeMax] = {
	// DEFAULT, PLAYER, P_BULLET, ENEMY, E_BULLET
	{true,      true,   true,     true,  true},		// DEFAULT
	{true,      false,  false,    true,  true},		// PLAYER
	{true,      false,  false,    true,  false},	// P_BULLET
	{true,      true,   true,     false, false},	// ENENY
	{true,      true,   false,    false, false},	// E_BULLET
};


CollisionManager::CollisionManager()
	: isDebug_(IS_DEBUG)
{
	objpool_.reserve(1000);
}

CollisionManager::~CollisionManager()
{
}

CollisionObj* CollisionManager::getObj(CollisionComponent* _ccpnt)
{
	auto res = make_unique<CollisionObj>(_ccpnt);
	auto ptr = res.get();

	objpool_.push_back(move(res));

	//wstringstream ss;
	//ss << objpool_.size() << endl;
	//OutputDebugString(ss.str().c_str());
	return ptr;
}

void CollisionManager::releaseObj(CollisionObj* _target)
{
	auto res = find_if(objpool_.begin(), objpool_.end(),
		[&](const auto& c) {return c.get() == _target; });

	// 検索した結果、存在しなければ処理を止める
	assert(res != objpool_.end());

	objpool_.erase(res);
}

void CollisionManager::CaluculateCollide()
{
	int poolsize = objpool_.size();

	// 2重ループを用いて、総当たりで当たり判定を行う
	// 最初のループの最後の要素は、すでに全ての相手と判定済みなので処理しない
	// 次のループでは、すでに判定している相手とは処理しない
	for (int i = 0; i < poolsize - 1; i++) {
		for (int j = i + 1; j < poolsize; j++) {
			if (CollisionMatrix[objpool_[i]->ctype_][objpool_[j]->ctype_] &&
				objpool_[i]->checkCollide(*objpool_[j])) {
				// 衝突していたら、双方の CollisionComponent の衝突後の処理を行う
				objpool_[i]->ccpnt_->onCollisionFunc_(objpool_[j]->ccpnt_);
				objpool_[j]->ccpnt_->onCollisionFunc_(objpool_[i]->ccpnt_);
			}
		}
	}
}

// デバッグ描画
void CollisionManager::drawDebug()
{
	if (isDebug_) {
		for (auto& obj : objpool_) {
			obj->draw();
		}
	}
}
