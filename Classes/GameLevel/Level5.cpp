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
	m_whirlpool->m_isOn = true;
}

void Level5::loadWhirlpool(b2dJson* json)
{
	b2Body* body = json->getBodyByName("whirlpool");
	if (body)
	{
		BasicLevelBodyUserData* bud = new BasicLevelBodyUserData;
		body->SetUserData(bud);
		bud->bodyType = BodyType_Whirlpool;
		bud->body = body;
		m_whirlpool = WhirlpoolSprite::create(body, false);
		m_whirlpool->setSpritePositionFromPhysicsBody();
		addChild(m_whirlpool, 9999);
		m_whirlpool->setScale(0.6f);
		m_whirlpool->setScale(m_whirlpool->getScale() / BasicLevelLayer::initialWorldScale());
		m_objectBodys.push_back(body);
	}
}

void Level5::update(float dt)
{
	m_whirlpool->update(dt);
	if (m_whirlpool->m_isOn)
	{
		whirlpoolEffect();
	}
	BasicLevelLayer::update(dt);
}

void Level5::addContactListener()
{
	m_contactListener = new ContactListenerWhirlpool();
	m_world->SetContactListener(m_contactListener);
	m_contactListener->m_layer = this;
}

void Level5::addBodyUserDataToSet(BasicLevelBodyUserData* bud)
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
			body->SetLinearDamping(5);
		}
	}
}

