#ifndef __PausemenuLayer_H__
#define __PausemenuLayer_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class BasicLevelLayer;

class PausemenuLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr, BasicLevelLayer* gameLevelLayer);
	CREATE_FUNC(PausemenuLayer);
private:
	//用于重新开始游戏关卡
	class BasicLevelLayer* m_gameLevelLayer;
	void replayBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void continueBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void settingBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif