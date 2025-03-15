#pragma once
#include "GTEngine.h"

class Enemy : public Actor
{
public:
	bool killedByPlayer = false;
	int pointsGiven;

private:
	int health;
	int speed;

public:
	Enemy(int health, int speed, char enemyDrawedChar, int points, int heightPos, int widthPos) 
		: health(health), speed(speed), pointsGiven(points)
	{
		onScreenChar = enemyDrawedChar;
		SetPosition(heightPos, widthPos);
	}

	void BeginPlay(void) override;
	void Tick(float deltaTime) override;
	void OnCollision(Actor* collidedActor) override;

private:
	void Move(void);
	void SetPosition(int height, int width);
};

