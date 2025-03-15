#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include <windows.h>

void Character::BeginPlay(void)
{
	posX = screenWidth / 4;
	posY = screenHeight / 2;
}

void Character::Tick(float deltaTime)
{
	Move();

	static float shootTimer = 0;
	shootTimer += deltaTime;
	if (timeToShoot <= shootTimer)
	{
		Shoot();
		shootTimer = 0;
	}
}

void Character::OnCollision(Actor* collidedActor)
{
	if (dynamic_cast<Enemy*>(collidedActor))
		playerGameOver = true;
}

bool Character::GetGameOver(void)
{
	return playerGameOver;
}

void Character::ResetPlayer(void)
{
	BeginPlay();
	playerGameOver = false;
}

void Character::Move(void)
{
	int yDirection = 0;
	int xDirection = 0;

	switch (playerInput->GetLastArrowKeyPressedAndReset())
	{
	case(VK_LEFT):
		yDirection = 0;
		xDirection = -1;
		break;
	case(VK_RIGHT):
		yDirection = 0;
		xDirection = 1;
		break;
	case(VK_UP):
		yDirection = -1;
		xDirection = 0;
		break;
	case(VK_DOWN):
		yDirection = 1;
		xDirection = 0;
		break;
	case(0): 
		yDirection = 0;
		xDirection = 0;
		return;
	default:
		break;
	}
	

	posY += yDirection;
	posX += xDirection;

	if (posX >= screenWidth - 1)
		posX = screenWidth - 2;
	else if (posX < 1)
		posX = 1;
	if (posY >= screenHeight - 1)
		posY = screenHeight - 2;
	else if (posY < 4)
		posY = 4;

}

void Character::Shoot(void)
{
	Bullet* bullet = new Bullet(posY, posX + 2, screenWidth);
	GameEngine::AddActor(bullet);
}
