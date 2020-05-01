#pragma once
#ifndef CHARACTER_MARIO
#define CHARACTER_MARIO
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Character.h"
#include "SoundEffect.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();


protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	SoundEffect* soundEffect;

private:
	FACING mFacingDirection;

};
#endif // !CHARACTER_MARIO


