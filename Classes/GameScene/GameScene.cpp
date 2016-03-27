#include "GameScene/GameScene.h"
#include "GameData/GameManager.h"
#include "GameLevel/BasicLevelLayer.h"
#include "GameLevel/Level1.h"
#include "GameLevel/Level2.h"
#include "GameLevel/Level3.h"
#include "GameLevel/Level4.h"
#include "GameLevel/Level5.h"
#include "GameLevel/Level6.h"
#include "GameLevel/Level7.h"
#include "GameLevel/Level8.h"

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
	case(5) :
		scene = Level5::createScene();
		break;
	case(6) :
		scene = Level6::createScene();
		break;
	case(7) :
		scene = Level7::createScene();
		break;
	case(8) :
		scene = Level8::createScene();
		break;
	default:
		CCLOG("error");
		break;
	}

	return scene;
}

void GameScene::replaceScene(int Level)
{
	auto director = Director::getInstance();
	auto scene = GameScene::createScene(Level);
	scene = TransitionFade::create(1.0f, scene, Color3B::BLACK);
	director->replaceScene(scene);
}
