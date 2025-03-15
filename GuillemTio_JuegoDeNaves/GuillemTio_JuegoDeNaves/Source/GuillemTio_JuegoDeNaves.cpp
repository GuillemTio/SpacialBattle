#include <iostream>
#include "JuegoDeNaves_GameEngine.h"

int main()
{
    int framesPerSecond = 2;
    int screenHeight = 33;
    int screenWidth = 94;

    JuegoDeNaves_GameEngine* engine = new JuegoDeNaves_GameEngine(framesPerSecond, screenHeight, screenWidth);
    engine->Start();
}
