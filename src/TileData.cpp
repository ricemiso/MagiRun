#include "TileData.h"
#include "ofApp.h"

TileData::TileData(string _filename)
	: loadedFile_("")
	, tileWidth_(0)
	, tileHeight_(0)
{
	if (_filename == "") return;
	loadFromFile(_filename);
}

TileData::~TileData()
{	
}

void TileData::loadFromFile(string _filename)
{
	tileimageList_.reserve(100);

	auto buffers = ofBufferFromFile(_filename);
	auto lines = buffers.getLines();
	auto itr = lines.begin();
	// タイルの大きさの取得
	tileWidth_ = stoi(itr.asString());
	++itr;
	tileHeight_ = stoi(itr.asString());
	++itr;
	loadedFile_ = itr.asString();

	// イメージの読み込みとタイル画像リストの作成
	auto imgMgr = ofApp::getInstance()->imagesManager_.get();

	imgMgr->loadContentsFromFile(itr.asString());
	auto imgbuff = ofBufferFromFile(loadedFile_);
	auto imglines = imgbuff.getLines();
	for (auto l : imglines) {
		tileimageList_.push_back(imgMgr->getContents(l));
	}
}

void TileData::releaseImage()
{
	tileimageList_.clear();
	ofApp::getInstance()->imagesManager_->unloadContentsFromFile(loadedFile_);
}

