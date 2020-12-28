#pragma once
#include "SDL.h";

class Sprite
{
	protected:
		SDL_Rect src;
		SDL_Rect dest;
		SDL_Texture* sprite;
		int width;
		int height;

	public:
		Sprite() {}
		Sprite(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h);
		SDL_Rect* GetSrc();
		SDL_Rect* GetDest();
		SDL_Texture* GetSprite();
		void SetSrc(SDL_Rect src);
		void SetDest(SDL_Rect dest);
		void SetSprite(SDL_Texture* sprite);
};

