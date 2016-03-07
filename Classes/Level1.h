#include "cocos2d.h"
#include "RUBELayer.h"
#include "ControllerLayer.h"


#ifndef __LEVEL1_H__
#define __LEVEL1_H__

class b2dJson;

enum BodyType
{
	BodyType_KEY,
	BodyType_FATALBALL
};

struct BasicLevelBodyUserData
{
	BodyType bodyType;
	b2Body* body;
};

class BasicLevelContactListener :public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);      // called by Box2D during the Step function when two fixtures begin touching
	virtual void EndContact(b2Contact* contact);        // called by Box2D during the Step function when two fixtures finish touching

	class Level1* m_layer;
};

class Level1:public RUBELayer
{
protected:
public: 
	BasicLevelContactListener* m_contactListener;
	
	b2Body* m_player;						//存储主角的刚体用于移动
	
	b2Body* m_door;							//通关的门
	bool m_isPlayerCollideWithDoor;
											//由于cocos2dx封装的Vector仅支持继承自CCNode的类，所以这里用STL的Vector
	std::vector<b2Body*> m_groundBodys;		//存储场景刚体用于旋转操作
											
	std::vector<b2Body*> m_objectBodys;		//存储非场景刚体用于旋转操作
	//存储当前场景的旋转角度
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);
	std::set<BasicLevelBodyUserData*> m_allKeys;
	std::set<BasicLevelBodyUserData*> m_keyToProgress;


	ControllerLayer* m_controllerLayer;


	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);


	virtual void clear();
	virtual void update(float dt);

	void movePlayer();
	//旋转场景刚体
	void rotateGroundBody();
	//旋转非场景的刚体
	void rotateObjectBody(b2Body* body);
	//读钥匙的刚体
	void loadKeys(b2dJson* json);
	void addContactListener();
	void addControllerLayer();
	static cocos2d::Scene* createScene();

	void win();
	void lose();

	b2PrismaticJoint* test;
};

#endif