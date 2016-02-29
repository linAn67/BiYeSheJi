#include "cocos2d.h"
#include "RUBELayer.h"

#ifndef __LEVEL1_H__
#define __LEVEL1_H__

class b2dJson;

class Level1:public RUBELayer
{
protected:
public: 
	b2Body* m_backgroundBody;

	static cocos2d::Scene* scene();
	
	Level1();

	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);
	virtual void clear();
	virtual void update(float dt);

};

#endif