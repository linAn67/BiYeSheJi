#include "Level1.h"
#include "rubestuff/b2dJson.h"
#include "ControllerLayer.h"


using namespace std;
using namespace cocos2d;
using namespace ui;

Scene* Level1::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene

	//蓝色背景
	Color4B c4b = Color4B(104, 171, 213, 255);
	LayerColor* layer2 = LayerColor::create(c4b);
	scene->addChild(layer2);


	Level1* layer = new Level1();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();


	return scene;
}

Level1::Level1()
{

}

std::string Level1::getFilename()
{
	return "level1.json";
}

cocos2d::Point Level1::initialWorldOffset()
{
	//place (0,0) of physics world at center of bottom edge of screen
	Size s = Director::getInstance()->getWinSize();
	return Vec2(s.width / 2, s.height / 2);
}

float Level1::initialWorldScale()
{
	Size s = Director::getInstance()->getWinSize();
	return s.height / 8; //screen will be 8 physics units high
}

void Level1::afterLoadProcessing(b2dJson* json)
{
	RUBELayer::afterLoadProcessing(json);

	m_backgroundBody = json->getBodyByName("gruand");
	m_obstacleControl = json->getBodyByName("obstacleControl");
	m_player = json->getBodyByName("player");


	addControllerLayer();

}

void Level1::addControllerLayer()
{
	Size winSize = Director::sharedDirector()->getWinSize();
	m_controlLayer = ControllerLayer::create();
	//由于在初始化时的一些坐标转换，在添加精灵时需要根据转换后的layer进行一些坐标变换和大小缩放
	m_controlLayer->setAnchorPoint(Vec2(0, 0));
	m_controlLayer->setPosition(Vec2(-winSize.width / 2, -winSize.height / 2) / initialWorldScale());
	m_controlLayer->setScale(m_controlLayer->getScale() / initialWorldScale());
	addChild(m_controlLayer,10);
}

void Level1::clear()
{
	RUBELayer::clear();
}

void Level1::update(float dt)
{
	RUBELayer::update(dt);
	m_controlLayer->update(dt);

// 	m_backgroundBody->rotateAroundExternalPoint(0, 0, CC_DEGREES_TO_RADIANS(0.01));
// 	m_obstacleControl->rotateAroundExternalPoint(0, 0, CC_DEGREES_TO_RADIANS(0.01));

	float32 rotateAngle = m_controlLayer->m_rotateAngle;
	m_backgroundBody->SetTransform(m_backgroundBody->GetPosition(), CC_DEGREES_TO_RADIANS(rotateAngle));
	m_obstacleControl->SetTransform(m_obstacleControl->GetPosition(), CC_DEGREES_TO_RADIANS(rotateAngle));

	

	switch (m_controlLayer->m_playerMoveDirection)
	{
	case PLAYER_MOVETOLEFT:
		m_player->SetTransform(m_player->GetPosition() - b2Vec2(0.025, 0), m_player->GetAngle());
		break;
	case PLAYER_MOVETORIGHT:
		m_player->SetTransform(m_player->GetPosition() + b2Vec2(0.025, 0), m_player->GetAngle());
		break;
	case PLAYER_NOTMOVE:
		break;
	default:
		break;
	}

	setImagePositionsFromPhysicsBodies();
}


