#ifndef __BAISICLEVEL_H__
#define __BAISICLEVEL_H__

#include "cocos2d.h"
#include "RUBELayer.h"
#include "ControllerLayer.h"
#include "rubestuff/b2dJson.h"

class b2dJson;

enum BodyType
{
	BodyType_KEY,
	BodyType_FATALBALL
};

struct BodyData 
{
	b2Body* body;
	b2Vec2 position;
	float32 angle;
	b2Vec2 linearVelocity;

};

struct LevelStateData
{
	std::vector<BodyData*> allBodyDatas;
	float levelRotateAngle;
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

	class BasicLevelLayer* m_layer;
};

class BasicLevelLayer:public RUBELayer
{
protected:
public: 
	BasicLevelContactListener* m_contactListener;
	
	b2Body* m_playerBody;						//�洢���ǵĸ��������ƶ�
	b2Fixture* m_playerFootSensorFixture;			//��ײ��⵱ǰ�ȵĵط���ʲô
	b2Body* m_door;							//ͨ�ص���
	bool m_isPlayerCollideWithDoor;
											//����cocos2dx��װ��Vector��֧�ּ̳���CCNode���࣬����������STL��Vector
	std::vector<b2Body*> m_groundBodys;		//�洢��������������ת����
											
	std::vector<b2Body*> m_objectBodys;		//�洢�ǳ�������������ת����
	//�洢��ǰ��������ת�Ƕ�
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);

	//�������Կ�׵�bud
	std::set<BasicLevelBodyUserData*> m_allKeys;
	//��Ŵ�ɾ����Կ�׵�bud
	std::set<BasicLevelBodyUserData*> m_keyToProgress;
	//ÿһ֡��������������и����λ���Լ���ת�Ƕ�
	std::set<LevelStateData*> m_levelStateDatas;

	ControllerLayer* m_controllerLayer;


	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);


	
	virtual void clear();
	virtual void update(float dt);

	void movePlayer();
	void rotateAllObjectBodys();
	//��ת��������,��̬����,����λ����0,0
	void rotateAllGroundBodys();
	//��ת�ǳ����ĸ���,��̬����
	void rotateObjectBody(b2Body* body);

	//��ȡԿ�׵ĸ���,������userdata������userdata����m_allKeys
	void loadKeys(b2dJson* json);
	//��ȡ��ĸ��壬������userdata���������m_objectBodys
	void loadBalls(b2dJson* json);
	//���Ӹ��������
	void loadChains(b2dJson* json);
	//box2d����ײ���
	void addContactListener();
	//������ť��
	void addControllerLayer();
	//����ؿ���ǰ���и����λ�ü��Ƕ�
	void saveLevelStateDatas();
	//��ȡ�����ùؿ���ǰ���и����λ�ü��Ƕ�
	void loadAndSetLevelStateDatas();

	static cocos2d::Scene* createScene();

	//�����ͨ���ؿ�ʱ�������л�����
	virtual void win();
	//�����ʧ��ʱ������ʧ�ܽ��棬��ҿ�ѡ��������뿪��ǰ�ؿ�
	virtual void lose();

};

#endif