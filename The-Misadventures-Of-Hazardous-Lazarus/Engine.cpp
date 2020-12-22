#include "Engine.h"
#include <iostream>
using namespace std;

//Engine Constants
#define FPS 60
#define WIDTH 960
#define HEIGHT 726

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

}

//=== RENDER: Anything display related goes here ===
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

//=== CLEAN: All data and memory allocation goes here ===
void Engine::Clean() {
	cout << "Cleaning Engine" << endl;
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
