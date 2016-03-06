#include "ControllerLayer.h"

const float rotateDegree = 0.4f;

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

	m_rotationDirection = NOTROTATING;
	m_playerMoveDirection = PLAYER_NOTMOVE;
	m_rotateAngle = 0;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ControllerLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(ControllerLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}


void ControllerLayer::moveToLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_playerMoveDirection = PLAYER_MOVETOLEFT;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_playerMoveDirection = PLAYER_NOTMOVE;
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
		m_playerMoveDirection = PLAYER_MOVETORIGHT;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_playerMoveDirection = PLAYER_NOTMOVE;
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
		m_rotationDirection = CLOCKWISE;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_rotationDirection = NOTROTATING;
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
		m_rotationDirection = ANTICLOCKWISE;
		break;
	case Widget::TouchEventType::MOVED:
		m_rotationDirection = NOTROTATING;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_rotationDirection = NOTROTATING;
		break;
	default:
		break;
	}
}

void ControllerLayer::update(float delta)
{
	switch (m_rotationDirection)
	{
	case CLOCKWISE:
		m_rotateAngle += rotateDegree;
		break;
	case ANTICLOCKWISE:
		m_rotateAngle -= rotateDegree;
		break;
	case NOTROTATING:
		break;
	default:
		break;
	}
}

void ControllerLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode==EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_rotationDirection = ANTICLOCKWISE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_rotationDirection = CLOCKWISE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_playerMoveDirection = PLAYER_MOVETOLEFT;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		m_playerMoveDirection = PLAYER_MOVETORIGHT;
	}

}

void ControllerLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_rotationDirection = NOTROTATING;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_rotationDirection = NOTROTATING;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		m_playerMoveDirection = PLAYER_NOTMOVE;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		m_playerMoveDirection = PLAYER_NOTMOVE;
	}
}

