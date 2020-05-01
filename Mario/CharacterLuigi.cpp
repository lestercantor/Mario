#include "CharacterLuigi.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {

}

CharacterLuigi::~CharacterLuigi() {

}

void CharacterLuigi::Render() {
	if  (Character::mFacingDirection == FACING_LEFT) {
		// Luigi's default sprite faces the left
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_NONE);
	}
	else {
		// Luigi faces right
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			// Moves Luigi left
			mMovingLeft = true;
			break;

		case SDLK_d:
			// Moves Luigi right
			mMovingRight = true;
			break;

		case SDLK_w:
			if (mCanJump)
				Character::Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			mMovingLeft = false;
			break;

		case SDLK_d:
			mMovingRight = false;
			break;
		}
	}
}