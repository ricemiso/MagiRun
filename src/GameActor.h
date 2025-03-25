#pragma once
#include "ofMain.h"
#include "Component.h"

class GameActor
{
protected:
	ofVec3f		pos_;	// ローカル座標
	ofVec3f		worldPos_;	// ワールド座標

	float		rotAngle_;	// ローカル回転角
	float		worldRotAngle_;	// ワールド回転角

	ofVec3f		scale_;		// ローカル倍率
	ofVec3f		worldScale_;	// ワールド倍率

	vector<unique_ptr<Component>> componentList_;
	string		name_;
	vector<unique_ptr<GameActor>>	childList_;
	queue<unique_ptr<GameActor>>	childAddQue_;

public:
	// コンストラクタ
	GameActor(string _name = "");
	// デストラクタ
	virtual ~GameActor();

	// アクセサ
	ofVec3f& Pos();		// 読み書き可能なアクセサメソッド
	const ofVec3f& WorldPos();

	float& RotAngle();
	const float& WorldRotAngle();

	ofVec3f& Scale();
	const ofVec3f WorldScale();

	string& Name();

	// ワールド座標、回転、倍率の計算
	void caluclateWorldTransform();
	
	std::function<void()>  drawfunc;

	// 更新処理(仮想関数)ただし、純粋仮想関数にはしない
	virtual void update();
	// 描画処理(仮想関数)
	virtual void draw();

	// 初期化するメソッド
	void initialize(ofVec3f _pos, string _name);

	bool	waitforErase_;	// 削除予定フラグ

	// テンプレート関数はヘッダに書くこと
	template <typename T>
	T* addComponent() {
		auto tmp = make_unique<T>(this);	// このメソッドで生成するコンポーネントクラスは
											// 第一引数に ゲームアクターのポインタのみにすること！
		auto res = tmp.get();
		componentList_.push_back(move(tmp));
		return res;
	}

	GameActor* parent_;		// 親のゲームアクター

	GameActor* addChild();

	// コンポーネントの削除
	void removeComponent(string _name);

	// 全ての子供を削除
	void removeAllChild();

	// 検索用メソッド
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

