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
	
	b2Body* m_player;						//�洢���ǵĸ��������ƶ�
	
	b2Body* m_door;							//ͨ�ص���
	bool m_isPlayerCollideWithDoor;
											//����cocos2dx��װ��Vector��֧�ּ̳���CCNode���࣬����������STL��Vector
	std::vector<b2Body*> m_groundBodys;		//�洢��������������ת����
											
	std::vector<b2Body*> m_objectBodys;		//�洢�ǳ�������������ת����
	//�洢��ǰ��������ת�Ƕ�
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
	//��ת��������
	void rotateGroundBody();
	//��ת�ǳ����ĸ���
	void rotateObjectBody(b2Body* body);
	//��Կ�׵ĸ���
	void loadKeys(b2dJson* json);
	void addContactListener();
	void addControllerLayer();
	static cocos2d::Scene* createScene();

	void win();
	void lose();

	b2PrismaticJoint* test;
};

#endif