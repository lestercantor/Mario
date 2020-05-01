#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include "CharacterMario.h"

using namespace::std;

// Globals
SDL_Window*	gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;

// Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[]) {
	// Flag to check if we wish to quit
	bool quit = false;

	// Check if SDL was set up correctly
	if (InitSDL()) {
		// Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();
		// Game loop
		while (!quit) {
			Render();
			quit = Update();
		}
	}

	// Close Window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL() {
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL did not intialise. Error: " << SDL_GetError();
		return false;
	}
	else {
		// All good, so attempt to create the window
		gWindow = SDL_CreateWindow("Games Engine Creation - Mario", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Did the window get created?
		if (gWindow == NULL) {
			// No
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL) {
			// Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) && imageFlags)) {
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
			
		}
		else {
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}

	return true;
}

void CloseSDL() {
	// Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL subsystems
	IMG_Quit;
	SDL_Quit();

	delete gameScreenManager;
	gameScreenManager = NULL;

	// Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
}

bool Update() {
	// Get the new time
	Uint32 newTime = SDL_GetTicks();

	// Event Handler
	SDL_Event e;

	// Get the events
	SDL_PollEvent(&e);

	// Handle any events
	switch (e.type) {
		// Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
} 

void Render() {
	// Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	// Update the screen
	SDL_RenderPresent(gRenderer);
}