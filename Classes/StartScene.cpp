#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BasicLevelLayer.h"
#include "SimpleAudioEngine.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

USING_NS_CC;
using namespace CocosDenshion;

using namespace ui;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("startscene/StartScene.csb");
	addChild(rootNode);

	Button* startBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode,"StartBtn");
	startBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::touchEvent, this));

	// preload the sound effects
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/Haggstrom.mp3");
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	
	return true;
}

void StartScene::touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto scene = Level1::createScene();
	scene = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		director->replaceScene(scene);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}