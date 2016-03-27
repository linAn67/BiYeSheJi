#ifndef __MyBodyUserData_H__
#define __MyBodyUserData_H__

#include "Box2D/box2d.h"

enum BodyType
{
	BodyType_KEY,
	BodyType_FATALBALL,
	BodyType_Door,
	BodyType_Whirlpool,
	BodyType_Ground,
	BodyType_Edge,
	BodyType_Player = 99
};

struct MyBodyUserData
{
	BodyType bodyType;
	b2Body* body;
};

#endif