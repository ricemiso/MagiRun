#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent :  public Component
{
private:
	ofImage* image_;	// ofImgae の ポインタ
	ofVec3f offset_;	// 描画オフセット位置
	bool enabled_;		// 表示の on/off (true = 表示)
	int		chipW_;		// チップの幅(チップのサイズが０なら、通常描画)
	int		chipH_;		// チップの高さ
	int		chipCol_;	// 画像の横チップ数
	int		chipNo_;	// チップ番号

public:
	SpriteComponent(GameActor* _gactor);
	~SpriteComponent();
	virtual void update();
	void draw();
	void setImage(ofImage* _img, int _chipW = 0, int _chipH = 0);
	bool& Enabled();
	ofVec3f& Offset();
	int& ChipNo();
	int getChipW();
	int getChipH();
};


