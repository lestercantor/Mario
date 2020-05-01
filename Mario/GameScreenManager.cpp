#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "GameScreenIntro.h"
#include "GameOver.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen = NULL;

	// Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render() {
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	// Clear up the old screen
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenIntro* tempIntro;
	GameOver* tempOver;

	SCREEN_INTRO* SCREEN_INTRO;
	SCREEN_GAMEOVER* SCREEN_GAMEOVER;
	SCREEN_LEVEL1* SCREEN_LEVEL1;


	switch (newScreen) {
	case SCREEN_INTRO:
		tempIntro = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)tempIntro;
		tempIntro = NULL;
		break;

	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;

	case SCREEN_GAMEOVER:
		tempOver = new GameOver(mRenderer);
		mCurrentScreen = (GameScreen*)tempOver;
		tempOver = NULL;
		break;
	}
}