#include "ofApp.h"
#include "AnimationComponent.h"
#include "GameActor.h"
#include "SpriteComponent.h"
#include "AnimSeq.h"

AnimationComponent::AnimationComponent(GameActor* _gActor)
	: Component(_gActor, "AnimationComponent")
	, remainTime_(0)
	, nowIdx_(0)
	, animSeq_(nullptr)
	, sprCpnt_(nullptr)
{}

AnimationComponent::~AnimationComponent()
{}

void AnimationComponent::initialize(AnimSeq* _animSeq)
{
	animSeq_ = _animSeq;

	nowIdx_ = 0;

	sprCpnt_ = gActor_->getComponent<SpriteComponent>();
	assert(sprCpnt_ != nullptr);

	setNextSprite(nowIdx_);
}

void AnimationComponent::update()
{
	if (animSeq_ == nullptr) return;

	--remainTime_;

	if (remainTime_ <= 0) {
		nowIdx_ = animSeq_->getFrame(nowIdx_).next_;
		setNextSprite(nowIdx_);
	}
}

void AnimationComponent::setNextSprite(int _idx)
{
	auto animFrame = animSeq_->getFrame(_idx);

	// �X�v���C�g�R���|�[�l���g�ɉ摜��ݒ肷��
	sprCpnt_->setImage(animFrame.image_, animFrame.chipW_, animFrame.chipH_);
	// �X�v���C�g�R���|�[�l���g�Ƀ`�b�v�ԍ���ݒ肷��
	sprCpnt_->ChipNo() = animFrame.chipNo_;
	// �X�v���C�g�R���|�[�l���g�ɃI�t�Z�b�g�ʒu��ݒ肷��
	sprCpnt_->Offset() = animFrame.offset_;
	// �X�v���C�g�R���|�[�l���g�ɕ\���E��\����ݒ肷��
	sprCpnt_->Enabled() = animFrame.visible_;
	// �c�莞�Ԃ�ݒ肷��
	remainTime_ = animFrame.time_;
}
