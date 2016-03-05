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
	b2Body* m_player;
	//����cocos2dx��װ��Vector��֧�ּ̳���CCNode���࣬����������STL��Vector
	std::vector<b2Body*> m_groundBodys;
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);
	ControllerLayer* m_controllerLayer;

	static cocos2d::Scene* createScene();


	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);
	virtual void clear();
	virtual void update(float dt);

	void movePlayer();
	void rotateGroundBody();
	void addControllerLayer();
};

#endif