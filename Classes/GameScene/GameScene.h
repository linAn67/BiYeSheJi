#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:	
	static cocos2d::Scene* createScene(int Level);
	static void replaceScene(int Level);
	static cocos2d::Scene* getNextLevel();

};

#endif