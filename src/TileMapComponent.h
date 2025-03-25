#pragma once
#include "Component.h"
#include "ofMain.h"

class TileData;
class MapData;

class TileMapComponent : public Component
{
private:
	TileData* tileData_;
	MapData* mapData_;
	ofVec2f offset_;		// 表示位置（回転の中心）
public:
	TileMapComponent(GameActor* _gActor);
	virtual ~TileMapComponent();
	void initialize(string _tilefile, string _mapfile);
	void initialize(TileData* _tile, MapData* _map);
	virtual void update();
	void draw();
	ofVec2f& Offset();

	short posToTile(ofVec2f pos);
	short cellToTile(int _col, int _row);
	int getMapWidth();
	int getMapHeight();
	ofRectangle getCellRect(int _col, int _row);
	ofRectangle getCellRect(ofVec2f _pos);
};

