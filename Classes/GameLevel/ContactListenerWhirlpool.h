#ifndef __ContactListenerWhirlpool_H__
#define __ContactListenerWhirlpool_H__
#include "Box2D/Box2D.h"
#include "GameLevel/ContactListener.h"

class ContactListenerWhirlpool : public ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
	virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching

	class Level5* m_layer;
};

#endif