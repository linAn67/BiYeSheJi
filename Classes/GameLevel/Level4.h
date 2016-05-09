#ifndef __LEVEL4_H__
#define __LEVEL4_H__

#include "BasicLevelLayer.h"

class Level4:public BasicLevelLayer
{
public:
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();

};

#endif