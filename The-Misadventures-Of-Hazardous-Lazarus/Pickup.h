#pragma once
#include "Sprite.h"

class Pickup : public Sprite
{
	private:
		short pointValue;

	public:
		Pickup(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short p);
		short GetPointValue();
		void SetPointValue(short p);
};

