#ifndef __LevelStateData_H__
#define __LevelStateData_H__

#include "Box2D/Box2D.h"
#include "cocos2d.h"

struct BodyData
{
	b2Body* body;
	b2Vec2 position;
	float32 angle;
	b2Vec2 linearVelocity;
	float32 angularVelocity;
	bool active;
};

struct LevelStateData
{
	std::vector<BodyData*> allBodyDatas;
	float levelRotateAngle;
};

#endif