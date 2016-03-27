#ifndef __BAISICLEVEL_H__
#define __BAISICLEVEL_H__

#include "cocos2d.h"
#include "GameLevel/BasicLoadLayer.h"
#include "RUBELayer.h"
#include "GameUI/ControllerLayer.h"
#include "rubestuff/b2dJson.h"
#include "Helper/SaveLevelState.h"
#include "GameLevel/ContactListener.h"
#include "GameData/GameManager.h"
#include "GameScene/GameScene.h"
#include "Sprite/Player.h"
#include "GameData/MyBodyUserData.h"
//����ڴ�й©��
/*#include <vld.h>*/

class b2dJson;

class BasicLevelLayer:public BasicLoadLayer
{

public: 
	Player* m_player;
	b2Body* m_door;
	bool m_isPlayerCollideWithDoor;
	int m_numFootContacts;

	//�洢�ǳ�������������ת����
	std::vector<b2Body*> m_objectBodys;
	//�洢��ǰ��������ת�Ƕ�
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);

	//��ֹ��Ҷ���ظ����ͨ�ذ�ť���³���
	bool m_isLocked;

	//�������Կ�׵�bud
	std::set<MyBodyUserData*> m_allKeys;
	//��Ŵ�ɾ����Կ�׵�bud
	std::set<MyBodyUserData*> m_keyToProgress;


	ControllerLayer* m_controllerLayer;
	ContactListener* m_contactListener;

	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);

	virtual void clear();
	virtual void update(float dt);

	void movePlayer();

	void rotateBodyPosition(b2Body* body);
	b2Vec2 rotateB2Vec(b2Vec2 velocity);

	static cocos2d::Scene* createScene();

	//�����ͨ���ؿ�ʱ�������л�����
	virtual void win();
	//�����ʧ��ʱ������ʧ�ܽ��棬��ҿ�ѡ��������뿪��ǰ�ؿ�
	virtual void lose();

	void doPause();
	void rotateBodyAndChangeAngle(b2Body* body);

	//box2d����ײ���
	virtual void addContactListener();

private:
	//��ȡ���棬������userdata���������m_objectBodys
	void loadGround(b2dJson* json);
	void loadPlayer(b2dJson* json);
	//��ȡԿ�׵ĸ���,������userdata������userdata����m_allKeys
	void loadKeys(b2dJson* json);
	//��ȡ��ĸ��壬������userdata���������m_objectBodys
	void loadBalls(b2dJson* json);
	//���Ӹ��������
	void loadChains(b2dJson* json);
	//��ȡ�߽�
	void loadEdge(b2dJson* json);
	//��ȡ��
	void loadDoor(b2dJson* json);

	//������ť��
	void addControllerLayer();

	void rotateAllObjectBodys();
	

};

#endif