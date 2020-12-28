#pragma once
#include "Sprite.h"

class Pickup : public Sprite
{
	Pickup(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h);
};

