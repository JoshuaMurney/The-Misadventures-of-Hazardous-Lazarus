#pragma once
#include "Sprite.h"

class Enemy : public Sprite
{
	protected:
		short health;
		float damage;
		bool direction;

	public:
		Enemy() {}
		Enemy(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short hp, float d);
		short GetHealth();
		void SetHealth(short hp);
		void TakeDamage();
		float GetDamage();
		bool GetDirection();
		virtual void Update();
};

