#pragma once
#ifndef _SOUND_EFFECT_
#define _SOUND_EFFECT_
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>

using namespace::std;

class SoundEffect {
private:
	Mix_Chunk* soundEffect;
	int soundEffectChannel;

public:
	SoundEffect(int audioRate, Uint16 audioFormat, int audioChannels, int audioBuffers);
	~SoundEffect();

	void Load(string path);
	void Play(int channel, int loop);
};

#endif // !_SOUND_EFFECT_