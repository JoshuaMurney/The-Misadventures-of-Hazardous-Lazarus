#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

//Engine Constants
#define FPS 60
#define WIDTH 960
#define HEIGHT 726
#define PLAYER_W 48
#define PLAYER_H 126

//Border Constants
#define TOP_BORDER HEIGHT / 2
#define BOTTOM_BORDER HEIGHT - PLAYER_H
#define LEFT_BORDER 0
#define RIGHT_BORDER WIDTH - PLAYER_W

#include "SDL.h"
#include "SDL_mixer.h"
#include "Sprite.h"
#include "Player.h"
#include "Bat.h"
#include <iostream>
#include <vector>

class Engine
{
	private:
		//Engine Attributes
		bool running = false;
		Uint32 start, end, delta, fps;
		const Uint8* keystates;
		SDL_Window* window;
		SDL_Renderer* renderer;

		Player player;
		Bat bat;
		Sprite floor[27];

		SDL_Texture* lazarusSide;
		SDL_Texture* ground;
		SDL_Texture* batTexture;

		//Engine Functions
		int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
		void Clean();
		void Wake();
		void HandleEvents();
		bool KeyDown(SDL_Scancode c);
		void CheckCollision();
		void Update();
		void Render();
		void Sleep();

	public:
		Engine() {}
		int Run();
};

#endif

