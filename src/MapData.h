#pragma once
#include "ofMain.h"

class MapData
{
private:
public:
	unique_ptr<short[]>  data_;
	int width_;
	int height_;
	MapData(std::string _filename = "");
	virtual ~MapData();
	MapData(MapData&&) = default;	// デフォルトムーブコンストラクタ
	// ムーブ代入演算子
	MapData& operator= (MapData&& other) noexcept {
		if (this != &other) {
			data_ = move(other.data_);
			width_ = other.width_;
			height_ = other.height_;
		}
		return *this;
	}
	void loadFromFile(std::string _filename);
	short getTile(int _col, int _row);
};

