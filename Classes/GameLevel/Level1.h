#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "BasicLevelLayer.h"

class Level1:public BasicLevelLayer
{
public:
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
};

#endif