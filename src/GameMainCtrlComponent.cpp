#include "ofMain.h"
#include "GameActor.h"
#include "GameMainCtrlComponent.h"
#include "GameState.h"

GameStateTitle GameMainCtrlComponent::gameStateTitle_;
GameStateMain GameMainCtrlComponent::gameStateMain_;
GameStateGameOver GameMainCtrlComponent::gameStateGameOver_;
GameStateMainRPG GameMainCtrlComponent::gameStateMainRPG_;
GameStateGameCLEAR GameMainCtrlComponent::gameStateGameClear_;


GameMainCtrlComponent::GameMainCtrlComponent(GameActor* _gActor)
	:Component(_gActor, "GameMainCtrlComponent")
, gameState_(&gameStateTitle_)
, isGameover_(false)
, ScenemoveCnt_(0)
, playerLife_(5)
, bombcnt_(0)
, battlecountr_(1)
, playerScore_(10)
{}

GameMainCtrlComponent::~GameMainCtrlComponent()
{}

void GameMainCtrlComponent::gameStateStart()
{
	gameState_ = &gameStateTitle_;
	gameState_->enter();
}

void GameMainCtrlComponent::update()
{
	// 現在のステートの更新
	auto res = gameState_->update();

	// 戻り値に次のステートが設定されていたら
	if (res != nullptr) {
		// 現在のステートを終了
		gameState_->exit();
		// 現在のステートを次のステートに
		gameState_ = res;
		// 次のステートの開始
		gameState_->enter();
	}
}
