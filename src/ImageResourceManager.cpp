#include "ImageResourceManager.h"

ImageResourceManager::ImageResourceManager()
	: contents_()
{}

ImageResourceManager::~ImageResourceManager()
{
	clearResource();
}

// 画像ファイル名を列挙したテキストを読み込んで内部に保持する
void ImageResourceManager::loadImageFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_[l] = ofImage(l);
	}
}

// パス名を指定して、画像のポインタを取得するメソッド
ofImage* ImageResourceManager::getImage(string _imagePath)
{
	return &contents_[_imagePath];
}

// 保持している画像を破棄して contents をクリア
void ImageResourceManager::clearResource()
{
	contents_.clear();
}

// 画像ファイル名を列挙したテキストを読み込んで画像を破棄する
void ImageResourceManager::unloadImageFromFile(string _filename)
{
	ofBuffer resfile = ofBufferFromFile(_filename);

	auto lines = resfile.getLines();
	for (auto l : lines) {
		contents_.erase(l);
	}
}
