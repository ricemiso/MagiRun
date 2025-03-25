#include "ofApp.h"
#include "GameActor.h"
#include "PlayerAction.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "TileMapComponent.h"
#include "GameMainCtrlComponent.h"
#include "GameState.h"

PlayerAction::PlayerAction(GameActor* _gActor)
	: Component(_gActor, "PlayerAction")
	, animCpnt_(nullptr)
	, moveCpnt_(nullptr)
	, shootInterval_(0)
	, hitState_(false)
	, isscale_(false)
	, hasJumped(false)
	, delayCounter_(60)
	, jumpTimer(120.0f)
	, lastcomeSceneTime_(std::chrono::steady_clock::now())
	
	
{
}

void PlayerAction::initialize(GameActor* _parent)
{
	auto app = ofApp::getInstance();

	// コンポーネント
	gActor_->addComponent<SpriteComponent>();
	animCpnt_ = gActor_->addComponent<AnimationComponent>();
	animCpnt_->initialize(app->animSeqManager_->getContents("AnimSeqIdle.json"));
	moveCpnt_ = gActor_->addComponent<MovementComponent>();
	auto colideCpn = gActor_->addComponent<CollisionComponent>();
	
	colideCpn->onCollisionFunc_ = std::bind(&PlayerAction::onCollision,
		this, std::placeholders::_1);
	// マップコライド
	mapCollide_ = gActor_->addComponent<MapCollideComponent>();
	mapCollide_->initialize(_parent->getComponent<TileMapComponent>());

	

	if (app->gameMainCtrlCpnt_->gameState_ == &GameMainCtrlComponent::gameStateMainRPG_)
	{
		gActor_->initialize(app->gameMainCtrlCpnt_->gameState_->playerPosition_, "Player");
		gActor_->Scale() = { 0.5f, 0.5f };
		mapCollide_->setCollideType(1, true);
		mapCollide_->setCollideType(8, true);
		//mapCollide_->setCollideType(7, true);
		colideCpn->initialize({ 0, -15.0f }, 25.0f, 25.0f, PLAYER_OBJECT);
	}
	else
	{
		gActor_->initialize({ 370, 570 }, "Player");
		mapCollide_->setCollideType(58, true);
		mapCollide_->setCollideType(3, true);
		mapCollide_->setCollideType(1, true);
		colideCpn->initialize({ 0, -30.0f }, 50.0f, 60.0f, PLAYER_OBJECT);
	}
	
	hasJumped = false;
}

void PlayerAction::update()
{

	auto app = ofApp::getInstance();
	auto input = app->inputManager_.get();
	auto animeResMgr = app->animSeqManager_.get();
	auto isnowmain = app->gameMainCtrlCpnt_->gameState_ == &GameMainCtrlComponent::gameStateMain_;
	int xaxis = input->getAxis("Horz");
	int yaxis = input->getAxis("Vert");

	if (app->gameMainCtrlCpnt_->gameState_ == &GameMainCtrlComponent::gameStateGameOver_) return;

	if (hitState_) {
		xaxis = yaxis = 0;
	}

	static string currentAnim;

	// 1. ジャンプアニメーション
	if (input->getButtonDown("Jump") && mapCollide_->checkObstacle(MapCollideComponent::DOWN) && isnowmain) {
		if (currentAnim != "AnimSeqJump.json") {
			animCpnt_->initialize(animeResMgr->getContents("AnimSeqJump.json"));
			currentAnim = "AnimSeqJump.json";
		}
	}
	// 2. 落下アニメーション（ジャンプ中 or 地面にいないなら）
	else if (hasJumped && !mapCollide_->checkObstacle(MapCollideComponent::DOWN)) {
		if (currentAnim != "AnimSeqJumpFall.json") {
			animCpnt_->initialize(animeResMgr->getContents("AnimSeqJumpFall.json"));
			currentAnim = "AnimSeqJumpFall.json";
		}
	}
	// 3. 移動アニメーション（左右移動）
	else if (xaxis != 0 || yaxis != 0) {
		if (currentAnim != "AnimSeqRun.json") {
			animCpnt_->initialize(animeResMgr->getContents("AnimSeqRun.json"));
			currentAnim = "AnimSeqRun.json";
		}
	}
	// 4. ダメージアニメーション（被ダメージ時）
	else if (hitState_) {
		if (currentAnim != "AnimSeqDead.json") {
			animCpnt_->initialize(animeResMgr->getContents("AnimSeqDead.json"));
			currentAnim = "AnimSeqDead.json";
		}
	}
	// 5. 待機アニメーション（どの条件にも当てはまらない場合）
	else {
		if (currentAnim != "AnimSeqIdle.json") {
			animCpnt_->initialize(animeResMgr->getContents("AnimSeqIdle.json"));
			currentAnim = "AnimSeqIdle.json";
		}
	}


	if (app->gameMainCtrlCpnt_->gameState_ == &GameMainCtrlComponent::gameStateMainRPG_)
	{
		moveCpnt_->setMoveVec({ xaxis * 2.0f, yaxis * 2.0f, 0.0f });
	}
	else
	{
		moveCpnt_->setMoveVec({ xaxis * 2.0f, moveCpnt_->MoveVec().y, 0.0f });

		
	}
	
	if (xaxis > 0) {
		if (isnowmain) {
			gActor_->Scale() = { 1.0f, 1.0f };
		}
		else
		{
			gActor_->Scale() = { 0.5f, 0.5f };
		}

	}
	else if (xaxis < 0) {
		if (isnowmain) {
			gActor_->Scale() = { -1.0f, 1.0f };
		}
		else
		{
			gActor_->Scale() = { -0.5f, 0.5f };
		}
	}

	// ジャンプ処理
	if (isnowmain) {
		if (input->getButtonDown("Jump") && mapCollide_->checkObstacle(MapCollideComponent::DOWN)) {
			moveCpnt_->MoveVec().y = -17.0f;
			moveCpnt_->Accele().y = 0.5f;
			jumpTimer = 120.0f;
			app->soundManager_->play(SE_JUMP);
			hasJumped = true;
		}
		else {
			// ジャンプ中はタイマーを減少
			if (jumpTimer > 0.0f) {
				--jumpTimer;  // ジャンプタイマーを減少させる
			}

			// もしジャンプタイマーが終了したら、落下処理を開始
			if (jumpTimer <= 0.0f) {
				if (!mapCollide_->checkObstacle(MapCollideComponent::DOWN)) {
					moveCpnt_->Accele().y += 0.5f;  // 加速度を増やして重力を適用
					moveCpnt_->MoveVec().y += moveCpnt_->Accele().y; // 加速度を速度に反映
				}
				else {
					moveCpnt_->MoveVec().y = 0;  // 地面に着いたら落下を停止
					moveCpnt_->Accele().y = 0;   // 加速度をリセット
				}
			}
		}
	}

	// 天井に接触したら即座に落下を開始
	if (mapCollide_->checkObstacle(MapCollideComponent::UP)) {
		moveCpnt_->MoveVec().y = 0.5f;  // 落下を強制的に開始
		moveCpnt_->Accele().y = 0.5f;   // 加速度をリセットせずに適用
		jumpTimer = 0.0f;  // ジャンプ状態を終了
	}

		// 歩数カウント
		static int walkCount = 0;
		if (xaxis != 0 || yaxis != 0) {
			walkCount++;
		}

		if (walkCount >= 15) {
			if (app->gameMainCtrlCpnt_->gameState_ == &GameMainCtrlComponent::gameStateMainRPG_) {
				if (ofRandom(1.0f) < 0.1f) { // 10%の確率でシーン移行
					resetAnimation();
					deleteBullet();
					app->gameMainCtrlCpnt_->ScenemoveCnt_ = 0;
					app->gameMainCtrlCpnt_->gameState_->exit(); // 現在のシーンをexit
					app->gameMainCtrlCpnt_->gameState_ = &GameMainCtrlComponent::gameStateMain_;
					hitState_ = false;
					app->gameMainCtrlCpnt_->gameState_->playerPosition_ = gActor_->WorldPos();
					lastcomeSceneTime_ = std::chrono::steady_clock::now();
					app->gameMainCtrlCpnt_->gameState_->enter();

				}
			}
			walkCount = 0; // 歩数リセット
		}


		if (shootInterval_ <= 0) {
			if (app->inputManager_->getButton("Fire") && isnowmain) {
				float bulletOffsetX = (gActor_->Scale().x > 0) ? 50.0f : -50.0f;
				float bulletAngle = (gActor_->Scale().x > 0) ? 0.0f : 180.0f; // 右向きなら0度、左向きなら180度
				ofVec3f bulletPosition = gActor_->WorldPos() + ofVec3f(bulletOffsetX, -25.0f, 0.0f);
				app->hierarchyRoot_->addChild()->createPlayerBullet(app->hierarchyRoot_.get(), bulletPosition, bulletAngle, 5.0f, "PlayerBullet");
				shootInterval_ = 4;
				app->soundManager_->play(SE_SHOT);
				app->soundManager_->setVolume(SE_SHOT, 2);
			}
		}
		else {
			shootInterval_ -= 1;
		}

		if (ofApp::getInstance()->inputManager_->getButtonDown("Bomb") && isnowmain && app->gameMainCtrlCpnt_->bombcnt_ >= 1) {
			deleteBullet();
			app->soundManager_->play(SE_BOMB);
			app->soundManager_->setVolume(SE_BOMB, 3);

			app->gameMainCtrlCpnt_->bombcnt_--;
		}


		// 死亡アニメーションを見るための遅延カウントダウン
		if (delayCounter_ > 0 && hitState_) {
			delayCounter_--;
			if (delayCounter_ == 0) {
				changeMainRPGScene();
			}
			return;
		}

		// 20秒立つとステージ切替
		auto now = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastcomeSceneTime_).count();
		if (duration >= 20&& isnowmain) {
			app->gameMainCtrlCpnt_->battlecountr_ += 1;
			changeMainRPGScene();
			lastcomeSceneTime_ = now; // タイマーをリセット
		}

		//ゴール判定
		if (mapCollide_->getTileNum(gActor_->WorldPos()) == 7) {
			auto app = ofApp::getInstance();
			app->gameMainCtrlCpnt_->gameState_->exit(); // 現在のシーンをexit
			app->gameMainCtrlCpnt_->gameState_ = &GameMainCtrlComponent::gameStateGameClear_;
			app->gameMainCtrlCpnt_->gameState_->enter();
		}

		if (mapCollide_->getTileNum(gActor_->WorldPos()) == 2) {
			app->soundManager_->play(SE_HEAL);
			app->soundManager_->setVolume(SE_HEAL, 3);
			app->gameMainCtrlCpnt_->playerLife_ = 5;
		}

}

void PlayerAction::onCollision(CollisionComponent* _other)
{
	auto app = ofApp::getInstance();
	hitState_ = true;
	app->gameMainCtrlCpnt_->playerLife_ -= 1;

	if (app->gameMainCtrlCpnt_->playerLife_ <= 0) {
		app->gameMainCtrlCpnt_->isGameover_ = true;
	}
	app->soundManager_->play(1);
}

void PlayerAction::resetAnimation()
{
	static string currentAnim = "";
}

void PlayerAction::deleteBullet()
{
	auto bullets = GameActor::findActors(ofApp::getInstance()->hierarchyRoot_.get(), "EnemyBullet");

	for (auto bullet : bullets) {
		bullet->waitforErase_ = true;
	}
}

void PlayerAction::changeMainRPGScene()
{
	auto app = ofApp::getInstance();

	resetAnimation();
	deleteBullet();
	app->gameMainCtrlCpnt_->gameState_->exit(); // 現在のシーンをexit
	
	app->gameMainCtrlCpnt_->gameState_ = &GameMainCtrlComponent::gameStateMainRPG_;
	app->gameMainCtrlCpnt_->ScenemoveCnt_ = 0;
	app->gameMainCtrlCpnt_->gameState_->enter();

	delayCounter_ = 60;
}

void PlayerAction::powerup()
{

}
