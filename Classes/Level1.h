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
	cocos2d::Sprite* bgSp;
	b2Body* m_backgroundBody;
	b2Body* m_obstacleControl;
	float32 rotateAngle;

	ControllerLayer* m_controlLayer;

	static cocos2d::Scene* createScene();
	
	Level1();

	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);
	virtual void clear();
	virtual void update(float dt);

	void addControllerLayer();
};

#endif