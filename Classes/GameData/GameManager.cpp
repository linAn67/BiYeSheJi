#include "GameData/GameManager.h"

GameManager* GameManager::instance;

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
		instance = new GameManager();
	return instance;
}
