#include "GameLevel/ContactListener.h"
#include "GameLevel/BasicLevelLayer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	MyBodyUserData* budA = (MyBodyUserData*)fA->GetBody()->GetUserData();
	MyBodyUserData* budB = (MyBodyUserData*)fB->GetBody()->GetUserData();

	//isPlayerColideWithKey
	if (budA && budA->bodyType == BodyType_KEY && budB && budB->bodyType == BodyType_Player)
	{
		m_layer->m_keyToProgress.insert(budA);
	}
	if (budB && budB->bodyType == BodyType_KEY && budA && budA->bodyType == BodyType_Player)
	{
		m_layer->m_keyToProgress.insert(budB);
	}

	//isPlayerColideWithDoor
	if (fA->GetBody() == layer->m_door && fB == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	if (fB->GetBody() == layer->m_door && fA == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	

	//ifColideWithBall,lose
	if (isPlayerColideWithBall(budA, budB))
	{
		m_layer->lose();
	} 
	

	//判断玩家是否离开地面
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts++;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts++;
	}

	//判断玩家是否接触到边界
	if (isPlayerColideWithEdge(budA, budB))
	{
		m_layer->lose();
	}
	
	
}

void ContactListener::EndContact(b2Contact* contact)
{
	BasicLevelLayer* layer = (BasicLevelLayer*)m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	MyBodyUserData* budA = (MyBodyUserData*)fA->GetBody()->GetUserData();
	MyBodyUserData* budB = (MyBodyUserData*)fB->GetBody()->GetUserData();

	//isPlayerColideWithDoor
	if (budA && budA->bodyType == BodyType_Door && fB == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}
	if (budB && budB->bodyType == BodyType_Door && fA == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = false;
	}

	//判断玩家是否离开地面
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
}

bool ContactListener::isPlayerColideWithBall(MyBodyUserData* budA, MyBodyUserData* budB)
{
	if (budA && budA->bodyType == BodyType_FATALBALL && budB && budB->bodyType == BodyType_Player)
	{
		return true;
	}
	if (budB && budB->bodyType == BodyType_FATALBALL && budA->bodyType == BodyType_Player)
	{
		return true;
	}
	return false;
}

bool ContactListener::isPlayerColideWithEdge(MyBodyUserData* budA, MyBodyUserData* budB)
{
	if (budA && budA->bodyType == BodyType_Edge && budB && budB->bodyType == BodyType_Player)
	{
		return true;
	}
	if (budB && budB->bodyType == BodyType_Edge && budA && budA->bodyType == BodyType_Player)
	{
		return true;
	}
	return false;
}