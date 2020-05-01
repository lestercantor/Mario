#pragma once
#ifndef _INTRO_
#define _INTRO_
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"

class Texture2D;

class GameScreenIntro : GameScreen {
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();
};
#endif // !_INTRO_
