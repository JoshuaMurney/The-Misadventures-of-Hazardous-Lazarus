#include "Pickup.h"
#include "SDL.h"

Pickup::Pickup(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short p) : Sprite(src, dest, spr, w, h) {
	pointValue = p;
}

short Pickup::GetPointValue() {
	return pointValue;
}

void Pickup::SetPointValue(short p) {
	pointValue = p;
}
