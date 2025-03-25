#include "AnimSeq.h"
#include "ofApp.h"

AnimSeq::AnimSeq(string _fileName)
{
	seqdata_.reserve(100);

	if (_fileName != "") {
		loadFromFile(_fileName);
	}
}

AnimSeq::~AnimSeq()
{}

void AnimSeq::loadFromFile(string _filename)
{
	// シーケンスの初期化
	seqdata_.clear();
	// json ファイルの読み込み
	auto json = ofLoadJson(_filename);
	// json オブジェクト配列の取得
	auto array = json["AnimFrameArray"];

	// forループで、jsonオブジェクトを取得してフレームデータを作成する
	auto imageResMgr = ofApp::getInstance()->imagesManager_.get();
	for (auto& data : array) {
		AnimFrame  frame;

		frame.image_ = imageResMgr->getContents(data["image"]);
		frame.chipNo_ = data["chipno"];
		frame.chipW_ = data["chipw"];
		frame.chipH_ = data["chiph"];
		frame.offset_ = { data["offset"]["x"], data["offset"]["y"] };
		frame.visible_ = data["visible"];
		frame.time_ = data["time"];
		frame.next_ = data["next"];
		seqdata_.push_back(frame);
	}
}

AnimFrame& AnimSeq::getFrame(int _idx)
{
	return seqdata_[_idx];
}
