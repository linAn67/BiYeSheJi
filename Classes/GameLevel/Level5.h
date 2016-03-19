#ifndef __LEVEL5_H__
#define __LEVEL5_H__

#include "BasicLevelLayer.h"
#include "Sprite/WhirlpoolSprite.h"
#include "GameLevel/ContactListenerWhirlpool.h"

class Level5:public BasicLevelLayer
{
public:
	WhirlpoolSprite* m_whirlpool;
	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
	virtual void update(float dt);
	virtual void clear();
	//存放被吸入漩涡的刚体
	ContactListenerWhirlpool* m_contactListener;
	virtual void addContactListener();
	void addBodyUserDataToSet(BasicLevelBodyUserData* bud);
	std::set<BasicLevelBodyUserData*> m_objsInWhirlpool;
private:
	void loadWhirlpool(b2dJson* json);
	void whirlpoolEffect();
};

#endif