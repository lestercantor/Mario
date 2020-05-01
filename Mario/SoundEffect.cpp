#include "SoundEffect.h"

SoundEffect::SoundEffect(int audioRate, Uint16 audioFormat, int audioChannels, int audioBuffers) {
	audioRate = 22050;
	audioFormat = AUDIO_S16;
	audioChannels = 2;
	audioBuffers = 4096;

    soundEffect = NULL;
	soundEffectChannel = -1;
}

SoundEffect::~SoundEffect() {
	Mix_FreeChunk(soundEffect);
	soundEffect = NULL;
}

void SoundEffect::Load(string path) {
	soundEffect = Mix_LoadWAV(path.c_str());

	if (soundEffect == NULL) {
		cout << "Failed to load sound effect. Error: " << Mix_GetError() << endl;
	}
}

void SoundEffect::Play(int channel, int loop) {
	soundEffectChannel = Mix_PlayChannel(channel, soundEffect, loop);
}
