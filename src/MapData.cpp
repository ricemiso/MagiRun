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

	// �}�b�v�̃T�C�Y���擾
	width_ = csv[0].getInt(0);
	height_ = csv[0].getInt(1);

	// �}�b�v�̃T�C�Y���A�}�b�v�f�[�^�z��𐶐�
	data_ = make_unique<short[]>(width_ * height_);

	// �}�b�v�f�[�^�z��Ƀ^�C������ǂݍ���
	for (int r = 0; r < height_; ++r) {
		for (int c = 0; c < width_; ++c) {
			// csv �t�@�C���� 2�s�ڂ���ǂݍ��ނ̂ŁA r + 1����
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
