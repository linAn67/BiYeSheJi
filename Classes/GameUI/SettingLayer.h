#ifndef __SettingLayer_H__
#define __SettingLayer_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class SettingLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene(cocos2d::Sprite* scrshot);
	CREATE_FUNC(SettingLayer);

private:

	//用于重新开始游戏关卡
	void exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void sliderEvent(Ref *pSender, cocos2d::ui::Slider::EventType type);
};

#endif