#include "CharacterMario.h"
#include "Texture2D.h"
#include "Constants.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {
	soundEffect = new SoundEffect(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

CharacterMario::~CharacterMario() {

}

void CharacterMario::Render() {
	if (Character::mFacingDirection == FACING_RIGHT) {
		// Mario's default sprite faces the right
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_NONE);
	}
	else {
		// Mario faces left
		Character::mTexture->Render(Character::mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			// Moves Mario left
			mMovingLeft = true;
			break;

		case SDLK_RIGHT:
			// Moves Mario right
			mMovingRight = true;
			break;

		case SDLK_UP:
			if (mCanJump) {
				Character::Jump();
				soundEffect->Load("Music/MarioJump.wav");
				soundEffect->Play(-1, 0);
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			mMovingLeft = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
	}
}
