#include "ImageResourceManager.h"

ImageResourceManager::ImageResourceManager()
	: contents_()
{}

ImageResourceManager::~ImageResourceManager()
{
	clearResource();
}

// �摜�t�@�C������񋓂����e�L�X�g��ǂݍ���œ����ɕێ�����
void ImageResourceManager::loadImageFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_[l] = ofImage(l);
	}
}

// �p�X�����w�肵�āA�摜�̃|�C���^���擾���郁�\�b�h
ofImage* ImageResourceManager::getImage(string _imagePath)
{
	return &contents_[_imagePath];
}

// �ێ����Ă���摜��j������ contents ���N���A
void ImageResourceManager::clearResource()
{
	contents_.clear();
}

// �摜�t�@�C������񋓂����e�L�X�g��ǂݍ���ŉ摜��j������
void ImageResourceManager::unloadImageFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.erase(l);
	}
}
