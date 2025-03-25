#pragma once
#include "ofMain.h"

class TileData
{
private:
	string loadedFile_;	// �ǂݍ��񂾃t�@�C���̃p�X��

public:
	vector<ofImage*> tileimageList_;	// �^�C���摜�̔z��
	int tileWidth_;		// �^�C���̕�
	int tileHeight_;	// �^�C���̍���
	TileData(string _filename = "");
	virtual ~TileData();
	void loadFromFile(string _filename);
	void releaseImage();
};

