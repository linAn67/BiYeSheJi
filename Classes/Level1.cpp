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

void Level1::win()
{
	CCLOG("win");
	
}

std::string Level1::getFilename()
{
	return "level1-1.json";
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
	BasicRUBELayer::afterLoadProcessing(json);
	json->getBodiesByName("ground", m_groundBodys);
	m_player = json->getBodyByName("player");
	m_door = json->getBodyByName("door");
	m_isPlayerCollideWithDoor = false;
	m_groundBodys.push_back(m_door);
	loadKeys(json);
	//m_objectBodys.push_back(json->getBodyByName("obstacle"));

	rotateAngle = 0;

	addControllerLayer();
	addContactListener();

	test = (b2PrismaticJoint*)json->getJointByName("joint0");
}

void Level1::loadKeys(b2dJson* json)
{
	std::vector<b2Body*> keyBodys;
	json->getBodiesByName("key", keyBodys);
	for each (auto body in keyBodys)
	{
		BasicLevelBodyUserData* bud = new BasicLevelBodyUserData;
		m_allKeys.insert(bud);
		body->SetUserData(bud);

		bud->bodyType = BodyType_KEY;
		bud->body = body;
	}
}

void Level1::addContactListener()
{
	m_contactListener = new BasicLevelContactListener();
	m_world->SetContactListener(m_contactListener);
	m_contactListener->m_layer = this;
}

void Level1::addControllerLayer()
{
	auto director = Director::sharedDirector();
	Size winSize = director->getWinSize();
	m_controllerLayer = ControllerLayer::create();
	m_controllerLayer->m_layer = this;
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

	//旋转非场景的物件
	rotateAngle = fmodf(rotateAngle, 360);
	if (rotateAngle != m_controllerLayer->m_rotateAngle){
		rotateObjectBody(m_player);
		for each (auto body in m_objectBodys)
		{
			rotateObjectBody(body);
		}
		for each (auto bud in m_allKeys)
		{
			rotateObjectBody(bud->body);
		}
		rotateAngle = m_controllerLayer->m_rotateAngle;
		rotateAngle = fmodf(rotateAngle, 360);
	}
	rotateGroundBody();
	movePlayer();
	RUBELayer::update(dt);

	//遍历待处理的钥匙进行清除
	for each (auto bud in m_keyToProgress)
	{
		removeBodyFromWorld(bud->body);
		m_allKeys.erase(bud);
		delete bud;
	}
	//遍历完后要clear list
	m_keyToProgress.clear();
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
	case PLAYER_NOTMOVING:
		break;
	default:
		break;
	}
}

void Level1::rotateGroundBody()
{
	for each (auto body in m_groundBodys)
	{
		Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
		bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));

		//body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle));
		body->SetTransform(b2Vec2(bodyPos.x,bodyPos.y), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle));
	}
}

void Level1::rotateObjectBody(b2Body* body)
{
	Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
	bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));
	body->SetTransform(b2Vec2(bodyPos.x, bodyPos.y), body->GetAngle());
}

//////////////////////////////////////////////////////////////////////////
//
//							ContactListener
//
//////////////////////////////////////////////////////////////////////////

void BasicLevelContactListener::BeginContact(b2Contact* contact)
{
	Level1* layer = (Level1*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	BasicLevelBodyUserData* budA = (BasicLevelBodyUserData*)fA->GetBody()->GetUserData();
	BasicLevelBodyUserData* budB = (BasicLevelBodyUserData*)fB->GetBody()->GetUserData();
	
	if (budA && budA->bodyType == BodyType_KEY && fB->GetBody() == layer->m_player)
	{
		layer->m_keyToProgress.insert(budA);
	}
	if (budB && budB->bodyType == BodyType_KEY && fA->GetBody() == layer->m_player)
	{
		layer->m_keyToProgress.insert(budB);
	}

	//isPlayerColideWithDoor
	if (fA->GetBody() == layer->m_door && fB->GetBody() == layer->m_player)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	if (fB->GetBody() == layer->m_door && fA->GetBody() == layer->m_player)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
}

void BasicLevelContactListener::EndContact(b2Contact* contact)
{
	Level1* layer = (Level1*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	//isPlayerColideWithDoor
	if (fA->GetBody() == layer->m_door && fB->GetBody() == layer->m_player)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
	if (fB->GetBody() == layer->m_door && fA->GetBody() == layer->m_player)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
}
