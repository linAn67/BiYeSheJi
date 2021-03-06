#include "Sprite/Player.h"
#include "Box2D/Box2D.h"
#include <math.h>

#define MAX_VELOCITY 1.5f

USING_NS_CC;

bool Player::init(b2Body* body, b2Fixture* footSensor, cocos2d::Sprite* sprite)
{
	if (!Sprite::init())
	{
		return false;
	}

	if (!m_body)
	{
		return false;
	}

	m_body = body;
	m_body->SetLinearDamping(1);
	m_sprite = sprite;
	m_footSensor = footSensor;
	m_isFlipX = sprite->isFlipX();
	return true;
}


Player* Player::create(b2Body* body, b2Fixture* footSensor, cocos2d::Sprite* sprite)
{
	Player* pRet = new(std::nothrow) Player();
	if (pRet&&pRet->init(body,footSensor, sprite))
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

void Player::update(float delta)
{
	setSpritePositionFromPhysicsBody();
	//根据x轴的线速度判断玩家当前移动的方向

	if (m_body->GetLinearVelocity().x>0.1f )
	{
		m_isFlipX = true;
	}
	else if (m_body->GetLinearVelocity().x<-0.1f)
	{
		m_isFlipX = false;
	}
	m_sprite->setFlipX(m_isFlipX);
}

void Player::setSpritePositionFromPhysicsBody()
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

void Player::move(PlayerMoveDirection dir)
{
	b2Vec2 force;
	switch (dir)
	{
	case PLAYER_MOVETOLEFT:
		force = b2Vec2(-1, 0);
		break;
	case PLAYER_MOVETORIGHT:
		force = b2Vec2(1, 0);
		break;
	default:
		force = b2Vec2(0, 0);
		break;
	}
	if (fabs(m_body->GetLinearVelocity().x)<MAX_VELOCITY)
	{
		force *= 10 * m_body->GetMass();
		m_body->ApplyForce(force, m_body->GetPosition(), true);
	}
}

b2Body* Player::getBody()
{
	return m_body;
}
