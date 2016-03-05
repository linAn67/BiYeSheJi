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
	//由于cocos2dx封装的Vector仅支持继承自CCNode的类，所以这里用STL的Vector
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