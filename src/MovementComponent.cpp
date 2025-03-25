#include "MovementComponent.h"
#include "GameActor.h"

MovementComponent::MovementComponent(GameActor* _gActor)
	: Component(_gActor, "MovementComponent")
	, movevec_()
	, accele_()
{}

MovementComponent::~MovementComponent()
{}

void MovementComponent::update()
{
	gActor_->Pos() += movevec_;
	movevec_ += accele_;
}

void MovementComponent::setMoveVec(ofVec3f _vec)
{
	movevec_ = _vec;
}

ofVec3f MovementComponent::getMoveVec()
{
	return movevec_;
}

void MovementComponent::setAccele(ofVec3f _acc)
{
	accele_ = _acc;
}

void MovementComponent::setAngle(float _degree, float _speed)
{
	setMoveVec({
		cosf(ofDegToRad(_degree)) * _speed,
		-sinf(ofDegToRad(_degree)) * _speed,
		0
	});
}
