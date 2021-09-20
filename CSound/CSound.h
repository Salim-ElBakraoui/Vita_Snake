/*
 * CSound.h
 *
 *  Created on: 17 sept. 2021
 *      Author: salim
 */
#include <SDL2/SDL_mixer.h>

#define VITA

#ifdef COMPUTER
	#define SOUND_DEFAULT_COLLECT_PATH		"Resources/Sound/collect.wav"
	#define SOUND_DEFAULT_POISON_PATH		"Resources/Sound/poison.wav"
	#define SOUND_DEFAULT_PAUSE_PATH		"Resources/Sound/pause.wav"

	#define SOUND_DEFAULT_MUSIC_PATH		"Resources/Sound/music.mp3"
#endif //ifdef COMPUTER

#ifdef VITA
	#define SOUND_DEFAULT_COLLECT_PATH		"app0://Resources/Sound/collect.wav"
	#define SOUND_DEFAULT_POISON_PATH		"app0://Resources/Sound/poison.wav"
	#define SOUND_DEFAULT_PAUSE_PATH		"app0://Resources/Sound/pause.wav"

	#define SOUND_DEFAULT_MUSIC_PATH		"app0://Resources/Sound/music.mp3"
#endif //ifdef VITA

#define SOUND_DEFAULT_MUSIC_VOLUME		((int)(128/2))

class CSound {
private:
	Mix_Music*		m_pMusic;

	Mix_Chunk*		m_pSoundCollect;
	Mix_Chunk*		m_pSoundPoison;
	Mix_Chunk*		m_pSoundPause;

public:
	CSound();
	~CSound();
	void MusicPause();
	void MusicPlay();
	void CollectPlay();
	void PoisonPlay();
	void PausePlay();
};
