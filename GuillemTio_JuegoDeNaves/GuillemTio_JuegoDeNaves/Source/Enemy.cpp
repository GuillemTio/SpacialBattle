#include "Enemy.h"
#include "Bullet.h"

void Enemy::BeginPlay(void)
{
}

void Enemy::Tick(float deltaTime)
{
	Move();
}

void Enemy::OnCollision(Actor* collidedActor)
{
	if(dynamic_cast<Bullet*>(collidedActor))
	{
		health--;
		if(health == 0)
		{
			destroyed = true;
			killedByPlayer = true;
		}
	}
}

void Enemy::Move(void)
{
	posX -= speed;
	if (posX <= 0) destroyed = true;
}

void Enemy::SetPosition(int height, int width)
{
	posX = width;
	posY = height;
}
