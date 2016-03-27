#ifndef __ChoseLevelLayer_H__
#define __ChoseLevelLayer_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class ChoseLevelLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ChoseLevelLayer);
private:
	bool m_locked;
	void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	cocos2d::Vector<cocos2d::ui::Button*> m_btns;
};

#endif