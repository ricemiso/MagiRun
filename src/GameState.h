#pragma once
#include "FontRendererComponent.h"

class GameState
{
private:
public:
public:
	GameState() : isbattle_(false), fontComponent_(nullptr), lifeFontComponent_(nullptr), playerPosition_({ 50,700,0 }), 
		 lastBombTime_(std::chrono::steady_clock::now()){
	};
	virtual ~GameState() {};
	virtual void enter() = 0;
	virtual GameState* update() = 0;
	virtual void exit() = 0;

	bool isbattle_;
	FontRendererComponent* fontComponent_;
	FontRendererComponent* lifeFontComponent_;
	
	std::chrono::steady_clock::time_point lastBombTime_;
	ofVec3f playerPosition_;
};

// �o�g�����
class GameStateMain : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

//RPG���
class GameStateMainRPG : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// �Q�[���I�[�o�[
class GameStateGameOver : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// �^�C�g��
class GameStateTitle : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// �Q�[���N���A
class GameStateGameCLEAR : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};
