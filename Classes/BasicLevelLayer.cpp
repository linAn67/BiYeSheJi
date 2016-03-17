#include "BasicLevelLayer.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

Scene* BasicLevelLayer::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	//蓝色背景
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

void BasicLevelLayer::lose()
{
	CCLOG("lose");
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
	json->getBodiesByName("ground", m_objectBodys);
	m_playerBody = json->getBodyByName("player");
	m_playerFootSensorFixture = json->getFixtureByName("playerfoot");
	m_door = json->getBodyByName("door");
	m_isPlayerCollideWithDoor = false;
	m_objectBodys.push_back(m_door);
	//////////////////////////////////////////////////////////////////////////
	BasicLevelBodyUserData* bud = new BasicLevelBodyUserData;
	bud->body = m_door;
	bud->bodyType = BodyType::BodyType_Door;
	m_door->SetUserData(bud);
	//////////////////////////////////////////////////////////////////////////
	if (json->getBodyByName("obstacle"))
	{
		m_objectBodys.push_back(json->getBodyByName("obstacle"));
	}

	loadChains(json);
	loadKeys(json);
	loadBalls(json);
	auto sp = Sprite::create("res/BasicBackGround.png");
	addChild(sp, -5);
	sp->setScale(0.0125f);
	rotateAngle = 0;

	addControllerLayer();
	addContactListener();

}

void BasicLevelLayer::loadBalls(b2dJson* json)
{
	if (json->getBodyByName("ball"))
	{
		std::vector<b2Body*> ballBodys;
		json->getBodiesByName("ball", ballBodys);
		for each (auto body in ballBodys)
		{
			BasicLevelBodyUserData* bud = new BasicLevelBodyUserData;
			m_objectBodys.push_back(body);
			body->SetUserData(bud);

			bud->bodyType = BodyType_FATALBALL;
			bud->body = body;
		}
	}
	else
	{
		CCLOG("no ball to load");
	}
}

void BasicLevelLayer::loadChains(b2dJson* json)
{
	if (json->getBodyByName("chain"))
	{
		std::vector<b2Body*> chainBodys;
		json->getBodiesByName("chain", chainBodys);
		for each (auto body in chainBodys)
		{
			m_objectBodys.push_back(body);
		}
	}
	else
	{
		CCLOG("no chain to load");
		
	}
}

void BasicLevelLayer::loadKeys(b2dJson* json)
{
	if (json->getBodyByName("key"))
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
	else
	{
		CCLOG("no key to load");
	}
}

void BasicLevelLayer::addContactListener()
{
	m_contactListener = new ContactListener();
	m_world->SetContactListener(m_contactListener);
	m_contactListener->m_layer = this;
}

void BasicLevelLayer::addControllerLayer()
{
	auto director = Director::getInstance();
	Size winSize = director->getWinSize();
	m_controllerLayer = ControllerLayer::create();
	m_controllerLayer->m_layer = this;
	//由于在初始化时的一些坐标转换，在添加精灵时需要根据转换后的layer进行一些坐标变换和大小缩放
	m_controllerLayer->setAnchorPoint(Vec2(0, 0));
	m_controllerLayer->setPosition(Vec2(-winSize.width / 2, -winSize.height / 2) / initialWorldScale());
	m_controllerLayer->setScale(m_controllerLayer->getScale() / initialWorldScale());
	addChild(m_controllerLayer,10);
}

void BasicLevelLayer::clear()
{
	RUBELayer::clear();
	m_objectBodys.clear();
	m_objectBodys.clear();
	for (std::set<BasicLevelBodyUserData*>::iterator it = m_allKeys.begin(); it != m_allKeys.end(); ++it)
	{
		delete *it;
	}
	m_allKeys.clear();
	m_keyToProgress.clear();
}

void BasicLevelLayer::update(float dt)
{
	m_controllerLayer->update(dt);
	RUBELayer::update(dt);
	if (m_controllerLayer->m_returnToPreviousLevelState)
	{
		//loadAndSetLevelStateDatas();
	}
	else
	{
		rotateAngle = fmodf(rotateAngle, 360);
		if (rotateAngle != m_controllerLayer->m_rotateAngle){
			rotateAllObjectBodys();
			rotateAngle = m_controllerLayer->m_rotateAngle;
			rotateAngle = fmodf(rotateAngle, 360);
		}
		movePlayer();
	}
	
	

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

void BasicLevelLayer::movePlayer()
{
	switch (m_controllerLayer->m_playerMoveDirection)
	{
	case PLAYER_MOVETOLEFT:
		m_playerBody->SetTransform(m_playerBody->GetPosition() - b2Vec2(0.025f, 0.0f), m_playerBody->GetAngle());
		break;
	case PLAYER_MOVETORIGHT:
		m_playerBody->SetTransform(m_playerBody->GetPosition() + b2Vec2(0.025f, 0.0f), m_playerBody->GetAngle());
		break;
	case PLAYER_NOTMOVING:
		break;
	default:
		break;
	}
}

void BasicLevelLayer::rotateAllObjectBodys()
{
	rotateBodyPosition(m_playerBody);
	for each (auto body in m_objectBodys)
	{
		rotateBodyAndChangeAngle(body);
	}
	for each (auto bud in m_allKeys)
	{
		rotateBodyAndChangeAngle(bud->body);
	}
}

void BasicLevelLayer::rotateBodyAndChangeAngle(b2Body* body)
{
	Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
	bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));
	float32 angle = CC_RADIANS_TO_DEGREES(body->GetAngle());
	angle +=m_controllerLayer->m_rotateAngle - rotateAngle;
	body->SetTransform(b2Vec2(bodyPos.x, bodyPos.y), CC_DEGREES_TO_RADIANS(angle));
}

void BasicLevelLayer::rotateBodyPosition(b2Body* body)
{
	Vec2 bodyPos = Vec2(body->GetPosition().x, body->GetPosition().y);
	bodyPos = bodyPos.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));
	body->SetTransform(b2Vec2(bodyPos.x, bodyPos.y), body->GetAngle());
}

void BasicLevelLayer::doPause()
{
	//Node::pause();
	auto director = Director::getInstance();

	//创建CCRenderTexture，纹理画布大小为窗口大小(480,320)
	RenderTexture *renderTexture = RenderTexture::create(1136, 640);

	//遍历Game类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	director->pushScene(PausemenuLayer::createScene(renderTexture,this));
}

void BasicLevelLayer::replay()
{
	auto director = Director::getInstance();
	director->replaceScene(createScene());
}
