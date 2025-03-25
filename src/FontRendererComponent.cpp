#include "FontRendererComponent.h"
#include "GameActor.h"

FontRendererComponent::FontRendererComponent(GameActor* _gActor)
	: Component(_gActor, "FontRendererComponent")
	, str_("")
	, col_(ofColor::white)
{}

FontRendererComponent::~FontRendererComponent()
{}

// ������
void FontRendererComponent::initialize(ofTrueTypeFont _font, string _str, ofVec3f _offset,
	ofColor _col)
{
	font_ = _font;
	str_ = _str;
	offset_ = _offset;
	col_ = _col;
	// �`��֐��I�u�W�F�N�g
	gActor_->drawfunc = std::bind(&FontRendererComponent::draw, this);
}

void FontRendererComponent::update()
{
}

void FontRendererComponent::draw()
{
	ofTranslate(offset_);
	ofSetColor(col_);
	font_.drawString(str_, 0, 0);
}

string& FontRendererComponent::String()
{
	return str_;
}

ofColor& FontRendererComponent::Color()
{
	return col_;
}
