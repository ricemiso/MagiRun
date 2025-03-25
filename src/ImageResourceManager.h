#pragma once
#include "ofMain.h"

class ImageResourceManager
{
private:
	unordered_map<string, ofImage> contents_;
	string defaultPath_;	// �f�t�H���g�̃t�H���_��

public:
	ImageResourceManager();
	virtual ~ImageResourceManager();

	// �摜�t�@�C������񋓂����e�L�X�g��ǂݍ���œ����ɕێ�����
	void loadImageFromFile(string _filename);

	// �p�X�����w�肵�āA�摜�̃|�C���^���擾���郁�\�b�h
	ofImage* getImage(string _imagePath);

	// �ێ����Ă���摜��j������ contents ���N���A
	void clearResource();

	// �摜�t�@�C������񋓂����e�L�X�g��ǂݍ���ŉ摜��j������
	void unloadImageFromFile(string _filename);
};
