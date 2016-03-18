#ifndef __BAISICLEVEL_H__
#define __BAISICLEVEL_H__

#include "cocos2d.h"
#include "RUBELayer.h"
#include "GameUI/ControllerLayer.h"
#include "rubestuff/b2dJson.h"
#include "Helper/SaveLevelState.h"
#include "GameLevel/ContactListener.h"
#include "GameData/GameManager.h"
#include "GameScene/GameScene.h"
//����ڴ�й©��
/*#include <vld.h>*/

class b2dJson;

enum BodyType
{
	BodyType_KEY,
	BodyType_FATALBALL,
	BodyType_Door
};

struct BasicLevelBodyUserData
{
	BodyType bodyType;
	b2Body* body;
};

class BasicLevelLayer:public RUBELayer
{
protected:
public: 
	
	b2Body* m_playerBody;						//�洢���ǵĸ��������ƶ�
	b2Fixture* m_playerFootSensorFixture;		//��ײ��⵱ǰ�ȵĵط���ʲô
	b2Body* m_door;								//ͨ�ص���
	bool m_isPlayerCollideWithDoor;
	int m_numFootContacts;
												//����cocos2dx��װ��Vector��֧�ּ̳���CCNode���࣬����������STL��Vector
	std::vector<b2Body*> m_objectBodys;			//�洢�ǳ�������������ת����
	//�洢��ǰ��������ת�Ƕ�
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);

	//��ֹ��Ҷ���ظ����ͨ�ذ�ť���³���
	bool m_isLocked;

	//�������Կ�׵�bud
	std::set<BasicLevelBodyUserData*> m_allKeys;
	//��Ŵ�ɾ����Կ�׵�bud
	std::set<BasicLevelBodyUserData*> m_keyToProgress;


	ControllerLayer* m_controllerLayer;
	ContactListener* m_contactListener;

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
	void rotateBodyPosition(b2Body* body);
	b2Vec2 rotateBodyVelocity(b2Vec2 velocity);
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

	static cocos2d::Scene* createScene();

	//�����ͨ���ؿ�ʱ�������л�����
	virtual void win();
	//�����ʧ��ʱ������ʧ�ܽ��棬��ҿ�ѡ��������뿪��ǰ�ؿ�
	virtual void lose();

	void doPause();
	void rotateBodyAndChangeAngle(b2Body* body);
};

#endif