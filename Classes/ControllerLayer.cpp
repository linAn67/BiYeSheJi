#include "ControllerLayer.h"



USING_NS_CC;


using namespace ui;

Scene* ControllerLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ControllerLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ControllerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("res/LayerController.csb");
	addChild(rootNode);

	Button* leftMoveBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "LeftMoveBtn");
	leftMoveBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::moveToLeft, this));
	Button* rightMoveBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "RightMoveBtn");
	rightMoveBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::moveToRight, this));

	Button* antiClockwiseBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "AntiClockwiseBtn");
	antiClockwiseBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::antiClockwiseRotate, this));
	Button* clockwiseBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "ClockwiseBtn");
	clockwiseBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::clockwiseRotate, this));

	log("move");
	return true;
}


void ControllerLayer::moveToLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}

void ControllerLayer::moveToRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}


void ControllerLayer::clockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		log("haha");
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}

void ControllerLayer::antiClockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	default:
		break;
	}
}
