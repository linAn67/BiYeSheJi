#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "BasicLevelLayer.h"

class Level3:public BasicLevelLayer
{
public:
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();

};

#endif