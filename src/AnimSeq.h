#pragma once
#include "ofMain.h"

struct AnimFrame {
	ofImage* image_;	// 画像のポインタ
	int chipNo_;		// チップ番号
	int chipW_;			// チップ幅(0 なら通常描画)
	int chipH_;			// チップ高さ
	ofVec2f offset_;	// オフセット位置
	bool visible_;		// 表示/非表示
	int time_;			// 表示時間(フレーム数)
	int next_;			// 次のコマのインデックス
};


class AnimSeq
{
private:
	vector<AnimFrame>  seqdata_;

public:
	AnimSeq(string _fileName = "");
	virtual ~AnimSeq();
	void loadFromFile(string _filename);
	AnimFrame& getFrame(int _idx);
};

