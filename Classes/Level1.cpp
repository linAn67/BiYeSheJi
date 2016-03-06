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

std::string Level1::getFilename()
{
	return "level1.json";
}

cocos2d::Point Level1::initialWorldOffset()
{
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

	m_groundBodys.push_back(json->getBodyByName("gruand"));
	m_groundBodys.push_back(json->getBodyByName("obstacleControl"));
	m_player = json->getBodyByName("player");

	rotateAngle = 0;

	addControllerLayer();


}

void Level1::addControllerLayer()
{
	Size winSize = Director::sharedDirector()->getWinSize();
	m_controllerLayer = ControllerLayer::create();
	//由于在初始化时的一些坐标转换，在添加精灵时需要根据转换后的layer进行一些坐标变换和大小缩放
	m_controllerLayer->setAnchorPoint(Vec2(0, 0));
	m_controllerLayer->setPosition(Vec2(-winSize.width / 2, -winSize.height / 2) / initialWorldScale());
	m_controllerLayer->setScale(m_controllerLayer->getScale() / initialWorldScale());
	addChild(m_controllerLayer,10);
}

void Level1::clear()
{
	RUBELayer::clear();
	m_groundBodys.clear();
	m_objectBodys.clear();
}

void Level1::update(float dt)
{
	m_controllerLayer->update(dt);

	rotateAngle = fmodf(rotateAngle, 360);

	if (rotateAngle != m_controllerLayer->m_rotateAngle){
		rotateObjectBody(m_player);
		for each (auto body in m_objectBodys)
		{
			rotateObjectBody(body);
		}
		rotateAngle = m_controllerLayer->m_rotateAngle;
		rotateAngle = fmodf(rotateAngle, 360);
	}


	rotateGroundBody();
	movePlayer();

	RUBELayer::update(dt);
}

void Level1::movePlayer()
{
	switch (m_controllerLayer->m_playerMoveDirection)
	{
	case PLAYER_MOVETOLEFT:
		m_player->SetTransform(m_player->GetPosition() - b2Vec2(0.025f, 0.0f), m_player->GetAngle());
		break;
	case PLAYER_MOVETORIGHT:
		m_player->SetTransform(m_player->GetPosition() + b2Vec2(0.025f, 0.0f), m_player->GetAngle());
		break;
	case PLAYER_NOTMOVE:
		break;
	default:
		break;
	}
}

void Level1::rotateGroundBody()
{
	for each (auto groundBody in m_groundBodys)
	{
		groundBody->SetTransform(groundBody->GetPosition(), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle));
	}
}

void Level1::rotateObjectBody(b2Body* body)
{
	Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
	bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));
	body->SetTransform(b2Vec2(bodyPos.x, bodyPos.y), 0);
}

