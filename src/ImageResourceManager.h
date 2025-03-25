#pragma once
#include "ofMain.h"

class ImageResourceManager
{
private:
	unordered_map<string, ofImage> contents_;
	string defaultPath_;	// デフォルトのフォルダ名

public:
	ImageResourceManager();
	virtual ~ImageResourceManager();

	// 画像ファイル名を列挙したテキストを読み込んで内部に保持する
	void loadImageFromFile(string _filename);

	// パス名を指定して、画像のポインタを取得するメソッド
	ofImage* getImage(string _imagePath);

	// 保持している画像を破棄して contents をクリア
	void clearResource();

	// 画像ファイル名を列挙したテキストを読み込んで画像を破棄する
	void unloadImageFromFile(string _filename);
};
