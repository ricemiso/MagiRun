#include "OutScreenCheckComponent.h"
#include "GameActor.h"

OutScreenCheckComponent::OutScreenCheckComponent(GameActor* _gActor)
	: Component(_gActor, "OutScreenCheckComponent")
{
}

OutScreenCheckComponent::~OutScreenCheckComponent()
{}

void OutScreenCheckComponent::update()
{
	auto pos = gActor_->WorldPos();

	// 画面外に出たら、消去する
	if (pos.x < 0 || pos.x > ofGetViewportWidth() ||
		pos.y < 0 || pos.y > ofGetViewportHeight()) {
		gActor_->waitforErase_ = true;		// 消去
	}
}
