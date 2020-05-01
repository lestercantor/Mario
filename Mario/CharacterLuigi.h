#pragma once
#ifndef CHARACTER_LUIGI
#define CHARACTER_LUIGI
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

private:
	FACING mFacingDirection;
};
#endif // !CHARACTER_LUIGI

