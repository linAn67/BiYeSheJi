#include "Sprite/ButtonSprite.h"
#include "Box2D/Box2D.h"

USING_NS_CC;


b2Fixture* ButtonSprite::getBtnSensor()
{
	return m_btnSensor;
}

b2Fixture* ButtonSprite::getbtnBaseSensor()
{
	return m_btnBaseSensor;
}

bool ButtonSprite::init(b2Body* btnBody, b2Body* btnBaseBody, b2Fixture* btnSensor, b2Fixture* btnBaseSensor)
{
	if (!Sprite::init())
	{
		return false;
	}
	if (!btnBody ||
		!btnBaseBody ||
		!btnSensor ||
		!btnBaseSensor)
	{
		return false;
	}
	m_isOn = false;
	m_btn = btnBody;
	m_btnBase = btnBaseBody;
	m_btnSensor = btnSensor;
	m_btnBaseSensor = btnBaseSensor;
	return true;
}

ButtonSprite* ButtonSprite::create(b2Body* btnBody, b2Body* btnBaseBody, b2Fixture* btnSensor, b2Fixture* btnBaseSensor)
{
	ButtonSprite* pRet = new(std::nothrow) ButtonSprite();
	if (pRet&&pRet->init(btnBody, btnBaseBody, btnSensor, btnBaseSensor))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void ButtonSprite::update(float delta)
{
	keepBtnOff();
}

void ButtonSprite::keepBtnOff()
{
	b2Vec2 force = m_btn->GetPosition() - m_btnBase->GetPosition();
	force.Normalize();
	force *= 5 * m_btn->GetMass();
	m_btn->ApplyForce(force, m_btn->GetPosition(), true);
	
}
