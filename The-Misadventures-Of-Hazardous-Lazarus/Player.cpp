#include "Player.h"
#include <algorithm>

Player::Player(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h) : Sprite(src, dest, spr, w, h) {
	health = 4.0;
	speed = 4;
	isGrounded = false;
	accelX = accelY = velocityX = velocityY = 0;
	maxVelX = 10;
	maxVelY = 60.0;
	grav = 8.0;
	drag = 0.88;
}
 
float Player::GetHealth() {
	return health;
}

short Player::GetSpeed() {
	return speed;
}

//This function SETS the health to THE VALUE THAT IS PASSED
void Player::SetHealth(float hp) {
	health = hp;
}

void Player::SetSpeed(short spd) {
	speed = spd;
}

//This function SUBTRACTS THE VALUE THAT IS PASSED from health
void Player::TakeDamage(float hp) {
	health -= hp;
}

void Player::Update() {
	velocityX += accelX;
	velocityX *= (isGrounded ? drag : 1.0);
	velocityX = std::min(std::max(velocityX, -maxVelX), maxVelX);
	dest.x += (int)velocityX;

	velocityY += accelY + grav * 0.1;
	velocityY = std::min(std::max(velocityY, -maxVelY), (grav));
	dest.y += (int)velocityY;

	accelX = accelY = 0.0;
}

void Player::Jump() {

}

void Player::Stop() {
	StopX();
	StopY();
}

void Player::StopX() {
	velocityX = 0.0;
}

void Player::StopY() {
	velocityY = 0.0;
}

void Player::SetAccelX(double a) {
	accelX = a;
}

void Player::SetAccelY(double a) {
	accelY = a;
}

bool Player::IsGrounded() {
	return isGrounded;
}

void Player::SetGrounded(bool flag) {
	isGrounded = flag;
}

double Player::GetVelX() {
	return velocityX;
}

double Player::GetVelY() {
	return velocityY;
}

void Player::SetX(float x) {
	dest.x = x;
}

void Player::SetY(float y) {
	dest.y = y;
}



