#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_
#include "cocos2d.h"

class GameManager
{
public:

	static GameManager* getInstance();

	int curLevel;

private:
	static GameManager * instance;
};

#endif