#include "Sprite.h"

Sprite::Sprite(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h) {
	this->src = src;
	this->dest = dest;
	sprite = spr;
	width = w;
	height = h;
}

SDL_Rect* Sprite::GetSrc() {
	return &src;
}

SDL_Rect* Sprite::GetDest() {
	return &dest;
}

SDL_Texture* Sprite::GetSprite() {
	return sprite;
}

void Sprite::SetSrc(SDL_Rect src) {
	this->src = src;
}

void Sprite::SetDest(SDL_Rect dest) {
	this->dest = dest;
}

void Sprite::SetSprite(SDL_Texture* sprite) {
	this->sprite = sprite;
}