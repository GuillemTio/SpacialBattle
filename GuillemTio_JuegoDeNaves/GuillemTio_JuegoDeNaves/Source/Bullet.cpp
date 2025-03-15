#include "Bullet.h"

void Bullet::BeginPlay(void)
{
}

void Bullet::Tick(float deltaTime)
{
	Move();
	if (posX >= screenWidth - 1)
		destroyed = true;
}

void Bullet::OnCollision(Actor* collidedActor)
{
	destroyed = true;
}

void Bullet::Move(void)
{
	posX++;
}
