#pragma once
#ifndef _POW_BLOCK_
#define _POW_BLOCK_
#include <SDL.h>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox() { return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth() / 3, mTexture->GetHeight()); };
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; };

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

#endif // !_POW_BLOCK_
