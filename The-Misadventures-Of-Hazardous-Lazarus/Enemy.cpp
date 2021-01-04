#include "Enemy.h"

Enemy::Enemy(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h, short hp, float d) : Sprite(src, dest, spr, w, h) {
	health = hp;
	damage = d;
	direction = 1;
}

short Enemy::GetHealth() {
	return health;
}

void Enemy::SetHealth(short hp) {
	health = hp;
}

void Enemy::TakeDamage() {
	health -= 1;
}

float Enemy::GetDamage() {
	return damage;
}

bool Enemy::GetDirection() {
	return direction;
}

void Enemy::Update() {}

