#pragma once
#include "ofMain.h"

class GameActor;

class Component
{
private:
	string	componentName_;

protected:
	GameActor* gActor_;

public:
	virtual void update() = 0;		// èÉêàâºëzä÷êî
	Component(GameActor* _gactor, string _name = "")
		: gActor_(_gactor)
		, componentName_(_name)
	{};
	virtual ~Component() {
	};
	string getComponentName() {
		return componentName_;
	};
	GameActor* gActor() {
		return gActor_;
	}
};
