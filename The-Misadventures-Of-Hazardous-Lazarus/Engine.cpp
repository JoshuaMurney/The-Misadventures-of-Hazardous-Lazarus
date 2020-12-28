#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "Sprite.h"
#include <iostream>
using namespace std;

int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "All Subsystems Initialized" << endl;
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		if (window != nullptr) {
			renderer = SDL_CreateRenderer(window, -1, NULL);

			if (renderer != nullptr) {
				//=========================================================
				// Any Sound Files and Textures should be initialized HERE
				//=========================================================
				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
					lazarusSide = IMG_LoadTexture(renderer, "Sprites/Lazarus Side.png");
					ground = IMG_LoadTexture(renderer, "Sprites/Ground.png");
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

	fps = (Uint32)round((1 / (double)FPS) * 1000);
	keystates = SDL_GetKeyboardState(nullptr);
	running = true;

	player = { {0, 0, 48, 126}, {100, 100, 48, 126}, lazarusSide, PLAYER_W, PLAYER_H };
	for (int i = 0; i < 20; i++) {
		floor[i] = { {0, 0, 48, 48}, {((48 * i)), (48 * 11), 48, 48}, ground, 48, 48 };
	}

	cout << "Engine Running successfully" << endl;
	return true;
}

//=== HANDLE_EVENTS: Process Event Handling and/or Keys ===
void Engine::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		}
	}
}

//=== UPDATE: anything that may be updated on a frame-by-frame basis goes here ===
void Engine::Update() {
	if (KeyDown(SDL_SCANCODE_A) && player.GetDest()->x > LEFT_BORDER) {
		player.SetAccelX(-1.0);
		player.Move();
	}
	else if (KeyDown(SDL_SCANCODE_D) && player.GetDest()->x < RIGHT_BORDER) {
		player.SetAccelX(1.0);
		player.Move();
	}
	else
		player.StopX();
}

//=== RENDER: Anything display related goes here ===
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, player.GetSprite(), player.GetSrc(), player.GetDest());
	for (int i = 0; i < 20; i++)
		SDL_RenderCopy(renderer, floor[i].GetSprite(), (floor+i)->GetSrc(), (floor+i)->GetDest());
	SDL_RenderPresent(renderer);
}

//=== CLEAN: All data and memory allocation goes here ===
void Engine::Clean() {
	cout << "Cleaning Engine" << endl;
	SDL_DestroyTexture(lazarusSide);
	SDL_DestroyTexture(ground);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//===================================================
// FUNCTIONS BELOW THIS POINT SHOULD NOT BE ALTERTED
//===================================================

//=== WAKE: Get a time when the game loop started. Used in FPS calculation ===
void Engine::Wake() {
	start = SDL_GetTicks();
}

//=== SLEEP: Manages The FPS ===
void Engine::Sleep() {
	end = SDL_GetTicks();
	delta = end - start;
	if (delta < fps)
		SDL_Delay(fps - delta);
}

//=== KEYDOWN: Returns the state of a key ===
bool Engine::KeyDown(SDL_Scancode c) {
	if (keystates != nullptr) {
		if (keystates[c] == 1)
			return true;
	}
	return false;
}

//=== RUN: Contains the Game Loop ===
int Engine::Run() {
	if (running)
		return 1;
	if (!Init("The Misadventures Of Hazardous Lazarus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE))
		return 2;
	while (running) {
		Wake();
		HandleEvents();
		Update();
		Render();
		if (running)
			Sleep();
	}

	Clean();
	return 0;
}
