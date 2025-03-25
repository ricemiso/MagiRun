#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent;
class AnimSeq;

class AnimationComponent : public Component
{
private:
	SpriteComponent* sprCpnt_;	// スプライト・コンポーネント
	AnimSeq* animSeq_;			// アニメーションシーケンス
	int nowIdx_;				// 現在のコマのインデックス
	int remainTime_;			// 次のコマまでの残り時間（フレーム数）
public:
	AnimationComponent(GameActor * _gActor);
	virtual ~AnimationComponent();
	void initialize(AnimSeq* _animSeq);
	virtual void update();
	void setNextSprite(int _idx);
};

