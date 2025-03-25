#include "SoundManager.h"

const string SoundManager::soundList_[] = 
{
	"MainBGM.mp3",
	"effect01.mp3",
	"explosion.mp3",
	"shotse.wav",
	"GameOver.mp3",
	"GameClear.mp3",
	"Get.mp3",
	"RPGBGM.mp3",
	"TitleBGM.mp3",
	"Jump.mp3",
	"EnemyDamage.mp3",
	"Bomb.mp3",
	"HEAL.mp3",
};

SoundManager::SoundManager()
{
	for (auto& snd : soundList_) {
		ofSoundPlayer p;
		p.load("sounds\\" + snd);
		soundResources_.push_back(p);
	}
}

SoundManager::~SoundManager()
{
	for (auto& snd : soundResources_) {
		snd.unload();
	}
}

// Ä¶
void SoundManager::play(int _id)
{
	if (_id < 0 || _id >= soundResources_.size()) return;

	soundResources_[_id].play();
}

// ’â~
void SoundManager::stop(int _id)
{
	if (_id < 0 || _id >= soundResources_.size()) return;

	soundResources_[_id].stop();
}

// ƒ‹[ƒvÄ¶
void SoundManager::loop(int _id)
{
	if (_id < 0 || _id >= soundResources_.size()) return;

	soundResources_[_id].setLoop(true);
	soundResources_[_id].play();
}

// ‰¹—Êİ’è
void SoundManager::setVolume(int _id, float _vol)
{
	if (_id < 0 || _id >= soundResources_.size()) return;

	soundResources_[_id].setVolume(_vol);
}
