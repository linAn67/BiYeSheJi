#ifndef __ButtonSprite_H__
#define __ButtonSprite_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"


class ButtonSprite :public cocos2d::Sprite
{
public:
	bool m_isOn;
	virtual bool init(b2Body* btnBody,b2Body* btnBaseBody,b2Fixture* btnSensor, b2Fixture* btnBaseSensor);
	static ButtonSprite* create(b2Body* btnBody, b2Body* btnBaseBody, b2Fixture* btnSensor, b2Fixture* btnBaseSensor);
	virtual void update(float delta);
	void keepBtnOff();
	b2Fixture* getBtnSensor();
	b2Fixture* getbtnBaseSensor();
private:
	b2Fixture* m_btnSensor;
	b2Fixture* m_btnBaseSensor;
	b2Body* m_btn;
	b2Body* m_btnBase;
	

};

#endif