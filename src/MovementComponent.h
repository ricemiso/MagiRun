#pragma once
#include "Component.h"

class MovementComponent : public Component
{
private:
	ofVec3f movevec_;		// 移動ベクトル
	ofVec3f accele_;		// 加速度
public:
	MovementComponent(GameActor* _gActor);
	virtual ~MovementComponent();
	virtual void update();
	void setMoveVec(ofVec3f _vec);
	ofVec3f getMoveVec();
	void setAccele(ofVec3f _acc);
	void setAngle(float _degree, float _speed);

	ofVec3f& MoveVec() { return movevec_; }
	ofVec3f& Accele() { return accele_; }
};

