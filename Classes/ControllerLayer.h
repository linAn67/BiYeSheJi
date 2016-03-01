#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
class ControllerLayer :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ControllerLayer);

	void moveToRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveToLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void clockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void antiClockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
protected:
private:
};
#endif 
