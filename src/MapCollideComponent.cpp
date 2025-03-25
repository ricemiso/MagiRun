#include "MapCollideComponent.h"
#include "GameActor.h"
#include "TileMapComponent.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "ofApp.h"
#include "GameMainCtrlComponent.h"
#include "GameState.h"

MapCollideComponent::MapCollideComponent(GameActor* _gActor)
	: Component(_gActor, "MapCollideComponent")
{
	movement_ = _gActor->getComponent<MovementComponent>();
	collision_ = _gActor->getComponent<CollisionComponent>();
}


void MapCollideComponent::initialize(TileMapComponent* _tileMap)
{
	tileMap_ = _tileMap;

	// �}�b�v����A�S�ẴZ����T�����čő�̃^�C���ԍ��𒲂ׂ�
	int w = tileMap_->getMapWidth();
	int h = tileMap_->getMapHeight();
	int tileNum = 0;
	for (int r = 0; r < h; r++) {
		for (int c = 0; c < w; c++) {
			if (tileNum < tileMap_->cellToTile(c, r)) {
				tileNum = tileMap_->cellToTile(c, r);
			}
		}
	}
	// ��Q������p�̘A�z�L����������
	for (short i = 0; i < tileNum; i++) {
		colTypeTable_.insert(map<short,bool>::value_type(i, false));
	}
}


void MapCollideComponent::update()
{
	// �����蔻��p�̎l�p�`���擾����
	auto rect = collision_->calcRect();

	// ���i�̍��E�𔻒�
	if (movement_->MoveVec().x < 0.0f) {
		checkCollide(rect, LEFT, LEFT_MIDDLE);
	}
	else {
		checkCollide(rect, RIGHT, RIGHT_MIDDLE);
	}

	// ������̔���
	if (movement_->MoveVec().y < 0.0f) {
		checkCollide(rect, UP, LEFT_TOP);
		checkCollide(rect, UP, CENTER_TOP);
		checkCollide(rect, UP, RIGHT_TOP);
	}
	// ���E�Ɉړ��������ׂ�
	if (movement_->MoveVec().x < 0.0f) {
		checkCollide(rect, LEFT, LEFT_TOP);
	}
	else {
		checkCollide(rect, RIGHT, RIGHT_TOP);
	}

	// �������̔���
	if (movement_->MoveVec().y > 0.0f) {
		checkCollide(rect, DOWN, LEFT_BOTTOM);
		checkCollide(rect, DOWN, CENTER_BOTTOM);
		checkCollide(rect, DOWN, RIGHT_BOTTOM);
	}
	// �����̍��E����
	if (movement_->MoveVec().x > 0.0f) {
		checkCollide(rect, LEFT, LEFT_BOTTOM);
	}
	else {
		checkCollide(rect, RIGHT, RIGHT_BOTTOM);
	}
}

void MapCollideComponent::setCollideType(int _tile, bool _collide)
{
	colTypeTable_[_tile] = _collide;
}

bool MapCollideComponent::checkObstacle(ofVec3f _pos)
{
	auto tile = tileMap_->posToTile(_pos);

	return colTypeTable_[tile];
}

int MapCollideComponent::getTileNum(ofVec3f _pos)
{
	auto tile = tileMap_->posToTile(_pos);

	return tile;
}




void  MapCollideComponent::forceFeedback(ofVec3f _pos, int _dir, ofRectangle& _rect)
{
	// �^�C���̎l�p�`���v�Z����
	auto tileRect = tileMap_->getCellRect(_pos);

	// �����ɉ����ĉ����߂�����
	float tx = 0.0f;
	float ty = 0.0f;
	switch (_dir) {
	case UP:
		ty = tileRect.getBottom() - _rect.getTop();
		break;
	case LEFT:
		tx = tileRect.getRight() - _rect.getLeft();
		break;
	case RIGHT:
		 tx = tileRect.getLeft() - _rect.getRight() - 1;
		break;
	case DOWN:
		ty =  tileRect.getTop() - _rect.getBottom() - 1;
		break;
	default:
		break;
	}
	gActor_->Pos().x += tx;
	gActor_->Pos().y += ty;
	_rect.translate(tx, ty);
}


bool MapCollideComponent::checkCollide(ofRectangle& _rect, int _dir, Position _pos, bool _isFeedback)
{
	bool res = false;
	ofVec2f point;

	// ���� _pos �ŗ^����ꂽ�_�̍��W���擾����
	switch (_pos) {
	case LEFT_TOP:
	case LEFT_MIDDLE:
	case LEFT_BOTTOM:
		point.x = _rect.getLeft();
		break;
	case CENTER_TOP:
	case CENTER_BOTTOM:
		point.x = _rect.getCenter().x;
		break;
	case RIGHT_TOP:
	case RIGHT_MIDDLE:
	case RIGHT_BOTTOM:
		point.x = _rect.getRight();
		break;
	}
	switch (_pos) {
	case LEFT_TOP:
	case CENTER_TOP:
	case RIGHT_TOP:
		point.y = _rect.getTop();
		break;
	case LEFT_MIDDLE:
	case RIGHT_MIDDLE:
		point.y = _rect.getCenter().y;
		break;
	case LEFT_BOTTOM:
	case CENTER_BOTTOM:
	case RIGHT_BOTTOM:
		point.y = _rect.getBottom();
		break;
	}

	res = checkObstacle(point);

	

	if (res && _isFeedback) {
		forceFeedback(point, _dir, _rect);
		if (_dir == LEFT || _dir == RIGHT) {
			movement_->MoveVec().x = movement_->Accele().x = 0.0f;
		}
		else {
			movement_->MoveVec().y = movement_->Accele().y = 0.0f;
		}
	}

	return res;
}

bool MapCollideComponent::checkObstacle(int _dir)
{
	bool res = false;
	auto rect = collision_->calcRect();

	switch (_dir) {
	case UP:
		rect.translate(0.0f, -1.0f);
		res = checkCollide(rect, _dir, LEFT_TOP, false) ||
			checkCollide(rect, _dir, CENTER_TOP, false) ||
			checkCollide(rect, _dir, RIGHT_TOP, false);
		break;
	case LEFT:
		rect.translate(-1.0f, 0.0f);
		res = checkCollide(rect, _dir, LEFT_TOP, false) ||
			checkCollide(rect, _dir, LEFT_MIDDLE, false) ||
			checkCollide(rect, _dir, LEFT_BOTTOM, false);
		break;
	case RIGHT:
		rect.translate(1.0f, 0.0f);
		res = checkCollide(rect, _dir, RIGHT_TOP, false) ||
			checkCollide(rect, _dir, RIGHT_MIDDLE, false) ||
			checkCollide(rect, _dir, RIGHT_BOTTOM, false);
		break;
	case DOWN:
		rect.translate(0.0f, 1.0f);
		res = checkCollide(rect, _dir, LEFT_BOTTOM, false) ||
			checkCollide(rect, _dir, CENTER_BOTTOM, false) ||
			checkCollide(rect, _dir, RIGHT_BOTTOM, false);
		break;
	default:
		break;
	}
	return res;
}


