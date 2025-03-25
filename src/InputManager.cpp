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
	// 名前から検索できる連想記憶の要素と、データ保存用の配列の要素を作成
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
		// 現在の状態を１つ前の状態に保持する
		keyStatus_[i].backValue = keyStatus_[i].nowValue;
		// 現在の状態を調べる(negaKey のみが押されていれば -1 となる　※posi nega 両方なら 0)
		keyStatus_[i].nowValue = static_cast<int>(ofGetKeyPressed(keyMap_[i].posiKey)) -
			static_cast<int>(ofGetKeyPressed(keyMap_[i].negaKey));
	}
}

bool InputManager::getButtonDown(string _keyName)
{
	// 上の実装方法も、下の実装方法も、やりたいことは全く同じ
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
