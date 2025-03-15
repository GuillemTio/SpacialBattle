#include "JuegoDeNaves_WaveManager.h"
#include "Enemy.h"
#include "GTEngine.h"
#include <iostream>
#include "TinyXML2/tinyxml2.h"

using namespace tinyxml2;

void JuegoDeNaves_WaveManager::UpdateWave(float deltaTime)
{
	waveTime += deltaTime;
	for (Wave w : waves) 
	{
		if(w.number == currentWave)
		{
			for (size_t i = currentWaveSpawn; i <= w.spawns.size(); i++)
			{
				if (w.spawns.at(i-1).spawnTime <= waveTime)
				{
					for (EnemyProperties ep : enemyTypes)
					{
						if(ep.type == w.spawns.at(i-1).enemyType)
						{
							CreateEnemy(ep, w.spawns.at(i-1).yPercentage);
							break;
						}
					}

					currentWaveSpawn++;

					if (currentWaveSpawn > w.spawns.size())
					{
						waveTime = -timeBetweenWaves;
						currentWave++;
						currentWaveSpawn = 1;
					}
						
				}
				else
					break;

			}

			break;
		}
	}

	if (!wavesFinished && (currentWave > waves.size()))
	{
		wavesFinished = true;
	}
}

void JuegoDeNaves_WaveManager::ResetWaveManager(void)
{
	waveTime = 0;
	wavesFinished = false;
	currentWave = 1;
	currentWaveSpawn = 1;
}

void JuegoDeNaves_WaveManager::CreateEnemy(EnemyProperties ep, int yPercentage)
{
	int yPos = ((height-3) / 100.0f * yPercentage) + 3; // sumo y resto la parte de la pantalla no jugable
	Enemy* enemy = new Enemy(ep.health, ep.speed, ep.sprite, ep.pointsGiven, yPos, width-1);
	engine->AddActor(enemy);
}

void JuegoDeNaves_WaveManager::InitializeFile(void)
{
	XMLDocument doc;
	doc.LoadFile("Resources/EnemyWaves.xml");

	if (doc.ErrorID() == 0)
	{
		XMLElement* start = doc.FirstChildElement("EnemyWaves");

		XMLElement* enemies = start->FirstChildElement("Enemies");

		XMLElement* enemy = enemies->FirstChildElement("Enemy");

		while (enemy)
		{
			EnemyProperties en;

			en.type = enemy->IntAttribute("type");
			en.sprite = enemy->Attribute("sprite")[0];
			en.health = enemy->IntAttribute("health");
			en.speed = enemy->IntAttribute("speed");
			en.pointsGiven = enemy->IntAttribute("points");

			enemyTypes.push_back(en);

			enemy = enemy->NextSiblingElement("Enemy");
		}

		XMLElement* waveElement = start->FirstChildElement("Waves")->FirstChildElement("Wave");
		while (waveElement)
		{
			Wave wave;
			wave.number = waveElement->IntAttribute("number");

			XMLElement* spawn = waveElement->FirstChildElement("Spawn");

			while(spawn)
			{
				SpawnProperties sp;
				sp.enemyType = spawn->IntAttribute("enemy");
				sp.yPercentage = spawn->IntAttribute("yPercentage");
				sp.spawnTime = spawn->IntAttribute("time");
				wave.spawns.push_back(sp);
				spawn = spawn->NextSiblingElement("Spawn");
			}

			waves.push_back(wave);
			waveElement = waveElement->NextSiblingElement("Wave");
		}

	}
	else
		std::cerr << "Errors in XML doc";
}
