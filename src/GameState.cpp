#include "ofMain.h"
#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "GameMainCtrlComponent.h"
#include "FontRendererComponent.h"


//--------------------------------------------
// ゲームメイン
#include "PlayerAction.h"
#include "TileMapComponent.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "MapCollideComponent.h"

// 開始
void GameStateMain::enter()
{
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();

	// マップ
	auto tileData = app->tileresManager_->getContents("TileDef01.txt");
	auto mapData = app->mapresManager_->getContents("map01.csv");
	auto map = root->addChild();
	map->initialize({ 0, 0 }, "Map");
	map->addComponent<TileMapComponent>()->initialize(tileData, mapData);

	// プレイヤー
	auto player = map->addChild();
	player->addComponent<PlayerAction>()->initialize(map);

	
	int count = app->gameMainCtrlCpnt_->battlecountr_;

	if (count == 1) {
		float x = ofRandom(100, 900);
		float y = ofRandom(100, 700);
		GameActor::createEnemy(root, { x, y }, "Enemy");
	}
	else
	{
		int cnt = ofRandom(2, count);
		for (int i = 0; i < cnt; ++i) {
			float x = ofRandom(100, 900);
			float y = ofRandom(100, 700);
			GameActor::createEnemy(root, { x, y }, "Enemy");
		}
	}

	
	lastBombTime_ = std::chrono::steady_clock::now();


	auto font = root->addChild();
	auto lifefont = root->addChild();
	auto powerupfont = root->addChild();
	fontComponent_ = font->addComponent<FontRendererComponent>();
	lifeFontComponent_ = lifefont->addComponent<FontRendererComponent>();
	fontComponent_->initialize(app->myFont, "BOMB :", { 100,25 }, ofColor::white);
	lifeFontComponent_->initialize(app->myFont, "LIFE :", { 300,25 }, ofColor::white);

	app->soundManager_->loop(BGM_MAIN);
}

// 更新
GameState* GameStateMain::update()
{
	auto app = ofApp::getInstance();

	if (app->gameMainCtrlCpnt_->isGameover_) {
		return &GameMainCtrlComponent::gameStateGameOver_;
	}

	if (app->gameMainCtrlCpnt_->ScenemoveCnt_ > app->gameMainCtrlCpnt_->battlecountr_) {
		app->gameMainCtrlCpnt_->ScenemoveCnt_ = 0;
		app->gameMainCtrlCpnt_->battlecountr_ += 1;
		return &GameMainCtrlComponent::gameStateMainRPG_;
	}

	// 5秒ごとに bombcnt_ をカウントアップ
	auto now = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastBombTime_).count();
	if (duration >= 5) {
		app->gameMainCtrlCpnt_->bombcnt_ += 1;
		lastBombTime_ = now; 
	}

	stringstream ss;
	ss << "BOMB :" << " " << app->gameMainCtrlCpnt_->bombcnt_;
	fontComponent_->String() = ss.str();

	stringstream lss;
	lss << "LIFE :" << " " << app->gameMainCtrlCpnt_->playerLife_;
	lifeFontComponent_->String() = lss.str();

	return nullptr;
}

// 終了
void GameStateMain::exit()
{
	auto app = ofApp::getInstance();
	app->soundManager_->stop(BGM_MAIN);
	ofApp::getInstance()->hierarchyRoot_->removeAllChild();
}

//Main RPG Scene
void GameStateMainRPG::enter()
{
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();

	auto tileData = app->tileres2Manager_->getContents("TileDef02.txt");
	auto mapData = app->mapresManager_->getContents("map02.csv");

	auto map = root->addChild();
	map->initialize({ 0,0 }, "Map");
	map->addComponent<TileMapComponent>()->initialize(tileData, mapData);

	// プレイヤー
	auto player = map->addChild();
	player->addComponent<PlayerAction>()->initialize(map);

	auto font = root->addChild();
	auto lifefont = root->addChild();
	auto powerupfont = root->addChild();
	fontComponent_ = font->addComponent<FontRendererComponent>();
	lifeFontComponent_ = lifefont->addComponent<FontRendererComponent>();
	fontComponent_->initialize(app->myFont, "BOMB :", { 100,25 }, ofColor::white);
	lifeFontComponent_->initialize(app->myFont, "LIFE :", { 300,25 }, ofColor::white);

	app->soundManager_->loop(BGM_MAINRPG);
}

GameState* GameStateMainRPG::update()
{
	auto app = ofApp::getInstance();

	stringstream ss;
	ss << "BOMB :" << " " << app->gameMainCtrlCpnt_->bombcnt_;
	fontComponent_->String() = ss.str();

	stringstream lss;
	lss << "LIFE :" << " " << app->gameMainCtrlCpnt_->playerLife_;
	lifeFontComponent_->String() = lss.str();

	return nullptr;
}

void GameStateMainRPG::exit()
{
	
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();
	auto map = root->getChildByName("Map"); 
	if (map != nullptr) {
		auto player = map->getChildByName("Player");
		if (player != nullptr) {
			playerPosition_ = player->WorldPos();
		}
	}

	app->soundManager_->stop(BGM_MAINRPG);

	ofApp::getInstance()->hierarchyRoot_->removeAllChild();
}

//----------------------------------------------
// ゲームオーバー状態
void GameStateGameOver::enter()
{
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();
	auto actor = root->addChild();
	actor->addComponent<FontRendererComponent>()->
		initialize(app->myFont, "GAME OVER", { 230,100 }, ofColor::red);
	actor->Scale() = { 2.0f, 2.0f };
	auto actor6 = root->addChild();
	actor6->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"Push Space", { 300,450 }, ofColor::white);
	actor6->Scale() = { 1.5f, 1.5f };

	app->gameMainCtrlCpnt_->gameStateMainRPG_.playerPosition_ = { 50, 700, 0 };
	app->soundManager_->loop(BGM_GAMEOVER);
}

GameState* GameStateGameOver::update()
{
	auto app = ofApp::getInstance();
	// Startキーが押されたら、タイトルへ
	if (ofApp::getInstance()->inputManager_->getButtonDown("Start")) {
		app->soundManager_->stop(BGM_GAMEOVER);
		return &GameMainCtrlComponent::gameStateTitle_;
	}
	return nullptr;
}

void GameStateGameOver::exit()
{
	auto app = ofApp::getInstance();
	app->soundManager_->stop(BGM_GAMEOVER);
	ofApp::getInstance()->hierarchyRoot_->removeAllChild();
}

//------------------------------------------------------
// タイトル状態

void GameStateTitle::enter()
{
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();

	auto actor = root->addChild();
	actor->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, "MagiRun", { 230,100 }, ofColor::white);
	actor->Scale() = { 2.0f, 2.0f };

	auto actor2 = root->addChild();
	actor2->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"移動 : WASD", { 480,300 }, ofColor::white);
	actor2->Scale() = { 1.5f, 1.5f };

	auto actor3 = root->addChild();
	actor3->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"ジャンプ : W", { 480,350 }, ofColor::white);
	actor3->Scale() = { 1.5f, 1.5f };

	auto actor4 = root->addChild();
	actor4->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"ショット : SPACE", { 480,400 }, ofColor::white);
	actor4->Scale() = { 1.5f, 1.5f };

	auto actor5 = root->addChild();
	actor5->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, u8"ボム(敵弾の全消去) : E", { 480,450 }, ofColor::white);
	actor5->Scale() = { 1.5f, 1.5f };

	auto actor6 = root->addChild();
	actor6->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, "Push Space", { 300,450 }, ofColor::white);
	actor6->Scale() = { 1.5f, 1.5f };


	app->soundManager_->loop(BGM_TITLE);
	app->gameMainCtrlCpnt_->isGameover_ = false;
	app->gameMainCtrlCpnt_->ScenemoveCnt_ = 0;
	app->gameMainCtrlCpnt_->playerLife_ = 5;
	app->gameMainCtrlCpnt_->bombcnt_ = 0;
	app->gameMainCtrlCpnt_->playerScore_ = 10;
	app->gameMainCtrlCpnt_->battlecountr_ = 1;
}

GameState* GameStateTitle::update()
{
	if (ofApp::getInstance()->inputManager_->getButtonDown("Start")) {

		return &GameMainCtrlComponent::gameStateMainRPG_;
	}

	return nullptr;
}

void GameStateTitle::exit()
{
	auto app = ofApp::getInstance();
	app->soundManager_->stop(BGM_TITLE);
	ofApp::getInstance()->hierarchyRoot_->removeAllChild();
}


//----------------------------------------------
// ゲームクリア状態
void GameStateGameCLEAR::enter()
{
	auto app = ofApp::getInstance();
	auto root = app->hierarchyRoot_.get();
	auto actor = root->addChild();
	actor->addComponent<FontRendererComponent>()->
		initialize(app->myFont, "GAME CLEAR", { 230,100 }, ofColor::red);
	actor->Scale() = { 2.0f, 2.0f };
	auto actor6 = root->addChild();
	actor6->addComponent<FontRendererComponent>()->
		initialize(ofApp::getInstance()->myFont, "Push Space", { 300,450 }, ofColor::white);
	actor6->Scale() = { 1.5f, 1.5f };

	app->gameMainCtrlCpnt_->gameStateMainRPG_.playerPosition_ = { 50, 700, 0 };
	app->soundManager_->loop(BGM_GAMECLEAR);
}

GameState* GameStateGameCLEAR::update()
{
	auto app = ofApp::getInstance();
	// Startキーが押されたら、タイトルへ
	if (ofApp::getInstance()->inputManager_->getButtonDown("Start")) {
		app->soundManager_->stop(BGM_GAMECLEAR);
		return &GameMainCtrlComponent::gameStateTitle_;
	}
	return nullptr;
}

void GameStateGameCLEAR::exit()
{
	auto app = ofApp::getInstance();
	app->soundManager_->stop(BGM_GAMECLEAR);
	ofApp::getInstance()->hierarchyRoot_->removeAllChild();
}
