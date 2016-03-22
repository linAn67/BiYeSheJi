#ifndef __LEVEL8_H__
#define __LEVEL8_H__

#include "GameLevel/Level5.h"


class Level8:public Level5
{
public:
	
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
	virtual void update(float dt);
	virtual float initialWorldScale();
};

#endif