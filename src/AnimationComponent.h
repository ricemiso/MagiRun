#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent;
class AnimSeq;

class AnimationComponent : public Component
{
private:
	SpriteComponent* sprCpnt_;	// �X�v���C�g�E�R���|�[�l���g
	AnimSeq* animSeq_;			// �A�j���[�V�����V�[�P���X
	int nowIdx_;				// ���݂̃R�}�̃C���f�b�N�X
	int remainTime_;			// ���̃R�}�܂ł̎c�莞�ԁi�t���[�����j
public:
	AnimationComponent(GameActor * _gActor);
	virtual ~AnimationComponent();
	void initialize(AnimSeq* _animSeq);
	virtual void update();
	void setNextSprite(int _idx);
};

