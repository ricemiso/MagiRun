#pragma once
#include "ofMain.h"

class InputManager
{
private:
	// �L�[�}�b�v��`�\����
	struct KeyDefine {
		string name;
		int posiKey;	// ���������Ɓ{�L�[�����p
		int negaKey;	// �|�L�[
	};
	static KeyDefine keyMap_[];
	static size_t  keyListSize_;
	// ���t���[���̃L�[��Ԃ�ۑ�����\����
	struct KeyStatus {
		int nowValue;
		int backValue;
	};
	vector<KeyStatus> keyStatus_;
	// �A�N�V�������Ō������邽�߂̘A�z�L���z��
	map<string, int>  keylist_;

public:
	InputManager();
	virtual ~InputManager();
	bool getButtonDown(string _keyName);
	bool getButtonUp(string _keyName);
	bool getButton(string _keyName);
	int getAxis(string _keyName);
	void update();
};

