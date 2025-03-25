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

	// スプライトコンポーネントに画像を設定する
	sprCpnt_->setImage(animFrame.image_, animFrame.chipW_, animFrame.chipH_);
	// スプライトコンポーネントにチップ番号を設定する
	sprCpnt_->ChipNo() = animFrame.chipNo_;
	// スプライトコンポーネントにオフセット位置を設定する
	sprCpnt_->Offset() = animFrame.offset_;
	// スプライトコンポーネントに表示・非表示を設定する
	sprCpnt_->Enabled() = animFrame.visible_;
	// 残り時間を設定する
	remainTime_ = animFrame.time_;
}
