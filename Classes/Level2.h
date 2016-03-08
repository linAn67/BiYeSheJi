#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "BasicLevelLayer.h"

class Level2:public BasicLevelLayer
{
public:
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);

};

#endif