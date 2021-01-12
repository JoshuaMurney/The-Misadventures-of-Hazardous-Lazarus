#include "Player.h"
#include <algorithm>

Player::Player(SDL_Rect src, SDL_Rect dest, SDL_Texture* spr, int w, int h) : Sprite(src, dest, spr, w, h) {
	health = 4.0;
	speed = 4;
	isGrounded = false;
	batForm = false;
	accelX = accelY = velocityX = velocityY = 0;
	maxVelX = 10;
	maxVelY = 10;
	jumpForce = 60.0;
	speedModifier = 1.0;
	grav = 8.0;
	drag = 0.88;
	direction = 0;
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
	velocityX = std::min(std::max(velocityX, -(maxVelX * speedModifier)), (maxVelX * speedModifier));
	dest.x += (int)velocityX;

	if (batForm) {
		velocityY += accelY;
		velocityY = std::min(std::max(velocityY, -(maxVelY * speedModifier)), (maxVelY * speedModifier));
		dest.y += (int)velocityY;
	}
	else {
		velocityY += accelY + grav * 0.1;
		velocityY = std::min(std::max(velocityY, -jumpForce), (grav));
		dest.y += (int)velocityY;
	}

	accelX = accelY = 0.0;
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
	if (accelX > 0)
		direction = 0;
	else
		direction = 1;
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

bool Player::IsBatForm() {
	return batForm;
}

void Player::SetBatForm(bool flag) {
	batForm = flag;
}

void Player::SetSpeedModifier(double spd) {
	speedModifier = spd;
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

bool Player::GetDirection() {
	return direction;
}

