#pragma once
#include "ofMain.h"

enum {
	BGM_MAIN,
	SE_GAME_OVER,
	SE_EXPLOSION,
	SE_SHOT,
	BGM_GAMEOVER,
	BGM_GAMECLEAR,
	SE_GET,
	BGM_MAINRPG,
	BGM_TITLE,
	SE_JUMP,
	SE_ENEMYLOST,
	SE_BOMB,
	SE_HEAL,
};

class SoundManager
{
private:
	const static string soundList_[];
	vector<ofSoundPlayer> soundResources_;
public:
	SoundManager();
	virtual ~SoundManager();
	void play(int _id);		// çƒê∂
	void stop(int _id);		// í‚é~
	void loop(int _id);		// ÉãÅ[Évçƒê∂
	void setVolume(int _id, float _vol);	// âπó ê›íË
};
