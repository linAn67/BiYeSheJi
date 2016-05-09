#ifndef __LEVEL8_H__
#define __LEVEL8_H__

#include "GameLevel/Level7.h"


class Level8:public Level7
{
public:
	
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
	virtual float initialWorldScale();
};

#endif