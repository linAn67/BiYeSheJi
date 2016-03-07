#include "ControllerLayer.h"
#include "Level1.h"
const float rotateDegree = 1.4f;

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
	leftMoveBtn->setOpacity(200);
	Button* rightMoveBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "RightMoveBtn");
	rightMoveBtn->setOpacity(200);
	rightMoveBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::moveToRight, this));

	Button* antiClockwiseBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "AntiClockwiseBtn");
	antiClockwiseBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::antiClockwiseRotate, this));
	Button* clockwiseBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "ClockwiseBtn");
	clockwiseBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::clockwiseRotate, this));

	Button* confirmBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "ConfirmBtn");
	confirmBtn->addTouchEventListener(CC_CALLBACK_2(ControllerLayer::confirmBtnCallBack, this));

	m_rotationDirection = RD_NOTROTATING;
	m_playerMoveDirection = PLAYER_NOTMOVING;
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
	case Widget::TouchEventType::MOVED:
		m_playerMoveDirection = PLAYER_MOVETOLEFT;
		break;
	default:
		m_playerMoveDirection = PLAYER_NOTMOVING;
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
	case Widget::TouchEventType::MOVED:
		m_playerMoveDirection = PLAYER_MOVETORIGHT;
		break;
	default:
		m_playerMoveDirection = PLAYER_NOTMOVING;
		break;
	}
}


void ControllerLayer::clockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_rotationDirection = RD_CLOCKWISE;
		break;
	case Widget::TouchEventType::MOVED:
		m_rotationDirection = RD_CLOCKWISE;
		break;
	case Widget::TouchEventType::CANCELED:
		m_rotationDirection = RD_NOTROTATING;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_rotationDirection = RD_NOTROTATING;
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
		m_rotationDirection = RD_ANTICLOCKWISE;
		break;
	case Widget::TouchEventType::MOVED:
		m_rotationDirection = RD_ANTICLOCKWISE;
		break;
	case Widget::TouchEventType::CANCELED:
		m_rotationDirection = RD_NOTROTATING;
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_rotationDirection = RD_NOTROTATING;
		break;
	default:
		break;
	}
}

void ControllerLayer::update(float delta)
{
	switch (m_rotationDirection)
	{
	case RD_CLOCKWISE:
		m_rotateAngle += rotateDegree;
		break;
	case RD_ANTICLOCKWISE:
		m_rotateAngle -= rotateDegree;
		break;
	case RD_NOTROTATING:
		break;
	default:
		break;
	}
}

void ControllerLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m_rotationDirection = RD_ANTICLOCKWISE;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_rotationDirection = RD_CLOCKWISE;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_playerMoveDirection = PLAYER_MOVETOLEFT;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_playerMoveDirection = PLAYER_MOVETORIGHT;
		break;
	default:
		break;
	}

}

void ControllerLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m_rotationDirection = RD_NOTROTATING;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_rotationDirection = RD_NOTROTATING;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_playerMoveDirection = PLAYER_NOTMOVING;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		m_playerMoveDirection = PLAYER_NOTMOVING;
		break;
	default:
		break;
	}
}

void ControllerLayer::confirmBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (m_layer->m_isPlayerCollideWithDoor&&m_layer->m_allKeys.size() == 0)
		{
			m_layer->win();
		}
		break;
	default:
		break;
	}
	
}

