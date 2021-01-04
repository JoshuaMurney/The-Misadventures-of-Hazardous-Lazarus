#include "Bat.h"
#include "SDL.h"

Bat::Bat(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short hp, float d, int xMax) : Enemy(src, dest, spr, w, h, hp, d) {
	this->xMax = xMax;
	xDirection = 1;
	yDirection = 1;
	yDelta = 0;
	xDelta = 0;
	speed = 2;
}

void Bat::Update() {
	xDelta += (xDirection * speed);
	if (xDelta <= 0) {
		xDirection = 1;
		direction = 1;
	}
	else if (xDelta >= xMax) {
		xDirection = -1;
		direction = 0;
	}

	yDelta += yDirection;
	if (yDelta == 10)
		yDirection = -1;
	else if (yDelta == -10)
		yDirection = 1;

	dest.x += (xDirection * speed);
	dest.y += yDirection;
}
