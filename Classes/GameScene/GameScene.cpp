#include "GameScene/GameScene.h"
#include "GameData/GameManager.h"
#include "GameLevel/BasicLevelLayer.h"
#include "GameLevel/Level1.h"
#include "GameLevel/Level2.h"
#include "GameLevel/Level3.h"
#include "GameLevel/Level4.h"

USING_NS_CC;


cocos2d::Scene* GameScene::createScene(int Level)
{
	GameManager::getInstance()->curLevel = Level;
	Scene* scene;
	switch (Level)
	{
	case(1) : 
		scene = Level1::createScene(); 
		break;
	case(2) : 
		scene = Level2::createScene();
		break;
	case(3) : 
		scene = Level3::createScene();
		break;
	case(4) :
		scene = Level4::createScene();
		break;
	}

	return scene;
}
