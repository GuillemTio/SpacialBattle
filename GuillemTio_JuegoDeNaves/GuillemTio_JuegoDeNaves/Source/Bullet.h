#pragma once
#include "GTEngine.h"

class Bullet : public Actor
{
private:
	int screenWidth;

public:
	Bullet(int height, int width, int screenWidth) : screenWidth(screenWidth)
	{
		onScreenChar = '-';
		posY = height;
		posX = width;
	}

	void BeginPlay(void) override;
	void Tick(float deltaTime) override;
	void OnCollision(Actor* collidedActor) override;

	void Move(void);
};

