#pragma once
#ifndef _CHARACTER_KOOPA_
#define _CHARACTER_KOOPA_
#include <SDL.h>
#include "Commons.h"
#include "Character.h"
#include <iostream>
class CharacterKoopa : public Character 
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	void FlipRightWayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	bool GetInjured();
	void TakeDamage();
	void Jump();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();
};

#endif // !_CHARACTER_KOOPA_


