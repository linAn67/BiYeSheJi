#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameUI/ControllerLayer.h"

class Player :public cocos2d::Sprite
{
public:
	bool m_isFlipX;
	virtual bool init(b2Body* body, b2Fixture* footSensor, cocos2d::Sprite* sprite);
	static Player* create(b2Body* body, b2Fixture* footSensor, cocos2d::Sprite* sprite);
	virtual void update(float delta);
	void setSpritePositionFromPhysicsBody();
	void move(PlayerMoveDirection dir);
	b2Body* getBody();
public:
	b2Fixture* m_footSensor;
private:
	Sprite* m_sprite;
	b2Body* m_body;
};

#endif