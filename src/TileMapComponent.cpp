#include "TileMapComponent.h"
#include "GameActor.h"
#include "ofApp.h"
#include "TileData.h"
#include "MapData.h"

TileMapComponent::TileMapComponent(GameActor* _gActor)
	: Component(_gActor, "TileMapComponent")
{
	_gActor->drawfunc = std::bind(&TileMapComponent::draw, this);
}

TileMapComponent::~TileMapComponent()
{
}

void TileMapComponent::initialize(string _tilefile, string _mapfile)
{
	auto app = ofApp::getInstance();

	tileData_ = app->tileresManager_->getContents(_tilefile);
	mapData_ = app->mapresManager_->getContents(_mapfile);
}


void TileMapComponent::initialize(TileData* _tile, MapData* _map)
{
	tileData_ = _tile;
	mapData_ = _map;
}


void TileMapComponent::update()
{
}

void TileMapComponent::draw()
{
	ofSetColor(ofColor::white);

	int w = mapData_->width_;
	int h = mapData_->height_;
	int tw = tileData_->tileWidth_;
	int th = tileData_->tileHeight_;

	// �񐔂ƍs���̉񐔕��A2�d���[�v����
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			auto tile = mapData_->data_[y * w + x];
			// �^�C���T�C�Y�ɑΉ��������W���v�Z���A�}�b�v�f�[�^�̔ԍ��̃^�C���摜��`�悷��
			auto tilePos = ofVec2f(x * tw, y * th);
			auto pos = offset_ + tilePos;
			// �^�C���摜���X�g�̗v�f����������Ȃ�ʏ�̕`��
			// �摜���P����������΁A�؂�o���ĕ`��
			if (tileData_->tileimageList_.size() > 1) {
				tileData_->tileimageList_[tile]->draw(pos);
			}
			else {
				auto image = tileData_->tileimageList_[0];
				// 1���̉摜����A�^�C����؂�o���ĕ`�悷��
				int col = image->getWidth() / tw;	// �摜�̉��̃^�C����
				// �؂�o���ʒu���v�Z����
				float sx = (tile % col) * tw;
				float sy = (tile / col) * th;
				image->drawSubsection(pos.x, pos.y, tw, th, sx, sy);
			}
		}
	}
}

ofVec2f& TileMapComponent::Offset()
{
	return offset_;
}

short TileMapComponent::posToTile(ofVec2f pos)
{
	int tw = tileData_->tileWidth_;
	int th = tileData_->tileHeight_;

	int col = pos.x / tw;
	int row = pos.y / th;

	return mapData_->getTile(col, row);
}

short TileMapComponent::cellToTile(int _col, int _row)
{
	return mapData_->getTile(_col, _row);
}

int TileMapComponent::getMapWidth()
{
	return mapData_->width_;
}

int TileMapComponent::getMapHeight()
{
	return mapData_->height_;
}

ofRectangle TileMapComponent::getCellRect(int _col, int _row)
{
	int tw = tileData_->tileWidth_;
	int th = tileData_->tileHeight_;

	return ofRectangle(_col * tw, _row * th, tw, th);
}

ofRectangle TileMapComponent::getCellRect(ofVec2f _pos)
{
	int tw = tileData_->tileWidth_;
	int th = tileData_->tileHeight_;

	int col = _pos.x / tw;
	int row = _pos.y / th;

	return getCellRect(col, row);
}
