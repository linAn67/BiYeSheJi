#ifndef __BaseSprite_H__
#define __BaseSprite_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"


class BaseSprite : public cocos2d::Sprite
{
public:
	Sprite* m_sprite;
	b2Body* m_body;
	virtual void update(float delta);
	void setSpritePositionFromPhysicsBody();
};

#endif // __HELLOWORLD_SCENE_H__
