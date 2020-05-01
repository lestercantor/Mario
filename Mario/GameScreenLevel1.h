#pragma once
#ifndef _LEVEL_1_
#define _LEVEL_1_
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "SoundEffect.h"
#include "GameScreenManager.h"
#include <vector>
class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen {
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	
	void UpdatePOWBlock();

private:
	Texture2D* mBackgroundTexture;
	Character* MarioCharacter;
	CharacterKoopa* koopaCharacter;

	float koopaTimer;

	LevelMap* mLevelMap;

	PowBlock* mPowBlock;
	CharacterCoin* coin;
	SoundEffect* soundEffect;
	Mix_Music* gMusic;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenshake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoin(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);

	void LoadMusic(string path);

	std::vector<CharacterKoopa*> mEnemies;
	std::vector<CharacterCoin*> mCoins;
};
#endif // !_LEVEL_1_
