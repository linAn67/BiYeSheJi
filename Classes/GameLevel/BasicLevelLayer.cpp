#include "GameLevel/BasicLevelLayer.h"
#include "GameUI/LoseLayer.h"
#include "GameUI/PausemenuLayer.h"

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
	if (!m_isLocked)
	{
		m_isLocked = true;
		auto director = Director::getInstance();
		auto scene = GameScene::getNextLevel();
		scene = TransitionFade::create(1.0f, scene, Color3B::WHITE);
		director->replaceScene(scene);
	}
}

void BasicLevelLayer::lose()
{
	//Node::pause();
	auto director = Director::getInstance();

	//创建CCRenderTexture，纹理画布大小为窗口大小(1136, 640)
	RenderTexture *renderTexture = RenderTexture::create(1136, 640);

	//遍历Game类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	director->pushScene(LoseLayer::createScene(renderTexture));
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
	loadGround(json);
	loadEdge(json);
	loadPlayer(json);
	loadDoor(json);
	loadChains(json);
	loadKeys(json);
	loadBalls(json);
	auto sp = Sprite::create("res/BasicBackGround.png");
	addChild(sp, -5);
	sp->setScale(1.0f / initialWorldScale());
	rotateAngle = 0;

	addControllerLayer();
	addContactListener();
}

void BasicLevelLayer::loadGround(b2dJson* json)
{
	if (json->getBodyByName("ground"))
	{
		std::vector<b2Body*> groundBodys;
		json->getBodiesByName("ground", groundBodys);
		for each (auto body in groundBodys)
		{
			MyBodyUserData* bud = new MyBodyUserData;
			m_objectBodys.push_back(body);
			body->SetUserData(bud);

			bud->bodyType = BodyType_Ground;
			bud->body = body;
		}
	}
}



void BasicLevelLayer::loadPlayer(b2dJson* json)
{
	
	b2Body* body = json->getBodyByName("player");
	b2Fixture* foot= json->getFixtureByName("playerfoot");
	MyBodyUserData* bud = new MyBodyUserData;
	bud->body = body;
	bud->bodyType = BodyType::BodyType_Player;
	body->SetUserData(bud);
	Sprite* sp = getAnySpriteOnBody(body);
	m_player = Player::create(body, foot, sp);
	addChild(m_player);
}

void BasicLevelLayer::loadBalls(b2dJson* json)
{
	if (json->getBodyByName("ball"))
	{
		std::vector<b2Body*> ballBodys;
		json->getBodiesByName("ball", ballBodys);
		for each (auto body in ballBodys)
		{
			MyBodyUserData* bud = new MyBodyUserData;
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
			MyBodyUserData* bud = new MyBodyUserData;
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

void BasicLevelLayer::loadEdge(b2dJson* json)
{
	if (json->getBodyByName("edge"))
	{
		std::vector<b2Body*> edgeBodys;
		json->getBodiesByName("edge", edgeBodys);
		for each (auto body in edgeBodys)
		{
			MyBodyUserData* bud = new MyBodyUserData;
			m_objectBodys.push_back(body);
			body->SetUserData(bud);
			bud->bodyType = BodyType_Edge;
			bud->body = body;
		}
	}
}

void BasicLevelLayer::loadDoor(b2dJson* json)
{
	m_door = json->getBodyByName("door");
	//因为有几次都忘了在编辑器里加入门的刚体，所以加一句断言
	CCAssert(nullptr != m_door, "m_door not initial");
	m_isPlayerCollideWithDoor = false;
	m_numFootContacts = 0;
	m_objectBodys.push_back(m_door);
	m_isLocked = false;
	//////////////////////////////////////////////////////////////////////////
	MyBodyUserData* bud = new MyBodyUserData;
	bud->body = m_door;
	bud->bodyType = BodyType::BodyType_Door;
	m_door->SetUserData(bud);
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
	addChild(m_controllerLayer,99);
}

void BasicLevelLayer::clear()
{
	BasicLoadLayer::clear();
	m_objectBodys.clear();
	for (std::set<MyBodyUserData*>::iterator it = m_allKeys.begin(); it != m_allKeys.end(); ++it)
	{
		delete *it;
	}
	m_allKeys.clear();
	m_keyToProgress.clear();
}

void BasicLevelLayer::update(float dt)
{
	m_controllerLayer->update(dt);
	BasicLoadLayer::update(dt);
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
	
	if (m_player != nullptr)
	{
		m_player->update(dt);
	}

	//遍历待删除的钥匙进行清除
	for each (auto bud in m_keyToProgress)
	{
		removeBodyFromWorld(bud->body);
		m_allKeys.erase(bud);
	}
	//遍历完后要clear
	m_keyToProgress.clear();
}

void BasicLevelLayer::movePlayer()
{
	//在地上才能动
	if (m_numFootContacts>0)
	{
		m_player->move(m_controllerLayer->m_playerMoveDirection);
	}
}

void BasicLevelLayer::rotateAllObjectBodys()
{
	rotateBodyPosition(m_player->getBody());
	//遍历所有刚体，并旋转位置和角度
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
	float32 angle = CC_RADIANS_TO_DEGREES(body->GetAngle());
	angle +=m_controllerLayer->m_rotateAngle - rotateAngle;
	body->SetTransform(rotateB2Vec(body->GetPosition()), CC_DEGREES_TO_RADIANS(angle));
	if (!(body->GetLinearVelocity() == b2Vec2(0, 0)))
	{
		body->SetLinearVelocity(rotateB2Vec(body->GetLinearVelocity()));
	}
}

void BasicLevelLayer::rotateBodyPosition(b2Body* body)
{
	body->SetTransform(rotateB2Vec(body->GetPosition()), body->GetAngle());
	if (!(body->GetLinearVelocity()==b2Vec2(0,0)))
	{
		body->SetLinearVelocity(rotateB2Vec(body->GetLinearVelocity()));
	}
}

b2Vec2 BasicLevelLayer::rotateB2Vec(b2Vec2 velocity)
{
	Vec2 v = Vec2(velocity.x, velocity.y);
	v = v.rotateByAngle(Vec2(0, 0), CC_DEGREES_TO_RADIANS(m_controllerLayer->m_rotateAngle - rotateAngle));
	return b2Vec2(v.x, v.y);
}

void BasicLevelLayer::doPause()
{
	//Node::pause();
	auto director = Director::getInstance();

	//创建RenderTexture，纹理画布大小为窗口大小(1136, 640)
	RenderTexture *renderTexture = RenderTexture::create(1136, 640);

	//遍历所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	director->pushScene(PausemenuLayer::createScene(renderTexture));
}

b2Fixture* BasicLevelLayer::getPlayerFootSensorFixture()
{
	return m_player->m_footSensor;
}

b2Body* BasicLevelLayer::getDoorBody()
{
	return m_door;
}

void BasicLevelLayer::addKeysBudToContainer(MyBodyUserData* bud)
{
	if (bud->bodyType==BodyType_KEY)
	{
		m_keyToProgress.insert(bud);
	}
	else
	{
		CCLOG("the bud is not a key's bud");
	}
}

