#include "BasicLevelLayer.h"





using namespace std;
using namespace cocos2d;
using namespace ui;

Scene* BasicLevelLayer::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	//��ɫ����
	Color4B c4b = Color4B(104, 171, 213, 255);
	LayerColor* layer2 = LayerColor::create(c4b);
	scene->addChild(layer2,-2);

	BasicLevelLayer* layer = new BasicLevelLayer();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

void BasicLevelLayer::win()
{
	CCLOG("win");
	
}

std::string BasicLevelLayer::getFilename()
{
	return "level1.json";
}

cocos2d::Point BasicLevelLayer::initialWorldOffset()
{
	Size s = Director::getInstance()->getWinSize();
	return Vec2(s.width / 2, s.height / 2);
}

float BasicLevelLayer::initialWorldScale()
{
	Size s = Director::getInstance()->getWinSize();
	return s.height / 8; //screen will be 8 physics units high
}

void BasicLevelLayer::afterLoadProcessing(b2dJson* json)
{
	RUBELayer::afterLoadProcessing(json);
	json->getBodiesByName("ground", m_groundBodys);
	m_player = json->getBodyByName("player");
	m_door = json->getBodyByName("door");
	m_isPlayerCollideWithDoor = false;
	m_groundBodys.push_back(m_door);
	loadKeys(json);
	auto sp = Sprite::create("res/BasicBackGround.png");
	addChild(sp, -5);
	sp->setScale(0.0125);
	rotateAngle = 0;

	addControllerLayer();
	addContactListener();

}

void BasicLevelLayer::loadKeys(b2dJson* json)
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

void BasicLevelLayer::addContactListener()
{
	m_contactListener = new BasicLevelContactListener();
	m_world->SetContactListener(m_contactListener);
	m_contactListener->m_layer = this;
}

void BasicLevelLayer::addControllerLayer()
{
	auto director = Director::sharedDirector();
	Size winSize = director->getWinSize();
	m_controllerLayer = ControllerLayer::create();
	m_controllerLayer->m_layer = this;
	//�����ڳ�ʼ��ʱ��һЩ����ת���������Ӿ���ʱ��Ҫ����ת�����layer����һЩ����任�ʹ�С����
	m_controllerLayer->setAnchorPoint(Vec2(0, 0));
	m_controllerLayer->setPosition(Vec2(-winSize.width / 2, -winSize.height / 2) / initialWorldScale());
	m_controllerLayer->setScale(m_controllerLayer->getScale() / initialWorldScale());
	addChild(m_controllerLayer,10);
}

void BasicLevelLayer::clear()
{
	RUBELayer::clear();
	m_groundBodys.clear();
	m_objectBodys.clear();
}

void BasicLevelLayer::update(float dt)
{
	m_controllerLayer->update(dt);

	//��ת�ǳ��������
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

	//������������Կ�׽������
	for each (auto bud in m_keyToProgress)
	{
		removeBodyFromWorld(bud->body);
		m_allKeys.erase(bud);
		delete bud;
	}
	//�������Ҫclear list
	m_keyToProgress.clear();
}

void BasicLevelLayer::movePlayer()
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

void BasicLevelLayer::rotateGroundBody()
{
	for each (auto body in m_groundBodys)
	{
		Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
		bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));

		//body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle));
		body->SetTransform(b2Vec2(bodyPos.x,bodyPos.y), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle));
	}
}

void BasicLevelLayer::rotateObjectBody(b2Body* body)
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
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
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
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
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