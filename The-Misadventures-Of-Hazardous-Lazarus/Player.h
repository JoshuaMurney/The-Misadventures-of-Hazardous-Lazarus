#pragma once
#include "SDL.h"
#include "Sprite.h"
class Player : public Sprite
{
	private:
		float health;
		short speed;
		bool isGrounded;
		double accelX, accelY, velocityX, velocityY, maxVelX, maxVelY, drag, grav;

	public:
		Player() {}
		Player(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h);
		float GetHealth();
		short GetSpeed();
		void SetHealth(float hp);
		void SetSpeed(short spd);
		void TakeDamage(float hp);
		void Update();
		void Move();
		void Jump();
		void Stop();
		void StopX();
		void StopY();
		void SetAccelX(double a);
		void SetAccelY(double a);
		bool IsGrounded();
		void SetGrounded(bool flag);
		double GetVelX();
		double GetVelY();
		void SetX(float x);
		void SetY(float y);
};

