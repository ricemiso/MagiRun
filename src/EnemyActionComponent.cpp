#include "ofApp.h"
#include "EnemyActionComponent.h"
#include "GameActor.h"
#include "Bullet.h"
#include "GameMainCtrlComponent.h"

EnemyActionComponent::EnemyActionComponent(GameActor* _gactor) :
	Component(_gactor, "EnemyAction"), 
	incoming_(this),
	shooting_(this),
	outgoing_(this),
	state_(&incoming_),
	lastCollisionTime_(std::chrono::steady_clock::now()),
	levelupcuntup_(5)
{
	gActor_->drawfunc = [&]() {
		ofSetColor(ofColor::green);
		ofDrawRectangle(ofVec3f(-15, -15), 30, 30);
	};
	state_->enter();
}

EnemyActionComponent::~EnemyActionComponent() {
}

void EnemyActionComponent::update() {
	auto res = state_->update();
	if (res != nullptr) {
		state_->exit();
		state_ = res;
		state_->enter();
	}

	//if ((flamecnt % 4) == 0) {
	//	shot(flamecnt % 360);
	//}
	//flamecnt += 1;
}

void EnemyActionComponent::shot(float _angle) {
	//ofApp::getInstance()->addActor<Bullet>()->initialize(gActor_->Pos(), _angle);
	ofApp::getInstance()->hierarchyRoot_->addChild()->createBullet(ofApp::getInstance()->hierarchyRoot_.get(),gActor_->Pos(), _angle, "EnemyBullet");
		
}

void EnemyActionComponent::dead()
{
	state_->exit();
	state_ = &incoming_;
	state_->enter();
	ofApp::getInstance()->soundManager_->play(3);
}

void EnemyActionComponent::onCollision(CollisionComponent* _other)
{
	auto app = ofApp::getInstance();
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime_).count();
	if (duration < 300) {
		return; 
	}

	app->gameMainCtrlCpnt_->ScenemoveCnt_ += 1;
	app->gameMainCtrlCpnt_->playerScore_ -= 1;
	app->soundManager_->play(SE_ENEMYLOST);
	app->soundManager_->setVolume(SE_ENEMYLOST, 3);
	
	if (app->gameMainCtrlCpnt_->playerScore_ == 0) {
		app->gameMainCtrlCpnt_->playerScore_ = 10+ levelupcuntup_;
		levelupcuntup_ += 5;
	}
	dead();

	lastCollisionTime_ = now;
}