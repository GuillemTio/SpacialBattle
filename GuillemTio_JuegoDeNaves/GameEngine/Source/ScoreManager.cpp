#include "GTEngine.h"

void ScoreManager::AddScore(int points)
{
	currentScore += points;

	CheckHighScore();
}

int ScoreManager::GetHighScore(void)
{
	return highScore;
}

int ScoreManager::GetCurrentScore(void)
{
	return currentScore;
}

void ScoreManager::ResetGameScore(void)
{
	currentScore = 0;
}

void ScoreManager::CheckHighScore(void)
{
	if (highScore < currentScore)
	{
		highScore = currentScore;
		SaveHighScore(); // Guardado constante, gasta más recursos pero aunque se cierre partida a medias se queda la highscore
	}
}

void ScoreManager::SaveHighScore(void)
{
	std::ifstream hFileIn(highscoreFileRoute);

	if (hFileIn.is_open()) {
		int oldHighScore = 0;
		hFileIn >> oldHighScore;

		if (highScore > oldHighScore)
		{
			std::ofstream hFileOut(highscoreFileRoute, std::ofstream::trunc);
			
			if (hFileOut.is_open())
			{
				hFileOut << highScore;
				hFileOut.close();
			}
		}

		hFileIn.close();
	}
}

void ScoreManager::LoadHighScore(void)
{
	std::ifstream hFile(highscoreFileRoute);
	if (hFile.is_open()) {
		hFile >> highScore;
		hFile.close();
	}
}
