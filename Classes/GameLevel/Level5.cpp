#include "GameLevel/Level5.h"

USING_NS_CC;


Scene* Level5::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level5* layer = new Level5();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

void Level5::clear()
{
	BasicLevelLayer::clear();
}

std::string Level5::getFilename()
{
	return "level5.json";
}

void Level5::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
	loadWhirlpool(json);
	loadButton(json);
	m_whirlpool->m_isOn = true;

}

void Level5::loadWhirlpool(b2dJson* json)
{
	b2Body* body = json->getBodyByName("whirlpool");
	m_whirlpool = WhirlpoolSprite::create(body, false);
	if (body)
	{
		BasicLevelBodyUserData* bud = new BasicLevelBodyUserData;
		body->SetUserData(bud);
		bud->bodyType = BodyType_Whirlpool;
		bud->body = body;
		//令其与场景一同旋转
		m_objectBodys.push_back(body);
		
	}
	if (m_whirlpool != nullptr)
	{
		m_whirlpool->setSpritePositionFromPhysicsBody();
		addChild(m_whirlpool, 9999);
		m_whirlpool->setScale(0.6f);
		m_whirlpool->setScale(m_whirlpool->getScale() / BasicLevelLayer::initialWorldScale());
	}
}

void Level5::loadButton(b2dJson* json)
{
	b2Body* btnBody = json->getBodyByName("btn");
	b2Body* btnBaseBody = json->getBodyByName("btnBase");
	b2Fixture* btnSensor = json->getFixtureByName("btnSensor");
	b2Fixture* btnBaseSensor = json->getFixtureByName("btnBaseSensor");
	if (btnBody &&
		btnBaseBody)
	{
		m_objectBodys.push_back(btnBody);
		m_objectBodys.push_back(btnBaseBody);
	}
	m_button = ButtonSprite::create(btnBody, btnBaseBody, btnSensor, btnBaseSensor);
	if (m_button!=nullptr)
	{
		addChild(m_button);
	}
}

void Level5::update(float dt)
{
	if (m_whirlpool != nullptr)
	{
		m_whirlpool->update(dt);
		if (m_whirlpool->m_isOn)
		{
			whirlpoolEffect();
		}
	}
	if (m_button != nullptr)
	{
		m_button->update(dt);
	}
	BasicLevelLayer::update(dt);
}

void Level5::addContactListener()
{
	m_contactListener = new ContactListenerWhirlpool();
	m_world->SetContactListener(m_contactListener);
	m_contactListener->m_layer = this;
}

void Level5::addBodyUserDataInWhirlpool(BasicLevelBodyUserData* bud)
{
	CCLOG("addBodyUserDataToSet");
	m_objsInWhirlpool.insert(bud);
}

void Level5::whirlpoolEffect()
{
	b2Body* whirlpoolBody = m_whirlpool->m_body;
	for each (auto bud in m_objsInWhirlpool)
	{
		if (bud&&bud->body)
		{
			b2Body* body = bud->body;
			b2Vec2 force = whirlpoolBody->GetPosition() - body->GetPosition();
			force.Normalize();
			force *= m_whirlpool->m_whirlpoolGravity * body->GetMass();
			body->ApplyForce(force, body->GetPosition(), true);
			body->SetLinearDamping(9);
		}
	}
}

void Level5::removeBodyUserDataInWhirlpool(BasicLevelBodyUserData* bud)
{
	bud->body->SetLinearDamping(0);
	if (m_objsInWhirlpool.count(bud) == 1)
	{
		m_objsInWhirlpool.erase(bud);
	}
}


