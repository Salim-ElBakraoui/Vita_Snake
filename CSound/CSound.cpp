/*
 * CSound.cpp
 *
 *  Created on: 17 sept. 2021
 *      Author: salim
 */

#include "CSound.h"

CSound::CSound():
	m_pMusic(nullptr),
	m_pSoundCollect(nullptr),
	m_pSoundPoison(nullptr),
	m_pSoundPause(nullptr){

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	Mix_AllocateChannels(4);
	m_pMusic 		= Mix_LoadMUS(SOUND_DEFAULT_MUSIC_PATH);
	m_pSoundCollect = Mix_LoadWAV(SOUND_DEFAULT_COLLECT_PATH);
	m_pSoundPoison 	= Mix_LoadWAV(SOUND_DEFAULT_POISON_PATH);
	m_pSoundPause	= Mix_LoadWAV(SOUND_DEFAULT_PAUSE_PATH);
	Mix_PlayMusic(m_pMusic, -1);
	Mix_VolumeMusic(SOUND_DEFAULT_MUSIC_VOLUME);
}

CSound::~CSound() {
	Mix_FreeChunk(m_pSoundPause);
	Mix_FreeChunk(m_pSoundPoison);
	Mix_FreeChunk(m_pSoundCollect);
	Mix_CloseAudio();
}

void CSound::MusicPlay(){Mix_ResumeMusic();}

void CSound::MusicPause(){Mix_PauseMusic();}

void CSound::CollectPlay(){Mix_PlayChannel(1, m_pSoundCollect, 0);}

void CSound::PoisonPlay(){Mix_PlayChannel(0, m_pSoundPoison, 0);}

void CSound::PausePlay(){Mix_PlayChannel(2,m_pSoundPause, 0);}
