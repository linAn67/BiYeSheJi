#include "cocos2d.h"
#include "RUBELayer.h"
#include "ControllerLayer.h"


#ifndef __LEVEL1_H__
#define __LEVEL1_H__

class b2dJson;



class Level1:public RUBELayer
{
protected:
public: 
	//�洢���ǵĸ��������ƶ�
	b2Body* m_player;
	//����cocos2dx��װ��Vector��֧�ּ̳���CCNode���࣬����������STL��Vector
	//�洢��������������ת����
	std::vector<b2Body*> m_groundBodys;
	//�洢�ǳ�������������ת����
	std::vector<b2Body*> m_objectBodys;
	//�洢��ǰ��������ת�Ƕ�
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);
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

	void addControllerLayer();
	static cocos2d::Scene* createScene();
};

#endif