#include "JuegoDeNaves_GameEngine.h"
#include "Enemy.h"
#include <windows.h>
#include <iostream>

void JuegoDeNaves_GameEngine::GameLoop(void)
{
	while (!exitGameLoop)
	{
		inputManager->UpdateLastArrowKeyPressed();

		if (timeManager->shouldExecuteNextFrame())
		{
			if (!gameOver)
			{
				drawManager->ClearGameScreen();
				Update();
				CollisionManager();
				CheckDestroyed();
				CheckGameOver();
			}
			Draw();
		}

		exitGameLoop = inputManager->IsKeyDown(VK_ESCAPE);

		if (gameOver && inputManager->IsKeyDown(VK_SPACE)) 
		{
			gameOver = false;

			drawManager->ClearGameScreen();
			scoreManager->ResetGameScore();
			drawManager->ResetCurrentScore();
			mainCharacter->ResetPlayer();
			ResetActors();
			waveManager->ResetWaveManager();
		}
	}
}

void JuegoDeNaves_GameEngine::Update(void)
{

	waveManager->UpdateWave(timeManager->GetElapsedTime());

	for (size_t i = 0; i < actorsList.size(); i++)
	{
		actorsList[i]->Tick(timeManager->GetElapsedTime());
	}
	
}

void JuegoDeNaves_GameEngine::Draw(void)
{
	if (gameOver)
	{
		drawManager->DrawGameOver(scoreManager->GetCurrentScore(), 35, 10);
	}
	else
	{
		for (Actor* actor : actorsList)
		{
			drawManager->DrawActor(actor);
		}
	}

	drawManager->DrawScoreNumbers(scoreManager->GetCurrentScore(), scoreManager->GetHighScore());
	drawManager->PrintMatrix();
}

void JuegoDeNaves_GameEngine::CheckDestroyed(void)
{
	for (size_t i = 0; i < actorsList.size(); i++)
	{
		if (actorsList[i]->destroyed)
		{
			if (dynamic_cast<Enemy*>(actorsList[i]))
			{
				if (((Enemy*)actorsList[i])->killedByPlayer)
				{
					scoreManager->AddScore(((Enemy*)actorsList[i])->pointsGiven);
					drawManager->DrawExplosion(actorsList[i]->posY, actorsList[i]->posX);
				}
			}
			DestroyActor(actorsList[i]);

			i--;
		}
	}
}

void JuegoDeNaves_GameEngine::CheckGameOver(void)
{
	gameOver = mainCharacter->GetGameOver() || (waveManager->wavesFinished && !EnemiesLeft());
}

void JuegoDeNaves_GameEngine::ResetActors(void)
{
	for (size_t i = 0; i < actorsList.size(); i++)
	{
		if (!dynamic_cast<Character*>(actorsList[i]))
		{
			DestroyActor(actorsList[i]);

			i--;
		}
	}
}

bool JuegoDeNaves_GameEngine::EnemiesLeft(void)
{
	for (size_t i = 0; i < actorsList.size(); i++)
	{
		if (dynamic_cast<Enemy*>(actorsList[i]))
		{
			return true;
		}
	}

	return false;
}


void JuegoDeNaves_GameEngine::Start(void)
{
	drawManager->DrawScoreNumbers(scoreManager->GetCurrentScore(), scoreManager->GetHighScore());
	AddActor(mainCharacter);
	GameLoop();
}
