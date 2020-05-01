#include "Character.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) {
	mRenderer = renderer;
	mPosition = startPosition;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	mMovingLeft = false;
	mMovingRight = false;

	mJumping = false;
	mCanJump = false;
	mJumpForce = 0.0f;

	mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;

	isAlive = true;

	score = 0;
}

Character::~Character() {
	mRenderer = NULL;
}

void Character::Render() {
	mTexture->Render(mPosition, SDL_FLIP_NONE);
}

void Character::Update(float deltaTime, SDL_Event e) {
	// Collision position variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
    int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
		AddGravity(deltaTime);
	} 
	else {
		// Collided with ground so we can jump again
		mCanJump = true;
	}

	// Deal with jumping first
	if (mJumping) {
		// Adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		// Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		// Has the jump force reduced to zero?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mMovingLeft) {
		MoveLeft(deltaTime);
	}
	else if (mMovingRight) {
		MoveRight(deltaTime);
	}
}

void Character::MoveRight(float deltaTime) {
	mFacingDirection = FACING_RIGHT;
	if (mPosition.x >= (SCREEN_WIDTH - mTexture->GetWidth()))
		mPosition.x = SCREEN_WIDTH - mTexture->GetWidth();
	mPosition.x += MovementSpeed;
}

void Character::MoveLeft(float deltaTime) {
	mFacingDirection = FACING_LEFT;
	if (mPosition.x <= 0)
		mPosition.x = 0;
	mPosition.x -= MovementSpeed;
}

void Character::AddGravity(float deltaTime) {
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump() {
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

bool Character::IsJumping() {
	if (mJumping)
		return true;
	if (!mJumping)
		return false;
}

void Character::CancelJump() {
	mJumpForce = 0;
}

Circle2D Character::GetCollisionCircle() {
	return Circle2D(mPosition.x, mPosition.y, mCollisionRadius, mCollisionRadius);
}

Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;
}

void Character::SetAlive(bool alive) {
	isAlive = alive;
	SetPosition(Vector2D(1000, 1000));
}

bool Character::GetAlive() {
	return isAlive;
}

int Character::AddScore(int add) {
	score += add;
	cout << "Score: " << score << endl;
	return score;
}