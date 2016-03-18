#include "GameLevel/ContactListener.h"
#include "GameLevel/BasicLevelLayer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	BasicLevelBodyUserData* budA = (BasicLevelBodyUserData*)fA->GetBody()->GetUserData();
	BasicLevelBodyUserData* budB = (BasicLevelBodyUserData*)fB->GetBody()->GetUserData();

	if (budA && budA->bodyType == BodyType_KEY && fB->GetBody() == layer->m_playerBody)
	{
		layer->m_keyToProgress.insert(budA);
	}
	if (budB && budB->bodyType == BodyType_KEY && fA->GetBody() == layer->m_playerBody)
	{
		layer->m_keyToProgress.insert(budB);
	}

	//isPlayerColideWithDoor
	if (fA->GetBody() == layer->m_door && fB == layer->m_playerFootSensorFixture)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	if (fB->GetBody() == layer->m_door && fA == layer->m_playerFootSensorFixture)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}

	//ifColideWithBall,lose
	if (budA && budA->bodyType == BodyType_FATALBALL && fB->GetBody() == layer->m_playerBody)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_FATALBALL && fA->GetBody() == layer->m_playerBody)
	{
		layer->lose();
	}

	//判断玩家是否在空中
	if (fA == layer->m_playerFootSensorFixture || fB == layer->m_playerFootSensorFixture)
	{
		layer->m_numFootContacts++;
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	//isPlayerColideWithDoor
	if (fA->GetBody() == layer->m_door && fB == layer->m_playerFootSensorFixture)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
	if (fB->GetBody() == layer->m_door && fA == layer->m_playerFootSensorFixture)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
	if (fA == layer->m_playerFootSensorFixture || fB == layer->m_playerFootSensorFixture)
	{
		layer->m_numFootContacts--;
	}
}