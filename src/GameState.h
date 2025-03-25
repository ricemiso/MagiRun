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

// バトル画面
class GameStateMain : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

//RPG画面
class GameStateMainRPG : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// ゲームオーバー
class GameStateGameOver : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// タイトル
class GameStateTitle : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};

// ゲームクリア
class GameStateGameCLEAR : public GameState {
public:
	virtual void enter();
	virtual GameState* update();
	virtual void exit();
};
