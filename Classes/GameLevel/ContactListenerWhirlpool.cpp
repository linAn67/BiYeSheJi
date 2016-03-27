#include "GameLevel/ContactListenerWhirlpool.h"
#include "GameLevel/level5.h"

void ContactListenerWhirlpool::BeginContact(b2Contact* contact)
{

	Level5* layer = m_layer;
	b2Fixture* fA = contact->GetFixtureA();
	b2Fixture* fB = contact->GetFixtureB();

	MyBodyUserData* budA = (MyBodyUserData*)fA->GetBody()->GetUserData();
	MyBodyUserData* budB = (MyBodyUserData*)fB->GetBody()->GetUserData();

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

	//�ж�����Ƿ�Ӵ����߽�
	if (budA && budA->bodyType == BodyType_Edge && budB && budB->bodyType == BodyType_Player)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_Edge && budA && budA->bodyType == BodyType_Player)
	{
		layer->lose();
	}

	//�ж����Ƿ�Ӵ����߽磬ʧȥ����޷�ͨ��
	if (budA && budA->bodyType == BodyType_FATALBALL && budB && budB->bodyType == BodyType_Edge)
	{
		layer->lose();
	}
	if (budB && budB->bodyType == BodyType_FATALBALL && budA && budA->bodyType == BodyType_Edge)
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

	//�ж��Ƿ��������
	if (budA && budA->bodyType == BodyType_Whirlpool && budB)
	{
		m_layer->addBodyUserDataInWhirlpool(budB);
	}
	if (budB && budB->bodyType == BodyType_Whirlpool && budA)
	{
		m_layer->addBodyUserDataInWhirlpool(budA);
	}

	//�жϰ�ť�Ƿ񱻰��£�������������Ϊ����״̬
	if (m_layer->m_button!=nullptr)
	{
		if (fA==m_layer->m_button->getBtnSensor()&&fB==m_layer->m_button->getbtnBaseSensor())
		{
			m_layer->m_button->m_isOn = true;
		}
		if (fB == m_layer->m_button->getBtnSensor() && fA == m_layer->m_button->getbtnBaseSensor())
		{
			m_layer->m_button->m_isOn = true;
		}
	}


}

void ContactListenerWhirlpool::EndContact(b2Contact* contact)
{
	Level5* layer = (Level5*)m_layer;
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

	//�ж�����Ƿ��뿪����
	if (fA == layer->m_player->m_footSensor && budB && budB->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}
	if (fB == layer->m_player->m_footSensor && budA && budA->bodyType == BodyType_Ground)
	{
		layer->m_numFootContacts--;
	}

	//�ж��Ƿ��뿪����
	if (budA && budA->bodyType == BodyType_Whirlpool && budB)
	{
		m_layer->removeBodyUserDataInWhirlpool(budB);
	}
	if (budB && budB->bodyType == BodyType_Whirlpool && budA)
	{
		m_layer->removeBodyUserDataInWhirlpool(budA);
	}

	//�жϰ�ť�Ƿ���,������������Ϊ�ر�״̬
	if (m_layer->m_button != nullptr)
	{
		if (fA == m_layer->m_button->getBtnSensor() && fB == m_layer->m_button->getbtnBaseSensor())
		{
			m_layer->m_button->m_isOn = false;
		}
		if (fB == m_layer->m_button->getBtnSensor() && fA == m_layer->m_button->getbtnBaseSensor())
		{
			m_layer->m_button->m_isOn = false;
		}
	}
}