#pragma once
#include "Enemy.h"
class Bat : public Enemy
{
	private:
		int xDelta;
		int xMax;
		int yDelta;
		int yDirection;
		int xDirection;
		short speed;
	public:
		Bat() {}
		Bat(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short hp, float d, int xMax);
		void Update();
};

