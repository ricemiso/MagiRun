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

	// �����������ʁA���݂��Ȃ���Ώ������~�߂�
	assert(res != objpool_.end());

	objpool_.erase(res);
}

void CollisionManager::CaluculateCollide()
{
	int poolsize = objpool_.size();

	// 2�d���[�v��p���āA��������œ����蔻����s��
	// �ŏ��̃��[�v�̍Ō�̗v�f�́A���łɑS�Ă̑���Ɣ���ς݂Ȃ̂ŏ������Ȃ�
	// ���̃��[�v�ł́A���łɔ��肵�Ă��鑊��Ƃ͏������Ȃ�
	for (int i = 0; i < poolsize - 1; i++) {
		for (int j = i + 1; j < poolsize; j++) {
			if (CollisionMatrix[objpool_[i]->ctype_][objpool_[j]->ctype_] &&
				objpool_[i]->checkCollide(*objpool_[j])) {
				// �Փ˂��Ă�����A�o���� CollisionComponent �̏Փˌ�̏������s��
				objpool_[i]->ccpnt_->onCollisionFunc_(objpool_[j]->ccpnt_);
				objpool_[j]->ccpnt_->onCollisionFunc_(objpool_[i]->ccpnt_);
			}
		}
	}
}

// �f�o�b�O�`��
void CollisionManager::drawDebug()
{
	if (isDebug_) {
		for (auto& obj : objpool_) {
			obj->draw();
		}
	}
}
