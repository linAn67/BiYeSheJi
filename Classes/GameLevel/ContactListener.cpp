#include "GameLevel/ContactListener.h"
#include "GameLevel/BasicLevelLayer.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	MyBodyUserData* budA = (MyBodyUserData*)fA->GetBody()->GetUserData();
	MyBodyUserData* budB = (MyBodyUserData*)fB->GetBody()->GetUserData();

	//isPlayerColideWithKey
	if (budA && budA->bodyType == BodyType_KEY && budB && budB->bodyType == BodyType_Player)
	{
		m_layer->addKeysBudToContainer(budA);
	}
	if (budB && budB->bodyType == BodyType_KEY && budA && budA->bodyType == BodyType_Player)
	{
		m_layer->addKeysBudToContainer(budB);
	}

	//isPlayerColideWithDoor
	if (isPlayerColideWithDoor(fA,fB))
	{
		m_layer->m_isPlayerCollideWithDoor = true;
	}

	//ifColideWithBall,lose
	if (isPlayerColideWithBall(budA, budB))
	{
		m_layer->lose();
	} 

	//判断玩家是否离开地面
	if (isPlayerLeaveGround(fA,fB))
	{
		m_layer->m_numFootContacts++;
	}

	//判断玩家是否接触到边界
	if (isPlayerColideWithEdge(budA, budB))
	{
		m_layer->lose();
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	//isPlayerColideWithDoor
	if (isPlayerColideWithDoor(fA,fB))
	{
		m_layer->m_isPlayerCollideWithDoor = false;
	}

	//判断玩家是否离开地面
	if (isPlayerLeaveGround(fA,fB))
	{
		m_layer->m_numFootContacts--;
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

bool ContactListener::isPlayerColideWithDoor(b2Fixture* fA, b2Fixture* fB)
{
	if (fA->GetBody() == m_layer->getDoorBody() && fB == m_layer->getPlayerFootSensorFixture())
	{
		return true;
	}
	if (fB->GetBody() == m_layer->getDoorBody() && fA == m_layer->getPlayerFootSensorFixture())
	{
		return true;
	}
	return false;
}

bool ContactListener::isPlayerLeaveGround(b2Fixture* fA, b2Fixture* fB)
{
	MyBodyUserData* budA = (MyBodyUserData*)fA->GetBody()->GetUserData();
	MyBodyUserData* budB = (MyBodyUserData*)fB->GetBody()->GetUserData();
	if (fA == m_layer->getPlayerFootSensorFixture() && budB && budB->bodyType == BodyType_Ground)
	{
		return true;
	}
	if (fB == m_layer->getPlayerFootSensorFixture() && budA && budA->bodyType == BodyType_Ground)
	{
		return true;
	}
	return false;
}

