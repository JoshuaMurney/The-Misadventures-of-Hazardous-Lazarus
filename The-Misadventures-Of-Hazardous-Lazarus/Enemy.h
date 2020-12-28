#pragma once
#include "Sprite.h"

class Enemy : public Sprite
{
	protected:
		short health;
		float damage;

	public:
		Enemy(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short hp, float d);
		short GetHealth();
		void SetHealth(short hp);
		void TakeDamage();
		float GetDamage();
		//void virtual Move();
};

