#include "ofMain.h"
#include "GameActor.h"
#include "ofApp.h"
#include "EnemyActionComponent.h"
#include "PlayerAction.h"

// �R���X�g���N�^
GameActor::GameActor(string _name)
	: pos_(ofVec3f(0,0,0))
	, scale_({1, 1, 1})
	, rotAngle_(0)
	, waitforErase_(false)
	, name_(_name)
	, drawfunc([](){})	// ��̃����_��
{}

// �f�X�g���N�^
GameActor::~GameActor()
{
	OutputDebugString(L"dispose GameActor. \n");
}

// ���������郁�\�b�h
void GameActor::initialize(ofVec3f _pos, string _name)
{
	name_ = _name;
	pos_ = _pos;

	// ���[���h���W���v�Z����
	caluclateWorldTransform();
}

// �X�V����
void GameActor::update()
{
	// ���[���h���W���v�Z����
	caluclateWorldTransform();

	// �����̃R���|�[�l���g�̍X�V����
	for (auto& c : componentList_) {
		c->update();
	}
	// ���[���h���W���v�Z����
	caluclateWorldTransform();

	// ofApp �� �`�惊�X�g�ɓo�^
	ofApp::getInstance()->draworderset_.insert(this);

	// �폜�\��̎q�A�N�^�[���폜
	childList_.erase(
		remove_if(childList_.begin(), childList_.end(),
			[](const auto& a) {return a->waitforErase_; }),
		childList_.end()
	);
	// �ǉ��҂��q�A�N�^�[��ǉ�
	while (!childAddQue_.empty()) {
		childList_.push_back(move(childAddQue_.front()));
		childAddQue_.pop();
	}
	// �q�A�N�^�[�̍X�V����
	for (auto& c : childList_) {
		c->update();
	}
}

// �`�揈��
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


// �ǂݏ����\�ȃA�N�Z�T���\�b�h
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

// ���[���h���W�A��]�A�{���̌v�Z
void GameActor::caluclateWorldTransform()
{
	if (parent_ != nullptr) {
		worldScale_ = parent_->worldScale_ * scale_;
		worldRotAngle_ = parent_->worldRotAngle_ + rotAngle_;
		// �e�̈ړ��Ɖ�]�Ɗg�k�𔽉f������
		worldPos_ = parent_->worldPos_ +
			pos_.getRotated(-parent_->worldRotAngle_, ofVec3f(0, 0, 1)) *
			parent_->worldScale_;
	}
	else {
		worldScale_ = scale_;
		worldRotAngle_ = rotAngle_;
		worldPos_ = pos_.getRotated(-rotAngle_, ofVec3f(0, 0, 1)) * scale_;	
		//���̃Q�[���G���W���ł́A�{�̏ꍇ�A�����v���
	}
}


// �R���|�[�l���g�̍폜
void GameActor::removeComponent(string _name)
{
	// �����_���� [&] �Ƃ���ƁA�쐬���̊֐��̃X�R�[�v���󂯓n���� 
	componentList_.erase(
		remove_if(
			componentList_.begin(), componentList_.end(),
			[&](auto& c) { return (c->getComponentName() == _name); }
		),
		componentList_.end()
	);
}


// �q�̃Q�[���A�N�^�[�𐶐����Ēǉ�����
GameActor* GameActor::addChild()
{
	auto actor = make_unique<GameActor>();
	auto res = actor.get();
	childAddQue_.push(move(actor));
	res->parent_ = this;
	return res;
}


// �S�Ă̎q�����폜
void GameActor::removeAllChild()
{
	queue<unique_ptr<GameActor>>().swap(childAddQue_);	// queue �̑S����

	for (auto& c : childList_) {
		c->waitforErase_ = true;
	}
}


// �q�A�N�^�[�̎擾
GameActor* GameActor::getChild(int _index) const
{
	return childList_.at(_index).get();
}


// �Q�[���A�N�^�[���ċA�I�Ɍ������郁�\�b�h
GameActor* GameActor::findActor(GameActor* _current, string _name)
{
	// ���� _current�̖��O�� �� _name ����v���Ă�����A _current ��Ԃ�
	if (_current->Name() == _name) return _current;

	// ��v���Ă��Ȃ���΁A�����̑S�Ă̎q�A�N�^�[�̖��O����v���Ă��邩�A�ċA�I�ɂ���ׂ�
	for (auto& child : _current->childList_) {
		auto tmp = findActor(child.get(), _name);

		// �q�A�N�^�[����A��v�����A�N�^�[���߂��Ă�����A�����߂�
		if (tmp != nullptr) return tmp;
	}
	// �����łȂ���΁Anull ��߂�
	return nullptr;
}

list<GameActor*>&& GameActor::findActors(GameActor* _current, string _name, list<GameActor*>&& _list)
{
	// ���� _current �̖��O����v������ ���X�g�ɒǉ�����
	if (_current->Name() == _name) _list.push_back(_current);

	// �����̎q�A�N�^�[�S�Ă��ċA�I�� ��������
	for (auto& child : _current->childList_) {
		_list = findActors(child.get(), _name, move(_list));
	}

	// ���X�g��߂�
	return move(_list);
}



// ---------------------------------------------------------------------------
// �Q�[���A�N�^�[�̐������\�b�h

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
