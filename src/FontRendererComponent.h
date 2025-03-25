#pragma once
#include "ofMain.h"
#include "Component.h"

class FontRendererComponent : public Component
{
private:
	ofTrueTypeFont  font_;		// フォント
	ofColor			col_;		// 色
	string			str_;		// 文字列
	ofVec3f			offset_;	// ずらし位置
public:
	FontRendererComponent(GameActor* _gActor);
	virtual ~FontRendererComponent();
	// 初期化
	void initialize(ofTrueTypeFont _font, string _str, ofVec3f _offset = { 0,0,0 },
		ofColor _col = ofColor::white);

	virtual void update();
	virtual void draw();
	// アクセサ
	string& String();
	ofColor& Color();
};

