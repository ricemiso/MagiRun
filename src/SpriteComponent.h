#pragma once
#include "ofMain.h"
#include "Component.h"

class SpriteComponent :  public Component
{
private:
	ofImage* image_;	// ofImgae �� �|�C���^
	ofVec3f offset_;	// �`��I�t�Z�b�g�ʒu
	bool enabled_;		// �\���� on/off (true = �\��)
	int		chipW_;		// �`�b�v�̕�(�`�b�v�̃T�C�Y���O�Ȃ�A�ʏ�`��)
	int		chipH_;		// �`�b�v�̍���
	int		chipCol_;	// �摜�̉��`�b�v��
	int		chipNo_;	// �`�b�v�ԍ�

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


