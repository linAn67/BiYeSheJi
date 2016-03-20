#include "GameLevel/ContactListenerWhirlpool.h"
#include "GameLevel/level5.h"

void ContactListenerWhirlpool::BeginContact(b2Contact* contact)
{
	Level5* layer = m_layer;
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
	if (fA->GetBody() == layer->m_door && fB == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}
	if (fB->GetBody() == layer->m_door && fA == layer->m_player->m_footSensor)
	{
		layer->m_isPlayerCollideWithDoor = true;
	}

	//ifColideWithBall,lose
	if (budA && budA->bodyType == BodyType_FATALBALL && budB && budB->bodyType == BodyType_Player)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_FATALBALL && budA && budA->bodyType == BodyType_Player)
	{
		layer->lose();
	}

	//判断玩家是否接触到边界
	if (budA && budA->bodyType == BodyType_Edge && budB && budB->bodyType == BodyType_Player)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_Edge && budA && budA->bodyType == BodyType_Player)
	{
		layer->lose();
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

	//判断是否进入漩涡
	if (budA && budA->bodyType == BodyType_Whirlpool && budB)
	{
		m_layer->addBodyUserDataToSet(budB);
	}
	if (budB && budB->bodyType == BodyType_Whirlpool && budA)
	{
		m_layer->addBodyUserDataToSet(budA);
	}
}

void ContactListenerWhirlpool::EndContact(b2Contact* contact)
{
	Level5* layer = (Level5*)m_layer;
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

	//判断玩家是否离开地面
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}

	//判断是否离开漩涡
	if (budA && budA->bodyType == BodyType_Whirlpool && budB)
	{
		m_layer->m_objsInWhirlpool.erase(budB);
	}
	if (budB && budB->bodyType == BodyType_Whirlpool && budA)
	{
		m_layer->m_objsInWhirlpool.erase(budA);
	}
}