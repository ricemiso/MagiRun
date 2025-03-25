#pragma once
#include "ofMain.h"

struct AnimFrame {
	ofImage* image_;	// �摜�̃|�C���^
	int chipNo_;		// �`�b�v�ԍ�
	int chipW_;			// �`�b�v��(0 �Ȃ�ʏ�`��)
	int chipH_;			// �`�b�v����
	ofVec2f offset_;	// �I�t�Z�b�g�ʒu
	bool visible_;		// �\��/��\��
	int time_;			// �\������(�t���[����)
	int next_;			// ���̃R�}�̃C���f�b�N�X
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

