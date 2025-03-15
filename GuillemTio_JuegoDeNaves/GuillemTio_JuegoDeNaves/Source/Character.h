#pragma once
#include "GTEngine.h"

class Character : public Actor
{
private:
	InputManager* playerInput;
	int screenHeight = 1;
	int screenWidth = 1;
	float timeToShoot;

	bool playerGameOver = false;

public:
	Character(InputManager* input, int scHeight, int scWidth, float fireRate) 
		: playerInput(input), screenHeight(scHeight), screenWidth(scWidth), timeToShoot(fireRate)
	{
		onScreenChar = '>';
	}

	void BeginPlay(void) override;
	void Tick(float deltaTime) override;
	void OnCollision(Actor* collidedActor) override;

	bool GetGameOver(void);
	void ResetPlayer(void);

private:
	void Move(void);
	void Shoot(void);
};

