#include "MapData.h"
#include "ofxCsv.h"
#include "ofApp.h"

MapData::MapData(string _filename)
{
	if (_filename == "") return;
	loadFromFile(_filename);
}

MapData::~MapData()
{
}

void MapData::loadFromFile(string _filename)
{
	ofxCsv csv;
	csv.load(_filename);

	// マップのサイズを取得
	width_ = csv[0].getInt(0);
	height_ = csv[0].getInt(1);

	// マップのサイズ分、マップデータ配列を生成
	data_ = make_unique<short[]>(width_ * height_);

	// マップデータ配列にタイル情報を読み込む
	for (int r = 0; r < height_; ++r) {
		for (int c = 0; c < width_; ++c) {
			// csv ファイルの 2行目から読み込むので、 r + 1する
			data_[r * width_ + c] = csv[r + 1].getInt(c);
		}
	}
}

short MapData::getTile(int _col, int _row)
{
	if (_col >= 0 && _col < width_ && _row >= 0 && _row < height_) {
		return data_[_row * width_ + _col];
	}
	return -1;
}
