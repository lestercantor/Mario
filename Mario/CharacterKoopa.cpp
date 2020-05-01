#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed) : 
	Character(renderer, imagePath, startPosition, map) {
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	// 2 sprites on this spritesheet in 1 row
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightWayUp() {
	SDL_FLIP_HORIZONTAL;
	mInjured = false;
	Jump();
}

void CharacterKoopa::Render() {
	// Variable to hold the left position of what we want to draw
	int left = 0.0f;
	
	// If injured move the left position to be the left position of the second image on the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;

	// Get the portion of the spritesheet you want to draw
	//								{ XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite }
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	// Determine where you want it drawn
	SDL_Rect destRect{ (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	// Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	// To gain the benefit of the code written in the base class Update() function we need to call it
	Character::Update(deltaTime, e);

	if (!mInjured) {
		// We are not injured so move
		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT) {
			mMovingRight = true;
			mMovingLeft = false;
		}
	} 
	else {
		// We should not move when injured
		mMovingLeft = false;
		mMovingRight = false;

		// Count down the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}
}

bool CharacterKoopa::GetInjured() {
	return mInjured;
}