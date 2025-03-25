#include "ofMain.h"
#include "EnemyAction01State.h"
#include "Enemy.h"
#include "EnemyActionComponent.h"
#include "ofApp.h"
#include "GameMainCtrlComponent.h"
#include "GameState.h"

void EnemyAct01StateIncoming::enter()
{
	//belongTo_->gActor()->Pos() = ofVec3f(ofRandom(500) + 50, -200 + ofRandom(30), 0);
	belongTo_->gActor()->Pos() = ofVec3f(ofRandom(900) + 50, -200 + ofRandom(30), 0);

}

EnemyAction01State * EnemyAct01StateIncoming::update()
{
	belongTo_->gActor()->Pos() += ofVec3f(0, 5, 0);
	if (belongTo_->gActor()->Pos().y >= 300) {
		belongTo_->gActor()->Pos().y = 300;
		return &belongTo_->shooting_;
	}
	return nullptr;
}

void EnemyAct01StateIncoming::exit()
{
}

void EnemyAct01StateShooting::enter()
{
	shootingtime = 0;
	movDir = ofVec3f(0, 5, 0); // 初期の移動方向を下に設定
	changeDirTime = 0; // 方向変更のカウンタを初期化

}

EnemyAction01State * EnemyAct01StateShooting::update()
{
	auto app = ofApp::getInstance();
	/*shootingtime += 1;
	if ((shootingtime % 4) == 0) {
		belongTo_->shot(((shootingtime * 4) % 360) + 270);
	}
	if (shootingtime >= 120) {
		return &belongTo_->outgoing_;
	}*/

	shootingtime += 1;

	// battlecountr が大きくなるほど、弾の数を増やす
	int bulletCount = std::max(1, app->gameMainCtrlCpnt_->battlecountr_);  // battlecountr が大きいほど弾の数を増やす

	int interval = std::max(1, 30 - bulletCount);  // 間隔を battlecountr に応じて調整

	if ((shootingtime % interval) == 0) {  // 新しい発射間隔
		// 弾を発射する角度を計算
		belongTo_->shot(((shootingtime * 4) % 360) + 270);
	}


	// ランダムに動き続ける
	belongTo_->gActor()->Pos() += movDir;

	// 画面端に達した場合や一定時間ごとに方向を変更
	if (changeDirTime >= 120 || belongTo_->gActor()->Pos().x <= 0 || belongTo_->gActor()->Pos().x >= ofGetWidth() ||
		belongTo_->gActor()->Pos().y <= 10 || belongTo_->gActor()->Pos().y >= ofGetHeight() - 170) {

		do {
			if (belongTo_->gActor()->Pos().x <= 0) {
				// 左端：右に移動する方向のみ
				movDir = ofVec3f(ofRandom(0.5f, 1.0f), ofRandom(-1.0f, 1.0f), 0);
			}
			else if (belongTo_->gActor()->Pos().x >= ofGetWidth()) {
				// 右端：左に移動する方向のみ
				movDir = ofVec3f(ofRandom(-1.0f, -0.5f), ofRandom(-1.0f, 1.0f), 0);
			}
			else if (belongTo_->gActor()->Pos().y <= 10) {
				// 上端：下に移動する方向のみ
				movDir = ofVec3f(ofRandom(-1.0f, 1.0f), ofRandom(0.5f, 1.0f), 0);
			}
			else if (belongTo_->gActor()->Pos().y >= ofGetHeight() - 170) {
				// 下端：上に移動する方向のみ
				movDir = ofVec3f(ofRandom(-1.0f, 1.0f), ofRandom(-1.0f, -0.5f), 0);
			}
			else {
				// 通常時：ランダムな方向を設定
				movDir = ofVec3f(ofRandom(-1.0f, 1.0f), ofRandom(-1.0f, 1.0f), 0);
			}
		} while (movDir.length() < 0.5); // movDir が小さすぎる場合は再度ランダムな方向を設定

		// movDir の長さを固定（速度を一定にする）
		
		movDir.normalize();
		auto app = ofApp::getInstance();
		int num = app->gameMainCtrlCpnt_->battlecountr_;
		movDir *= ofRandom(1.0f* num, 2.0f*num); // 速度をランダムに設定

		changeDirTime = 0; // 方向変更のカウンタをリセット
	}


	return nullptr;
}

void EnemyAct01StateShooting::exit()
{
	shootingtime = 0;
}

void EnemyAct01StateOutgoing::enter()
{
	if (belongTo_->gActor()->Pos().x > 300) {
		movDir = ofVec3f(5, 0, 0);
	}
	else {
		movDir = ofVec3f(-5, 0, 0);
	}
}

EnemyAction01State * EnemyAct01StateOutgoing::update()
{
	belongTo_->gActor()->Pos() += movDir;
	if (belongTo_->gActor()->Pos().x >= -10 &&
		belongTo_->gActor()->Pos().x <= 610) {
		return nullptr;
	}
	return &belongTo_->incoming_;
}

void EnemyAct01StateOutgoing::exit()
{
}
