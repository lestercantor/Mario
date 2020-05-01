#pragma once
#ifndef _CHARACTER_
#define _CHARACTER_
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;

class Character {
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	bool mMovingLeft;
	bool mMovingRight;

	FACING mFacingDirection;

	float mCollisionRadius;

	bool isAlive;
	int score;
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition() { return mPosition; };
	
	void AddGravity(float deltaTime);
	void Jump();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	Circle2D GetCollisionCircle();

	bool IsJumping();
	void CancelJump();

	void SetAlive(bool alive);
	bool GetAlive();

	int AddScore(int add);
private:
	LevelMap* mCurrentLevelMap;
};

#endif // !_CHARACTER_

