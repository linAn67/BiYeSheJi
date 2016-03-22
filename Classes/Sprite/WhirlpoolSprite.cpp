#include "Sprite/WhirlpoolSprite.h"

USING_NS_CC;

bool WhirlpoolSprite::init(b2Body* body, bool isOn)
{
	if (!Sprite::init())
	{
		return false;
	}
	
	if (!body)
	{
		return false;
	}
	m_body = body;
	m_isOn = isOn;
	m_sprite = Sprite::create("basic-object/whirlpool.png");
	m_sprite->setOpacity(125);
	addChild(m_sprite);
	m_whirlpoolGravity = 15;
	return true;
}

WhirlpoolSprite* WhirlpoolSprite::create(b2Body* body, bool isOn)
{
	WhirlpoolSprite* pRet = new(std::nothrow) WhirlpoolSprite();
	if (pRet&&pRet->init(body, isOn))
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

void WhirlpoolSprite::update(float delta)
{
	setSpritePositionFromPhysicsBody();
	if (m_isOn)
	{
		float angle = fmod(m_sprite->getRotation(), 360);
		m_sprite->setRotation(angle - 0.1);
		m_sprite->setOpacity(125);
	}
	else
	{
		m_sprite->setOpacity(0);
	}
}

void WhirlpoolSprite::setSpritePositionFromPhysicsBody()
{
	Vec2 pos;
	float angle = -m_sprite->getRotation();
	if (m_body)
	{
		b2Vec2 bvec = m_body->GetPosition();


		pos = Vec2(bvec.x, bvec.y);
	}
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	this->setPosition(pos);
}