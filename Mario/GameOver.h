#pragma once
#ifndef _GAME_OVER_
#define _GAME_OVER_
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"

class Texture2D;

class GameOver : GameScreen {
public:
	GameOver(SDL_Renderer* renderer);
	~GameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();
};

#endif // !_GAME_OVER_


