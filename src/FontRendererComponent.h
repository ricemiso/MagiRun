#pragma once
#include "ofMain.h"
#include "Component.h"

class FontRendererComponent : public Component
{
private:
	ofTrueTypeFont  font_;		// �t�H���g
	ofColor			col_;		// �F
	string			str_;		// ������
	ofVec3f			offset_;	// ���炵�ʒu
public:
	FontRendererComponent(GameActor* _gActor);
	virtual ~FontRendererComponent();
	// ������
	void initialize(ofTrueTypeFont _font, string _str, ofVec3f _offset = { 0,0,0 },
		ofColor _col = ofColor::white);

	virtual void update();
	virtual void draw();
	// �A�N�Z�T
	string& String();
	ofColor& Color();
};

