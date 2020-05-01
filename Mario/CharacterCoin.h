#pragma once
#ifndef _CHARACTER_COIN_
#define _CHARACTER_COIN_
#include <SDL.h>
#include "Commons.h"
#include "Character.h"
class CharacterCoin : public Character {
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	float mCollected;

	float mFrameDelay;
	float mCurrentFrame;

public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition);
	~CharacterCoin();

	bool IsCollected();
	void CoinCollected();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();
};
#endif // !_CHARACTER_COIN_

