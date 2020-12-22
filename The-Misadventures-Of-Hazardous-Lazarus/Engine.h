#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL.h";
#include <iostream>
#include <vector>
#include "SDL_mixer.h"

class Engine
{
	private:
		//Engine Attributes
		bool running = false;
		Uint32 start, end, delta, fps;
		const Uint8* keystates;
		SDL_Window* window;
		SDL_Renderer* renderer;

		//Engine Functions
		int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
		void Clean();
		void Wake();
		void HandleEvents();
		bool KeyDown(SDL_Scancode c);
		void Update();
		void Render();
		void Sleep();

	public:
		int Run();
};

#endif

