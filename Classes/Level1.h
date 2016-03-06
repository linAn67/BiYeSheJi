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
	//存储主角的刚体用于移动
	b2Body* m_player;
	//由于cocos2dx封装的Vector仅支持继承自CCNode的类，所以这里用STL的Vector
	//存储场景刚体用于旋转操作
	std::vector<b2Body*> m_groundBodys;
	//存储非场景刚体用于旋转操作
	std::vector<b2Body*> m_objectBodys;
	//存储当前场景的旋转角度
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);
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

	void addControllerLayer();
	static cocos2d::Scene* createScene();
};

#endif