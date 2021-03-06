#ifndef __ContactListener_H__
#define __ContactListener_H__

#include "Box2D/Box2D.h"
#include "GameData/MyBodyUserData.h"

class ContactListener :public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
	virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching

	bool isPlayerColideWithDoor(b2Fixture* fA, b2Fixture* fB);
	bool isPlayerColideWithBall(MyBodyUserData* budA, MyBodyUserData* budB);
	bool isPlayerColideWithEdge(MyBodyUserData* budA, MyBodyUserData* budB);
	bool isPlayerLeaveGround(b2Fixture* fA, b2Fixture* fB);
	class BasicLevelLayer* m_layer;
};

#endif