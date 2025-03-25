#pragma once
#include "Component.h"

class TileMapComponent;
class MovementComponent;
class CollisionComponent;

class MapCollideComponent : public Component
{
protected:
	// �����蔻��l�p�`�̎���8�_�̒�`
	enum Position {
		LEFT_TOP,
		CENTER_TOP,
		RIGHT_TOP,
		LEFT_MIDDLE,
		RIGHT_MIDDLE,
		LEFT_BOTTOM,
		CENTER_BOTTOM,
		RIGHT_BOTTOM,
	};

	TileMapComponent* tileMap_;
	MovementComponent* movement_;
	CollisionComponent* collision_;

	map<short, bool>	colTypeTable_;	// �ǂ̃^�C������Q�����𔻒肷�邽�߂̘A�z�L��

	bool checkCollide(ofRectangle &_rect, int _dir, Position _pos, bool _isFeedback = true);
	bool checkObstacle(ofVec3f _pos);
	void forceFeedback(ofVec3f _pos, int _dir, ofRectangle &_rect);

public:
	enum {
		UP,
		LEFT,
		RIGHT,
		DOWN
	};
	MapCollideComponent(GameActor *_gActor);
	virtual ~MapCollideComponent() {};
	void initialize(TileMapComponent* _tileMap);
	virtual void update();
	void setCollideType(int _tile, bool _collide = false);
	bool checkObstacle(int _dir);
	int getTileNum(ofVec3f _pos);
	
	
};

