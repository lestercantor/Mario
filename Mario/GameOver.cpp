#include "GameOver.h"
#include "Texture2D.h"
#include <iostream>

GameOver::GameOver(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}

GameOver::~GameOver() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameOver::Update(float deltaTime, SDL_Event e) {

}

void GameOver::Render() {
	// Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameOver::SetUpLevel() {
	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/GameOver.png")) {
		cout << "Failed to load background texture!";
		return false;
	}
	return true;
}