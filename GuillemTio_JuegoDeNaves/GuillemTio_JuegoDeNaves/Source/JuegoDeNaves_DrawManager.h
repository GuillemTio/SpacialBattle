#pragma once
#include "GTEngine.h"

class JuegoDeNaves_DrawManager : public DrawManager
{

public: 
	JuegoDeNaves_DrawManager(int height, int width, bool drawScore = false) : DrawManager(height, width, drawScore)
	{
		DrawUpperLine();
	}

	void DrawUpperLine(void);

	void DrawExplosion(int height, int width);

	void ClearGameScreen(void);
		
};

