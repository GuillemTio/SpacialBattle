#include "GTEngine.h"

GameEngine* GameEngine::instance = nullptr;

void GameEngine::DestroyActor(Actor* actor)
{
	actorsList.erase(std::remove(actorsList.begin(), actorsList.end(), actor), actorsList.end());
	delete actor;
}

void GameEngine::CollisionManager(void)
{
	for (size_t i = 0; i < actorsList.size(); i++)
	{
		for (size_t j = i + 1; j < actorsList.size(); j++)
		{
			if ((actorsList[i]->posX == actorsList[j]->posX) && (actorsList[i]->posY == actorsList[j]->posY))
			{
				actorsList[i]->OnCollision(actorsList[j]);
				actorsList[j]->OnCollision(actorsList[i]);
			}
		}
	}
}