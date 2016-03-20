#include "GameLevel/ContactListener.h"
#include "GameLevel/BasicLevelLayer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	BasicLevelBodyUserData* budA = (BasicLevelBodyUserData*)fA->GetBody()->GetUserData();
	BasicLevelBodyUserData* budB = (BasicLevelBodyUserData*)fB->GetBody()->GetUserData();

	//isPlayerColideWithKey
	if (budA && budA->bodyType == BodyType_KEY && budB && budB->bodyType == BodyType_Player)
	{
		layer->m_keyToProgress.insert(budA);
	}
	if (budB && budB->bodyType == BodyType_KEY && budA && budA->bodyType == BodyType_Player)
	{
		layer->m_keyToProgress.insert(budB);
	}

	//isPlayerColideWithDoor
	if (budA && budA->bodyType == BodyType_Door && fB == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	if (budB && budB->bodyType == BodyType_Door && fA == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}

	//ifColideWithBall,lose
	if (budA && budA->bodyType == BodyType_FATALBALL && budB && budB->bodyType == BodyType_Player)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_FATALBALL && budA->bodyType == BodyType_Player)
	{
		layer->lose();
	}

	//�ж�����Ƿ��뿪����
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts++;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts++;
	}

	//�ж�����Ƿ�Ӵ����߽�
	if (budA && budA->bodyType == BodyType_Edge && budB && budB->bodyType == BodyType_Player)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_Edge && budA && budA->bodyType == BodyType_Player)
	{
		layer->lose();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	BasicLevelBodyUserData* budA = (BasicLevelBodyUserData*)fA->GetBody()->GetUserData();
	BasicLevelBodyUserData* budB = (BasicLevelBodyUserData*)fB->GetBody()->GetUserData();

	//isPlayerColideWithDoor
	if (budA && budA->bodyType == BodyType_Door && fB == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
	if (budB && budB->bodyType == BodyType_Door && fA == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}

	//�ж�����Ƿ��뿪����
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
}