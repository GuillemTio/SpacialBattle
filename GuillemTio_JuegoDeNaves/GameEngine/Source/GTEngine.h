#pragma once
#include <time.h>
#include <fstream>
#include "vector"

struct Object
{
	int posX, posY;
};

struct Actor : Object 
{
	char onScreenChar;
	bool destroyed = false;

	virtual void BeginPlay(void) = 0;
	virtual void Tick(float deltaTime) = 0;
	virtual void OnCollision(Actor* collidedActor) { };
};

class DrawManager
{
public:
	int height = 1, width = 1;

protected:
	bool hasScore = false;
	char initializeCharacter = ' ';
	char** matrix = nullptr;


protected:
	DrawManager() {}

public:
	DrawManager(int height, int width, bool drawScore = false) : height(height), width(width), hasScore(drawScore)
	{
		matrix = new char* [height];
		for (size_t i = 0; i < height; i++)
		{
			matrix[i] = new char[width];
		}

		InitializeMatrix(initializeCharacter);

		DrawBoard();
		if (hasScore) 
		{
			DrawScoreSeparator();
			DrawScoreTitles();
		}

	}

	~DrawManager()
	{
		for (size_t i = 0; i < height; i++)
		{
			delete matrix[i];
		}

		delete matrix;
	}

	void InitializeMatrix(char c);

	void PrintMatrix(void);

	void ClearScreen(void);

	void SetCharInPosition(char c, int h, int w);

	void DrawBoard(void);
	void DrawGameOverBoard(int wide, int tall);

	void DrawGameOver(int currentScore, int wide, int tall);

	void DrawScoreSeparator(void);
	void DrawScoreTitles(void);
	void DrawScoreNumbers(int currentScore, int highScore);
	void ResetCurrentScore(void);

	void DrawCharsInLine(char c, int heightLine, int startPosition, int endPosition);
	void DrawCharsInColumn(char c, int widthColumn, int startPosition, int endPosition);

	void DrawTextInPosition(char* c, int charLength, int h, int w);
	void DrawNumsInPosition(int toDraw, int h, int w);

	void DrawActor(Actor* actor);
};

class InputManager
{
private:
	static const int KEY_COUNT = 256;

	bool keyStates[KEY_COUNT] = { false };
	int keyPressedCount[KEY_COUNT] = { 0 };

	int* lettersPressed = new int[25];

	int lastArrowKeyPressed;

private:
	void CheckLettersPressed(void);

public:

	bool IsKeyDown(int key);

	void UpdateInput(void);
	void UpdateLastArrowKeyPressed(void);

	int* GetLettersPressed(void);

	void ResetKeyCount(void);

	int GetLastArrowKeyPressed(void);
	int GetLastArrowKeyPressedAndReset(void);
	void SetLastArrowKey(int arrowKey);

};

class ScoreManager
{
private:
	int currentScore = 0;
	int highScore = 0;

	const std::string highscoreFileRoute = "Resources/highscore.txt";

public:
	ScoreManager()
	{
		LoadHighScore();
	}

	void AddScore(int points);
	int GetHighScore(void);
	int GetCurrentScore(void);
	void ResetGameScore(void);

	void CheckHighScore(void);
	void SaveHighScore(void);
	void LoadHighScore(void);

};

class TimeManager
{
	clock_t previousFrameTimeSinceGameStarted = 0;
	float m_elapsedTime = 0.f;
	float desiredSecondsPerFrame = 1.0f;

public:
	TimeManager() {}
	TimeManager(float desiredSecondsPerFrame) : desiredSecondsPerFrame(desiredSecondsPerFrame)
	{
	}
	float GetElapsedTime(void) const;
	bool shouldExecuteNextFrame(void);
	void SetNewFrameTime(float newFrameTime)
	{
		desiredSecondsPerFrame = newFrameTime;
	}
};

class GameEngine
{
protected:
	bool exitGameLoop = false;
	bool gameOver = false;
	TimeManager* timeManager;
	ScoreManager* scoreManager;
	InputManager* inputManager;
	std::vector<Actor*> actorsList;

	static GameEngine* instance; // hago este "Singleton" para poder facilitar el acceso a la funcion de AddActor

protected:
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void GameLoop(void) = 0;
	
	virtual void CheckDestroyed(void) = 0;

public:
	GameEngine(int framesPerSecond)
	{
		timeManager = new TimeManager(1.0f / (float)framesPerSecond);

		scoreManager = new ScoreManager();

		inputManager = new InputManager();

		instance = this;
	}

	~GameEngine() {
		delete timeManager;
		delete scoreManager;
		delete inputManager;

		for(Actor* actor : actorsList)
		{
			delete actor;
		}
	}

	virtual void Start(void) = 0;

	void DestroyActor(Actor* actor);
	static void AddActor(Actor* actor)
	{
		if (instance)
		{
			instance->actorsList.push_back(actor);
			actor->BeginPlay();
		}
	}

	void CollisionManager(void);
};


