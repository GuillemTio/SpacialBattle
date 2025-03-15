#pragma once
#include "vector"
#include <functional>

class GameEngine;

struct EnemyProperties {
	int type;
	char sprite;
	int health;
	int speed;
	int pointsGiven;
};

struct SpawnProperties {
	int enemyType;
	int yPercentage;
	int spawnTime;
};

struct Wave {
	int number;
	std::vector<SpawnProperties> spawns;
};

class JuegoDeNaves_WaveManager
{
public:
	bool wavesFinished = false;

private:
	float waveTime = 0.0;
	int currentWave = 1;
	int currentWaveSpawn = 1;
	int timeBetweenWaves = 0;

	int height = 1, width = 1;
	GameEngine* engine;

	std::vector<EnemyProperties> enemyTypes;
	std::vector<SpawnProperties> waveSpawns;
	std::vector<Wave> waves;

public:
	JuegoDeNaves_WaveManager(int height, int width, int timeBetweenWaves, GameEngine* engine) 
		: height(height), width(width), timeBetweenWaves(timeBetweenWaves), engine(engine)
	{
		InitializeFile();
	}

	void UpdateWave(float deltaTime);
	void ResetWaveManager(void);

private:
	void CreateEnemy(EnemyProperties ep, int yPercentage);
	void InitializeFile(void);
};

