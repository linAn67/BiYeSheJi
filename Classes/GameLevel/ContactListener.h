#ifndef __ContactListener_H__
#define __ContactListener_H__

#include "Box2D/Box2D.h"

class ContactListener :public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
	virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching

	class BasicLevelLayer* m_layer;
};

#endif