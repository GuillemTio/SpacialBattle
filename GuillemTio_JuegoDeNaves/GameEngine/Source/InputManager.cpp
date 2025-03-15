#include "GTEngine.h"
#include <windows.h>
#include <iostream>

void InputManager::CheckLettersPressed(void)
{
    int letterIndex = 0;
    for (size_t i = 65; i <= 90; i++) // hex a decimal key-codes de las letras
    {
        lettersPressed[letterIndex] = keyPressedCount[i];
        letterIndex++;
    }
}

bool InputManager::IsKeyDown(int key)
{
    if (key >= 0 && key <= 255)
        return GetKeyState(key) & 0x8000;
    else
        return false;
}

void InputManager::UpdateInput(void)
{
    for (size_t i = 0; i < KEY_COUNT; i++)
    {
        bool currentlyPressed = (GetAsyncKeyState(i) & 0x8000) != 0;

        if (currentlyPressed && !keyStates[i]) {
            keyPressedCount[i]++;
        }

        keyStates[i] = currentlyPressed;
    }
}

void InputManager::UpdateLastArrowKeyPressed(void)
{
    static bool prevLeft = false;
    static bool prevRight = false;
    static bool prevUp = false;
    static bool prevDown = false;

    bool left = GetAsyncKeyState(VK_LEFT) & 0x8000; //uso async para mejor precision
    bool right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
    bool up = GetAsyncKeyState(VK_UP) & 0x8000;
    bool down = GetAsyncKeyState(VK_DOWN) & 0x8000;

    if (left && !prevLeft) lastArrowKeyPressed = VK_LEFT;
    if (right && !prevRight) lastArrowKeyPressed = VK_RIGHT;
    if (up && !prevUp) lastArrowKeyPressed = VK_UP;
    if (down && !prevDown) lastArrowKeyPressed = VK_DOWN;

    prevLeft = left;
    prevRight = right;
    prevUp = up;
    prevDown = down;
}

int* InputManager::GetLettersPressed(void)
{
    CheckLettersPressed();
    return lettersPressed;
}

void InputManager::ResetKeyCount(void)
{
    for (size_t i = 0; i < KEY_COUNT; i++)
    {
        keyPressedCount[i] = 0;
    }
}

int InputManager::GetLastArrowKeyPressed(void) 
{
    return lastArrowKeyPressed;
}

int InputManager::GetLastArrowKeyPressedAndReset(void)
{
    int key = lastArrowKeyPressed;
    lastArrowKeyPressed = 0;
    return key;
}

void InputManager::SetLastArrowKey(int arrowKey)
{
    lastArrowKeyPressed = arrowKey;
}
