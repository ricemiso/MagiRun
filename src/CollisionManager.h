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
	bool  isDebug_;		// true = �f�o�b�O�`�悷��

	CollisionManager();
	virtual ~CollisionManager();

	CollisionObj* getObj(CollisionComponent* _ccpnt);
	void releaseObj(CollisionObj* _target);
	void CaluculateCollide();

	// �R���W�����E�}�g���N�X�E�e�[�u��
	static bool CollisionMatrix[CollisionTypeMax][CollisionTypeMax];

	// �f�o�b�O�`��
	void drawDebug();
};

