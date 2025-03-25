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
	// ���݂̃X�e�[�g�̍X�V
	auto res = gameState_->update();

	// �߂�l�Ɏ��̃X�e�[�g���ݒ肳��Ă�����
	if (res != nullptr) {
		// ���݂̃X�e�[�g���I��
		gameState_->exit();
		// ���݂̃X�e�[�g�����̃X�e�[�g��
		gameState_ = res;
		// ���̃X�e�[�g�̊J�n
		gameState_->enter();
	}
}
