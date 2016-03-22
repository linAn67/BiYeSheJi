#ifndef __LEVEL7_H__
#define __LEVEL7_H__

#include "GameLevel/Level5.h"
#include "Sprite/WhirlpoolSprite.h"
#include "GameLevel/ContactListenerWhirlpool.h"

class Level7:public Level5
{
public:
	
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
	virtual void update(float dt);

};

#endif