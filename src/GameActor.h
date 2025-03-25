#pragma once
#include "ofMain.h"
#include "Component.h"

class GameActor
{
protected:
	ofVec3f		pos_;	// ���[�J�����W
	ofVec3f		worldPos_;	// ���[���h���W

	float		rotAngle_;	// ���[�J����]�p
	float		worldRotAngle_;	// ���[���h��]�p

	ofVec3f		scale_;		// ���[�J���{��
	ofVec3f		worldScale_;	// ���[���h�{��

	vector<unique_ptr<Component>> componentList_;
	string		name_;
	vector<unique_ptr<GameActor>>	childList_;
	queue<unique_ptr<GameActor>>	childAddQue_;

public:
	// �R���X�g���N�^
	GameActor(string _name = "");
	// �f�X�g���N�^
	virtual ~GameActor();

	// �A�N�Z�T
	ofVec3f& Pos();		// �ǂݏ����\�ȃA�N�Z�T���\�b�h
	const ofVec3f& WorldPos();

	float& RotAngle();
	const float& WorldRotAngle();

	ofVec3f& Scale();
	const ofVec3f WorldScale();

	string& Name();

	// ���[���h���W�A��]�A�{���̌v�Z
	void caluclateWorldTransform();
	
	std::function<void()>  drawfunc;

	// �X�V����(���z�֐�)�������A�������z�֐��ɂ͂��Ȃ�
	virtual void update();
	// �`�揈��(���z�֐�)
	virtual void draw();

	// ���������郁�\�b�h
	void initialize(ofVec3f _pos, string _name);

	bool	waitforErase_;	// �폜�\��t���O

	// �e���v���[�g�֐��̓w�b�_�ɏ�������
	template <typename T>
	T* addComponent() {
		auto tmp = make_unique<T>(this);	// ���̃��\�b�h�Ő�������R���|�[�l���g�N���X��
											// �������� �Q�[���A�N�^�[�̃|�C���^�݂̂ɂ��邱�ƁI
		auto res = tmp.get();
		componentList_.push_back(move(tmp));
		return res;
	}

	GameActor* parent_;		// �e�̃Q�[���A�N�^�[

	GameActor* addChild();

	// �R���|�[�l���g�̍폜
	void removeComponent(string _name);

	// �S�Ă̎q�����폜
	void removeAllChild();

	// �����p���\�b�h
	GameActor* getChild(int _index) const;

	template<typename T>
	T* getComponent() {
		for (auto& cpnt : componentList_) {
			if (typeid(T) == typeid(*cpnt.get())) {
				return dynamic_cast<T*>(cpnt.get());
			}
		}
		return nullptr;
	}

	GameActor* getChildByName(const std::string& name) {
		for (auto& child : childList_) {
			if (child->name_ == name) {
				return child.get();
			}
		}
		return nullptr;
	}

	static GameActor* findActor(GameActor* _current, string _name);
	static list<GameActor*>&& findActors(GameActor* _current, string _name,
		list<GameActor*>&& _list = list<GameActor*>());

	static void createPlayer(GameActor* _parent, ofVec3f _pos, string _name);
	static void createEnemy(GameActor* _parent, ofVec3f _pos, string _name);
	static void createBullet(GameActor* _parent, ofVec3f _pos, float _angle, string _name);
	static void createPlayerBullet(GameActor* _parent, ofVec3f _pos, float _angle, float _speed, string _name);
};

