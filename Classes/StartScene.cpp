#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

USING_NS_CC;


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

	auto rootNode = CSLoader::createNode("StartScene.csb");
	addChild(rootNode);

	Button* startBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode,"StartBtn");
	startBtn->addTouchEventListener(CC_CALLBACK_2(StartScene::touchEvent, this));


	return true;
}

void StartScene::touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto scene = StartScene::createScene();
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