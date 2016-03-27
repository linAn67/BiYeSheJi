#ifndef __LEVEL5_H__
#define __LEVEL5_H__

#include "BasicLevelLayer.h"
#include "Sprite/WhirlpoolSprite.h"
#include "Sprite/ButtonSprite.h"
#include "GameLevel/ContactListenerWhirlpool.h"

class Level5:public BasicLevelLayer
{
public:
	WhirlpoolSprite* m_whirlpool;
	ButtonSprite* m_button;


	virtual std::string getFilename();
	virtual void afterLoadProcessing(b2dJson* json);
	static cocos2d::Scene* createScene();
	virtual void update(float dt);
	virtual void clear();
	//存放被吸入漩涡的刚体
	ContactListenerWhirlpool* m_contactListener;
	virtual void addContactListener();


	void addBodyUserDataInWhirlpool(MyBodyUserData* bud);
	//重置刚体进入漩涡时被设定的属性
	void removeBodyUserDataInWhirlpool(MyBodyUserData* bud);
	std::set<MyBodyUserData*> m_objsInWhirlpool;
private:
	void loadWhirlpool(b2dJson* json);
	void loadButton(b2dJson* json);
	void whirlpoolEffect();
};

#endif