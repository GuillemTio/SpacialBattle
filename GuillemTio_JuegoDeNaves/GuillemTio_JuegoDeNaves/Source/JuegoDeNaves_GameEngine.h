#pragma once
#include "GTEngine.h"
#include "JuegoDeNaves_DrawManager.h"
#include "JuegoDeNaves_WaveManager.h"
#include "Character.h"

class JuegoDeNaves_GameEngine : GameEngine
{
private:
	JuegoDeNaves_DrawManager* drawManager;
	JuegoDeNaves_WaveManager* waveManager;

	Character* mainCharacter;

protected:
	void Update(void) override;
	void Draw(void) override;
	void GameLoop(void) override;

	void CheckDestroyed(void) override;
	void CheckGameOver(void);
	void ResetActors(void);

	bool EnemiesLeft(void);

public:
	JuegoDeNaves_GameEngine(int framesPerSecond, int screenHeight, int screenWidth) 
		: GameEngine(framesPerSecond)
	{
		drawManager = new JuegoDeNaves_DrawManager(screenHeight, screenWidth, true);
		waveManager = new JuegoDeNaves_WaveManager(screenHeight, screenWidth, 10, this);
		mainCharacter = new Character(inputManager, screenHeight, screenWidth, 1);
	}

	~JuegoDeNaves_GameEngine()
	{
		ResetActors();
		delete drawManager;
		delete waveManager;
		delete mainCharacter;
	}

	void Start(void) override;
};

