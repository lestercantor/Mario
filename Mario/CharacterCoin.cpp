#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition) :
	Character(renderer, imagePath, startPosition, map) {

	mPosition = startPosition;

	mCollected = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; // 3 sorutes on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();

	mCurrentFrame = 0;
	mFrameDelay = 0.2f;
}

CharacterCoin::~CharacterCoin() {

}

void CharacterCoin::CoinCollected() {
	mCollected = true;
}

bool CharacterCoin::IsCollected() {
	return mCollected;
}

void CharacterCoin::Render() {

	int	left = mSingleSpriteWidth * mCurrentFrame;

	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e) {
	// Change frame?
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f) {
		// Reset frame delay count
		mFrameDelay = ANIMATION_DELAY;

		// Move frame on
		mCurrentFrame++;

		// Loop frame around if it goes beyond the number of frames
		if (mCurrentFrame > 2)
			mCurrentFrame = 0;
	}
}