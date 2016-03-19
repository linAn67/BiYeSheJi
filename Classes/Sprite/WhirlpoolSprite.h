#ifndef __WhirlpoolSprite_H__
#define __WhirlpoolSprite_H__

#include "Sprite/BaseSprite.h"
class WhirlpoolSprite :public cocos2d::Sprite
{
public:
	bool m_isOn;
	virtual bool init(b2Body* body, bool isOn);
	static WhirlpoolSprite* create(b2Body* body, bool isOn);
	virtual void update(float delta);
	void setSpritePositionFromPhysicsBody();
public:
	Sprite* m_sprite;
	b2Body* m_body;
	float m_whirlpoolGravity;
};

#endif