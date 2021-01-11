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
					batTexture = IMG_LoadTexture(renderer, "Sprites/Bat.png");
					echoTexture = IMG_LoadTexture(renderer, "Sprites/Echo.png");
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

	echoTriggered = false;
	player = { {0, 0, 48, 126}, {600, 100, 48, 126}, lazarusSide, PLAYER_W, PLAYER_H };
	echo = { { 0, 0, 1920, 1452 }, {((player.GetDest()->x + (player.GetDest()->w / 2)) - WIDTH), ((player.GetDest()->y + (player.GetDest()->h / 2)) - HEIGHT), WIDTH * 2, HEIGHT * 2}, echoTexture, WIDTH * 2, HEIGHT * 2 };
	bat = { {0, 0, 47, 21}, {96, 96, 48, 21}, batTexture, 48, 21, 1, 0.5, (48 * 5)};
	for (int i = 0; i < 20; i++) {
		floor[i] = { {0, 0, 48, 48}, {(48 * i), (48 * 11), 48, 48}, ground, 48, 48 };
	}
	for (int j = 0; j < 5; j++) {
		floor[(j + 20)] = { {0, 0, 48, 48}, {(480 + (48 * j)), (48 * 7), 48, 48}, ground, 48, 48 };
	}
	floor[25] = { {0, 0, 48, 48}, {480, (48 * 6), 48, 48}, ground, 48, 48 };
	floor[26] = { {0, 0, 48, 48}, {480, (48 * 5), 48, 48}, ground, 48, 48 };

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
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				case SDLK_w:
					if (player.IsGrounded()) {
						player.SetAccelY(-20.0);
						player.SetGrounded(false);
					}
					break;
				case SDLK_LSHIFT:
					if (player.IsBatForm()) {
						player.SetBatForm(false);
						player.SetSpeedModifier(1.0);
						player.SetSprite(lazarusSide);
						player.SetSrc({ 0, 0, 48, 126 });
						player.SetDest({ player.GetDest()->x, player.GetDest()->y - 53, 48, 126 });
					}
					else {
						player.SetBatForm(true);
						player.SetSpeedModifier(0.75);
						player.SetSprite(batTexture);
						player.SetSrc({ 0, 0, 47, 21 });
						player.SetDest({ player.GetDest()->x, player.GetDest()->y + 53, 48, 21 });
					}
					break;
				case SDLK_SPACE:
					echoTriggered = true;
					break;
			}
		}
	}
}

void Engine::CheckCollision() {
	for (int i = 0; i < 27; i++) {
		if (SDL_HasIntersection(player.GetDest(), floor[i].GetDest())) {
			//Did Player hit the ground from the top?
			if (player.GetDest()->y + player.GetDest()->h - (float)player.GetVelY() <= floor[i].GetDest()->y) {
				player.SetGrounded(true);
				player.StopY();
				player.GetDest()->y = floor[i].GetDest()->y - player.GetDest()->h;
			}
			//Did player hit the ground from the bottom?
			else if (player.GetDest()->y - (float)player.GetVelY() >= (floor[i].GetDest()->y + floor[i].GetDest()->h)) {
				player.StopY();
				player.GetDest()->y = floor[i].GetDest()->y + floor[i].GetDest()->h;
			}
			//Did player hit the ground from the LEFT side?
			else if (player.GetDest()->x + player.GetDest()->w - (float)player.GetVelX() <= floor[i].GetDest()->x) {
				player.StopX();
				player.GetDest()->x = floor[i].GetDest()->x - player.GetDest()->w - 1;
			}
			//Did player hit the ground from the RIGHT side?
			else if (player.GetDest()->x - (float)player.GetVelX() >= (floor[i].GetDest()->x + floor[i].GetDest()->w)) {
				player.StopX();
				player.GetDest()->x = floor[i].GetDest()->x + floor[i].GetDest()->w + 1;
			}
		}
	}
}

//=== UPDATE: anything that may be updated on a frame-by-frame basis goes here ===
void Engine::Update() {
	if (KeyDown(SDL_SCANCODE_A) && player.GetDest()->x > LEFT_BORDER)
		player.SetAccelX(-1.0);
	else if (KeyDown(SDL_SCANCODE_D) && player.GetDest()->x < RIGHT_BORDER)
		player.SetAccelX(1.0);
	else
		player.StopX();

	if (player.IsBatForm()) {
		if (KeyDown(SDL_SCANCODE_W) && player.GetDest()->y > TOP_BORDER)
			player.SetAccelY(-1.0);
		else if (KeyDown(SDL_SCANCODE_S) && player.GetDest()->y < BOTTOM_BORDER)
			player.SetAccelY(1.0);
		else
			player.StopY();
	}

	if (echoTriggered || echoSize > 0.0) {
		if (echoTriggered) {
			echoSize += 0.125;
			if (echoSize >= 2.0) {
				echoSize = 2.0;
				echoTriggered = false;
			}
		}
		else {
			echoSize -= 0.0025;
			if (echoSize < 0.0)
				echoSize = 0.0;
		}
	}

	player.Update();
	echo.SetDest({((player.GetDest()->x + (player.GetDest()->w / 2)) - WIDTH - int(WIDTH * echoSize)), ((player.GetDest()->y + (player.GetDest()->h / 2)) - HEIGHT - int(HEIGHT * echoSize)), (WIDTH * 2) + int(WIDTH * 2 * echoSize), (HEIGHT * 2) + int(HEIGHT * 2 * echoSize)});
	bat.Update();
	CheckCollision();
}

//=== RENDER: Anything display related goes here ===
void Engine::Render() {
	SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, player.GetSprite(), player.GetSrc(), player.GetDest());
	SDL_RenderCopyEx(renderer, bat.GetSprite(), bat.GetSrc(), bat.GetDest(), 0.0, NULL, static_cast<SDL_RendererFlip>(bat.GetDirection()));
	for (int i = 0; i < 27; i++)
		SDL_RenderCopy(renderer, floor[i].GetSprite(), (floor+i)->GetSrc(), (floor+i)->GetDest());
	SDL_RenderCopy(renderer, echo.GetSprite(), echo.GetSrc(), echo.GetDest());
	SDL_RenderPresent(renderer);
}

//=== CLEAN: All data and memory allocation goes here ===
void Engine::Clean() {
	cout << "Cleaning Engine" << endl;
	SDL_DestroyTexture(lazarusSide);
	SDL_DestroyTexture(ground);
	SDL_DestroyTexture(batTexture);
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
