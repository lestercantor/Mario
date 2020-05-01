#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"
#include <Windows.h>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	mLevelMap = NULL;

	gMusic = NULL;
	soundEffect = new SoundEffect(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

GameScreenLevel1::~GameScreenLevel1() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete MarioCharacter;
	MarioCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	// Do the screen shake if required
	if (mScreenshake) {
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// End the shake after the duration
		if (mScreenshakeTime <= 0.0f) {
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	// Update Mario
	MarioCharacter->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateCoin(deltaTime, e);
	UpdateEnemies(deltaTime, e);
}

void GameScreenLevel1::Render() {
	// Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	// Draw coins
	for (unsigned int i = 0; i < mCoins.size(); i++) {
		mCoins[i]->Render();
	}

	// Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	mPowBlock->Render();
	MarioCharacter->Render();
}

bool GameScreenLevel1::SetUpLevel() {
	SetLevelMap();
	// Set up our POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!";
		return false;
	}

	// Load the background music
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Mixer could not initialise. Error: " << Mix_GetError() << endl;
		return false;
	}
	LoadMusic("Music/Mario.ogg");
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(gMusic, -1);
	}

	// Set up the player character
	MarioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);

	// Set up coins
	CreateCoin(Vector2D(180, 350));
	CreateCoin(Vector2D(210, 350));
	CreateCoin(Vector2D(240, 350));
	CreateCoin(Vector2D(270, 350));
	CreateCoin(Vector2D(300, 350));
	CreateCoin(Vector2D(150, 32));
	CreateCoin(Vector2D(120, 32));
	CreateCoin(Vector2D(325, 32));
	CreateCoin(Vector2D(355, 32));

	// Set up 2 bad guys 
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	return true;
}

void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	// Clear up any old map
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}
	// Set the new map
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(MarioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			// Collided whilst jumping
			if (MarioCharacter->IsJumping()) {
				DoScreenshake();
				mPowBlock->TakeAHit();
				MarioCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake() {
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty()) 
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) 
		{
			// Check if enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f) 
			{
				// Is the enemy off the screen to the left/right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
					mEnemies[i]->SetAlive(false);
			}

			// Now do the update
			mEnemies[i]->Update(deltaTime, e);

			// Check to see if the enemy collides with the player
			if ( (mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				(mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f) ) 
			{
				// Ignore the collisions if the enemy is behind a pipe?
			}
			else 
			{
				if (Collisions::Instance()->Circle(mEnemies[i]->GetCollisionCircle(), MarioCharacter->GetCollisionCircle())) 
				{
					if (mEnemies[i]->GetInjured()) {
						mEnemies[i]->SetAlive(false);
						MarioCharacter->AddScore(30);
					}
					else {
						MarioCharacter->SetAlive(false);
						
						Mix_HaltMusic();
						soundEffect->Load("Music/MarioDeath.wav");
						soundEffect->Play(-1, 0);
						Sleep(4000);					
					}
				}
			}
			// If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive()) 
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1) 
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position) {
	coin = new CharacterCoin(mRenderer, "Images/Coin.png", mLevelMap, position);
	mCoins.push_back(coin);
}

void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e) {
	if (!mCoins.empty()) {
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); i++) {
			mCoins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(mCoins[i]->GetCollisionCircle(), MarioCharacter->GetCollisionCircle())) {
				mCoins[i]->SetAlive(false);
				MarioCharacter->AddScore(10);

				soundEffect->Load("Music/CoinCollected.wav");
				soundEffect->Play(-1, 0);
			}

			if (!mCoins[i]->GetAlive()) {
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
	}
}

void GameScreenLevel1::LoadMusic(string path) {
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL) {
		cout << "Failed to load background music. Error: " << Mix_GetError() << endl;
	}
}