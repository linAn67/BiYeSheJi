#ifndef __LoseLayer_H__
#define __LoseLayer_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class LoseLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);
	CREATE_FUNC(LoseLayer);
private:
	//用于重新开始游戏关卡
	void replayBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif