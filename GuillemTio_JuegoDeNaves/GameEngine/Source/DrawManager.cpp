#include "GTEngine.h"
#include <iostream>
#include <string>

void DrawManager::InitializeMatrix(char c)
{
	if (matrix != nullptr)
	{
		for (size_t h = 0; h < height; h++)
		{
			for (size_t w = 0; w < width; w++)
			{
				matrix[h][w] = c;
			}
		}
	}
	else
	{
		std::cerr << "(InitializeMatrix) ojo que la matriz no está creada!!";
	}
}

void DrawManager::PrintMatrix(void)
{
	ClearScreen();

	if (matrix != nullptr)
	{
		for (size_t h = 0; h < height; h++)
		{
			for (size_t w = 0; w < width; w++)
			{
				std::cout << matrix[h][w];
			}
			std::cout << std::endl;
		}
	}
	else
	{
		std::cerr << "(PrintMatrix) ojo que la matriz no está creada!!";
	}
}

void DrawManager::ClearScreen(void)
{
	system("cls");
}

void DrawManager::SetCharInPosition(char c, int h, int w)
{
	if (matrix != nullptr)
	{
		if (h >= 0 && h < height)
		{
			char* fila = matrix[h];
			if (fila != nullptr && w >= 0 && w < width)
			{
				fila[w] = c;
			}
		}
		else
		{
			std::cerr << "el alto o el ancho se salen del tamaño de la matriz..";
		}
	}
	else
	{
		std::cerr << "matrix no inicializada";
	}
}

void DrawManager::DrawBoard(void)
{
	SetCharInPosition(201, 0, 0);
	DrawCharsInLine(205, 0, 1, width - 2);
	SetCharInPosition(187, 0, width - 1);
	DrawCharsInColumn(186, 0, 1, height - 2);
	DrawCharsInColumn(186, width - 1, 1, height - 2);
	SetCharInPosition(200, height - 1, 0);
	DrawCharsInLine(205, height - 1, 1, width - 2);
	SetCharInPosition(188, height - 1, width - 1);

}

void DrawManager::DrawGameOverBoard(int wide, int tall)
{
	if (wide < width && tall < height)
	{
		int middleHPosition = height / 2;
		int middleWPosition = width / 2;

		for (size_t i = middleHPosition - (tall / 2); i < middleHPosition + (tall / 2); i++)
		{
			for (size_t j = middleWPosition - (wide / 2); j < middleWPosition + (wide / 2); j++)
			{
				matrix[i][j] = ' ';
			}
		}


		SetCharInPosition(219, middleHPosition-(tall/2), middleWPosition-(wide/2));
		DrawCharsInLine(205, middleHPosition - (tall / 2), middleWPosition - (wide / 2)+1, middleWPosition + (wide / 2) -1);
		SetCharInPosition(219, middleHPosition - (tall / 2), middleWPosition + (wide / 2));
		DrawCharsInColumn(179, middleWPosition - (wide / 2), middleHPosition - (tall / 2) + 1, middleHPosition + (tall / 2) -1);
		DrawCharsInColumn(179, middleWPosition + (wide / 2), middleHPosition - (tall / 2) + 1, middleHPosition + (tall / 2) - 1);
		SetCharInPosition(219, middleHPosition + (tall / 2), middleWPosition - (wide / 2));
		DrawCharsInLine(205, middleHPosition + (tall / 2), middleWPosition - (wide / 2) + 1, middleWPosition + (wide / 2) - 1);
		SetCharInPosition(219, middleHPosition + (tall / 2), middleWPosition + (wide / 2));
	}
	else
		std::cerr << "GameOver board demasiado grande";
}

void DrawManager::DrawGameOver(int currentScore, int wide, int tall)
{
	DrawGameOverBoard(wide, tall);
	DrawTextInPosition((char*)"GAME  OVER", 10, height/2 - 3, width/2 - 5);
	DrawTextInPosition((char*)"PUNTOS:", 7, height / 2 - 1, width / 2 - 6);
	DrawNumsInPosition(currentScore, height / 2 - 1, width / 2 + 2);
	DrawTextInPosition((char*)"Press spacebar to restart", 25, height / 2 + 2, width / 2 - 12);
}

void DrawManager::DrawScoreSeparator(void)
{
	SetCharInPosition(204, 2, 0);
	DrawCharsInLine(205, 2, 1, width - 2);
	SetCharInPosition(185, 2, width - 1);
}

void DrawManager::DrawScoreTitles(void)
{
	if (hasScore)
	{
		DrawTextInPosition((char*)"PUNTUACION:", 11, 1, 4);
		DrawTextInPosition((char*)"RECORD:", 7, 1, 65);
	}
	else
		std::cerr << "score not set!";
}

void DrawManager::DrawScoreNumbers(int currentScore, int highScore)
{
	if (hasScore)
	{
		DrawNumsInPosition(currentScore, 1, 16);
		DrawNumsInPosition(highScore, 1, 73);
	}
	else
		std::cerr << "score not set!";
}

void DrawManager::ResetCurrentScore()
{
	DrawCharsInLine(initializeCharacter, 1, 16, 50);
}

void DrawManager::DrawCharsInLine(char c, int heightLine, int startPosition, int endPosition)
{
	if(heightLine <= height && heightLine >= 0)
	{
		for (size_t i = startPosition; i <= endPosition; i++)
		{
			matrix[heightLine][i] = c;
		}
	}
	else 
		std::cerr << "Wrong Height!";
}

void DrawManager::DrawCharsInColumn(char c, int widthColumn, int startPosition, int endPosition)
{
	if (widthColumn < width && widthColumn >= 0)
	{
		for (size_t i = startPosition; i <= endPosition; i++)
		{
			matrix[i][widthColumn] = c;
		}
	}
	else
		std::cerr << "Wrong Width!";
}

void DrawManager::DrawTextInPosition(char* c, int charLength, int h, int w)
{
	if (matrix != nullptr)
	{
		if (h >= 0 && h < height)
		{
			char* fila = matrix[h];
			if (fila != nullptr)
			{
				for (size_t i = 0; i < charLength; i++)
				{
					fila[w+i] = c[i];
				}
			}
		}
		else
		{
			std::cerr << "el alto o el ancho se salen del tamaño de la matriz";
		}
	}
	else
	{
		std::cerr << "matrix no inicializada";
	}
}

void DrawManager::DrawNumsInPosition(int toDraw, int h, int w)
{
	if (matrix != nullptr)
	{
		if (h >= 0 && h < height)
		{
			char* fila = matrix[h];
			if (fila != nullptr)
			{
				std::string chars = std::to_string(toDraw);
				int charLength = chars.length();

				for (size_t i = 0; i < charLength; i++)
				{
					fila[w + i] = chars[i];
				}
			}
		}
		else
		{
			std::cerr << "el alto o el ancho se salen del tamaño de la matriz";
		}
	}
	else
	{
		std::cerr << "matrix no inicializada";
	}
}

void DrawManager::DrawActor(Actor* actor)
{
	SetCharInPosition(actor->onScreenChar, actor->posY, actor->posX);
}

