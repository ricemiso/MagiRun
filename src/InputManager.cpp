#include "InputManager.h"

InputManager::KeyDefine InputManager::keyMap_[] = {
	{"Fire", ' ', 0},
	{"Bomb", 'e', 0},
	{"Horz",'d', 'a'},
	{"Vert",'s','w'},
	{"Start", ' ', 0},
	{"Jump", 'w', 0},
};
size_t  InputManager::keyListSize_ = sizeof(keyMap_) / sizeof(keyMap_[0]);

InputManager::InputManager()
{
	// ���O���猟���ł���A�z�L���̗v�f�ƁA�f�[�^�ۑ��p�̔z��̗v�f���쐬
	for (size_t i = 0; i < keyListSize_; ++i) {
		keylist_[keyMap_[i].name] = i;
		keyStatus_.push_back({0, 0});
	}
}

InputManager::~InputManager()
{
	keylist_.clear();
	keyStatus_.clear();
}

void InputManager::update()
{
	for (size_t i = 0; i < keyListSize_; ++i) {
		// ���݂̏�Ԃ��P�O�̏�Ԃɕێ�����
		keyStatus_[i].backValue = keyStatus_[i].nowValue;
		// ���݂̏�Ԃ𒲂ׂ�(negaKey �݂̂�������Ă���� -1 �ƂȂ�@��posi nega �����Ȃ� 0)
		keyStatus_[i].nowValue = static_cast<int>(ofGetKeyPressed(keyMap_[i].posiKey)) -
			static_cast<int>(ofGetKeyPressed(keyMap_[i].negaKey));
	}
}

bool InputManager::getButtonDown(string _keyName)
{
	// ��̎������@���A���̎������@���A��肽�����Ƃ͑S������
#if 0
	auto back = keyStatus_[keylist_[_keyName]].backValue;
	auto now = keyStatus_[keylist_[_keyName]].nowValue;

	if ( back != now && now == 1) {
		return true;
	}
	else {
		return false;
	}
#else
	return
		(keyStatus_[keylist_[_keyName]].backValue != 
			keyStatus_[keylist_[_keyName]].nowValue &&
			keyStatus_[keylist_[_keyName]].nowValue == 1);
#endif
}

bool InputManager::getButtonUp(string _keyName)
{
	return
		(keyStatus_[keylist_[_keyName]].backValue !=
			keyStatus_[keylist_[_keyName]].nowValue &&
			keyStatus_[keylist_[_keyName]].nowValue == 0);
}

bool InputManager::getButton(string _keyName)
{
	return (1 == keyStatus_[keylist_[_keyName]].nowValue);
}

int InputManager::getAxis(string _keyName)
{
	return keyStatus_[keylist_[_keyName]].nowValue;
}
