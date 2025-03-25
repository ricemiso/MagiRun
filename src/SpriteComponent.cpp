#include "SpriteComponent.h"
#include "GameActor.h"

SpriteComponent::SpriteComponent(GameActor* _gactor)
	: Component(_gactor, "SpriteComponent")
	, image_(nullptr)
	, offset_({ 0, 0, 0 })
	, chipW_(0)
	, chipH_(0)
	, chipCol_(0)
	, chipNo_(0)
{
	gActor_->drawfunc = std::bind(&SpriteComponent::draw, this);
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::update()
{
}

void SpriteComponent::draw()
{
	if (!enabled_) return;
	ofSetColor(ofColor::white);

	// �`�b�v�T�C�Y���O�Ȃ�A�ʏ�̕`��
	if(chipW_ == 0 || chipH_ == 0) {
		image_->draw(offset_);
	}
	// �摜����A�`�b�v��؂�o���ĕ`��
	else {
		// �؂�o���ʒu���v�Z����
		float sx = (chipNo_ % chipCol_) * chipW_;
		float sy = (chipNo_ / chipCol_) * chipH_;

		image_->drawSubsection(offset_.x, offset_.y, chipW_, chipH_, sx, sy);
	}
}

void SpriteComponent::setImage(ofImage* _img, int _chipW, int _chipH)
{
	image_ = _img;

	chipW_ = _chipW;
	chipH_ = _chipH;
	if (chipW_ > 0) {
		// �摜�̉��̃`�b�v�����v�Z����
		chipCol_ = image_->getWidth() / _chipW;
	}
	chipNo_ = 0;
}

bool& SpriteComponent::Enabled()
{
	return enabled_;
}

ofVec3f& SpriteComponent::Offset()
{
	return offset_;
}

int& SpriteComponent::ChipNo()
{
	return chipNo_;
}

int SpriteComponent::getChipW()
{
	return chipW_;
}

int SpriteComponent::getChipH()
{
	return chipH_;
}
