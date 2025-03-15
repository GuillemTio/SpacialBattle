#include "JuegoDeNaves_DrawManager.h"

void JuegoDeNaves_DrawManager::DrawUpperLine(void)
{
	SetCharInPosition(204, 3, 0);
	DrawCharsInLine(205, 3, 1, width - 2);
	SetCharInPosition(185, 3, width - 1);
}

void JuegoDeNaves_DrawManager::DrawExplosion(int height, int width)
{
	SetCharInPosition(47, height - 1, width + 1);
	SetCharInPosition(47, height + 1, width - 1);
	SetCharInPosition(92, height - 1, width - 1);
	SetCharInPosition(92, height + 1, width + 1);
	DrawCharsInColumn(124, width, height - 1, height + 1);
	DrawCharsInLine(196, height, width - 1, width + 1);
	SetCharInPosition('o', height, width);
}

void JuegoDeNaves_DrawManager::ClearGameScreen(void)
{
	for (size_t h = 4; h < height - 1; h++)
	{
		for (size_t w = 1; w < width - 1; w++)
		{
			matrix[h][w] = initializeCharacter;
		}
	}
	DrawBoard();
	DrawUpperLine();
}
