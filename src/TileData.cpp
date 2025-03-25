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
	// �^�C���̑傫���̎擾
	tileWidth_ = stoi(itr.asString());
	++itr;
	tileHeight_ = stoi(itr.asString());
	++itr;
	loadedFile_ = itr.asString();

	// �C���[�W�̓ǂݍ��݂ƃ^�C���摜���X�g�̍쐬
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

