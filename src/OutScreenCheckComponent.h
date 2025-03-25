#pragma once
#include "Component.h"

class OutScreenCheckComponent : public Component
{
public:
	OutScreenCheckComponent(GameActor* _gActor);
	virtual ~OutScreenCheckComponent();

	void update();
};

