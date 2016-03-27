#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class StartScene:public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StartScene);

	void touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
protected:
private:
	
	cocos2d::ui::Button* startBtn;
};
#endif 


