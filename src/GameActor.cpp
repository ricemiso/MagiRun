#include "ofMain.h"
#include "GameActor.h"
#include "ofApp.h"
#include "EnemyActionComponent.h"
#include "PlayerAction.h"

// コンストラクタ
GameActor::GameActor(string _name)
	: pos_(ofVec3f(0,0,0))
	, scale_({1, 1, 1})
	, rotAngle_(0)
	, waitforErase_(false)
	, name_(_name)
	, drawfunc([](){})	// 空のラムダ式
{}

// デストラクタ
GameActor::~GameActor()
{
	OutputDebugString(L"dispose GameActor. \n");
}

// 初期化するメソッド
void GameActor::initialize(ofVec3f _pos, string _name)
{
	name_ = _name;
	pos_ = _pos;

	// ワールド座標を計算する
	caluclateWorldTransform();
}

// 更新処理
void GameActor::update()
{
	// ワールド座標を計算する
	caluclateWorldTransform();

	// 自分のコンポーネントの更新処理
	for (auto& c : componentList_) {
		c->update();
	}
	// ワールド座標を計算する
	caluclateWorldTransform();

	// ofApp の 描画リストに登録
	ofApp::getInstance()->draworderset_.insert(this);

	// 削除予定の子アクターを削除
	childList_.erase(
		remove_if(childList_.begin(), childList_.end(),
			[](const auto& a) {return a->waitforErase_; }),
		childList_.end()
	);
	// 追加待ち子アクターを追加
	while (!childAddQue_.empty()) {
		childList_.push_back(move(childAddQue_.front()));
		childAddQue_.pop();
	}
	// 子アクターの更新処理
	for (auto& c : childList_) {
		c->update();
	}
}

// 描画処理
void GameActor::draw()
{
	ofPushMatrix();
	ofTranslate(worldPos_);
	ofRotateDeg(-worldRotAngle_);
	ofScale(worldScale_);

	assert(drawfunc != nullptr);
	drawfunc();

	ofPopMatrix();
}


// 読み書き可能なアクセサメソッド
ofVec3f& GameActor::Pos()
{
	return pos_;
}

const ofVec3f& GameActor::WorldPos()
{
	return worldPos_;
}

float& GameActor::RotAngle()
{
	return rotAngle_;
}

const float& GameActor::WorldRotAngle()
{
	return worldRotAngle_;
}

ofVec3f& GameActor::Scale()
{
	return scale_;
}

const ofVec3f GameActor::WorldScale()
{
	return worldScale_;
}


string& GameActor::Name()
{
	return name_;
}

// ワールド座標、回転、倍率の計算
void GameActor::caluclateWorldTransform()
{
	if (parent_ != nullptr) {
		worldScale_ = parent_->worldScale_ * scale_;
		worldRotAngle_ = parent_->worldRotAngle_ + rotAngle_;
		// 親の移動と回転と拡縮を反映させる
		worldPos_ = parent_->worldPos_ +
			pos_.getRotated(-parent_->worldRotAngle_, ofVec3f(0, 0, 1)) *
			parent_->worldScale_;
	}
	else {
		worldScale_ = scale_;
		worldRotAngle_ = rotAngle_;
		worldPos_ = pos_.getRotated(-rotAngle_, ofVec3f(0, 0, 1)) * scale_;	
		//このゲームエンジンでは、＋の場合、反時計回り
	}
}


// コンポーネントの削除
void GameActor::removeComponent(string _name)
{
	// ラムダ式に [&] とすると、作成元の関数のスコープが受け渡せる 
	componentList_.erase(
		remove_if(
			componentList_.begin(), componentList_.end(),
			[&](auto& c) { return (c->getComponentName() == _name); }
		),
		componentList_.end()
	);
}


// 子のゲームアクターを生成して追加する
GameActor* GameActor::addChild()
{
	auto actor = make_unique<GameActor>();
	auto res = actor.get();
	childAddQue_.push(move(actor));
	res->parent_ = this;
	return res;
}


// 全ての子供を削除
void GameActor::removeAllChild()
{
	queue<unique_ptr<GameActor>>().swap(childAddQue_);	// queue の全消し

	for (auto& c : childList_) {
		c->waitforErase_ = true;
	}
}


// 子アクターの取得
GameActor* GameActor::getChild(int _index) const
{
	return childList_.at(_index).get();
}


// ゲームアクターを再帰的に検索するメソッド
GameActor* GameActor::findActor(GameActor* _current, string _name)
{
	// 引数 _currentの名前が と _name が一致していたら、 _current を返す
	if (_current->Name() == _name) return _current;

	// 一致していなければ、自分の全ての子アクターの名前が一致しているか、再帰的にしらべる
	for (auto& child : _current->childList_) {
		auto tmp = findActor(child.get(), _name);

		// 子アクターから、一致したアクターが戻ってきたら、それを戻す
		if (tmp != nullptr) return tmp;
	}
	// そうでなければ、null を戻す
	return nullptr;
}

list<GameActor*>&& GameActor::findActors(GameActor* _current, string _name, list<GameActor*>&& _list)
{
	// 引数 _current の名前が一致したら リストに追加する
	if (_current->Name() == _name) _list.push_back(_current);

	// 自分の子アクター全てを再帰的に 検索する
	for (auto& child : _current->childList_) {
		_list = findActors(child.get(), _name, move(_list));
	}

	// リストを戻す
	return move(_list);
}



// ---------------------------------------------------------------------------
// ゲームアクターの生成メソッド

void GameActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	auto playerActionCpnt = actor->addComponent<PlayerAction>();
	auto collisionCpnt = actor->addComponent<CollisionComponent>();
	collisionCpnt->initialize({ 0,-30 }, 42.0f, 50.0f, CollisionType::PLAYER_OBJECT);
	collisionCpnt->onCollisionFunc_ = std::bind(&PlayerAction::onCollision,
		playerActionCpnt, std::placeholders::_1);
}



void GameActor::createEnemy(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	auto enemyActionComponent_ = actor->addComponent<EnemyActionComponent>();
	auto coli = actor->addComponent<CollisionComponent>();
	coli->initialize({ 0,0 }, 20, 20, CollisionType::ENEMY_OBJECT);
	coli->onCollisionFunc_ = std::bind(&EnemyActionComponent::onCollision,
		enemyActionComponent_, std::placeholders::_1);
}

#include "MovementComponent.h"
#include "OutScreenCheckComponent.h"
#include "CollisionComponent.h"
#include "BulletActionComponent.h"


void GameActor::createBullet(GameActor* _parent, ofVec3f _pos, float _angle, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	auto movementComponent_ = actor->addComponent<MovementComponent>();
	actor->addComponent<OutScreenCheckComponent>();
	auto coli = actor->addComponent<CollisionComponent>();
	auto action_ = actor->addComponent<BulletActionComponent>();

	coli->initialize({ 0,0 }, 10, 10, CollisionType::ENEMY_BULLET);
	coli->onCollisionFunc_ = std::bind(&BulletActionComponent::onCollision,
		action_, std::placeholders::_1);

	movementComponent_->setAngle(_angle, 1);
}

void GameActor::createPlayerBullet(GameActor* _parent, ofVec3f _pos, float _angle, float _speed, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	auto movementComponent_ = actor->addComponent<MovementComponent>();
	actor->addComponent<OutScreenCheckComponent>();
	auto coli = actor->addComponent<CollisionComponent>();
	auto action_ = actor->addComponent<BulletActionComponent>();

	coli->initialize({ 0,0 }, 10, 10, CollisionType::PLAYER_BULLET);
	coli->onCollisionFunc_ = std::bind(&BulletActionComponent::onCollision,
		action_, std::placeholders::_1);

	movementComponent_->setAngle(_angle, _speed);
}
