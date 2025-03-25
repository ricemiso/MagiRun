#pragma once
#include "ofMain.h"

class TileData
{
private:
	string loadedFile_;	// 読み込んだファイルのパス名

public:
	vector<ofImage*> tileimageList_;	// タイル画像の配列
	int tileWidth_;		// タイルの幅
	int tileHeight_;	// タイルの高さ
	TileData(string _filename = "");
	virtual ~TileData();
	void loadFromFile(string _filename);
	void releaseImage();
};

