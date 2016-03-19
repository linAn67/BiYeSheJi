#include "Sprite/BaseSprite.h"


USING_NS_CC;

void BaseSprite::update(float delta)
{
	setSpritePositionFromPhysicsBody();
}

void BaseSprite::setSpritePositionFromPhysicsBody()
{
	Vec2 pos = m_sprite->getPosition();
	float angle = -m_sprite->getRotation();
	if (m_body)
	{
		b2Vec2 localPos(pos.x, pos.y);
		b2Rot rot(m_body->GetAngle());
		b2Mul(rot, localPos) + m_body->GetPosition();
		pos.x = localPos.x;
		pos.y = localPos.y;
		angle += -m_body->GetAngle();
	}
	m_sprite->setRotation(CC_RADIANS_TO_DEGREES(angle));
	m_sprite->setPosition(pos);
}

