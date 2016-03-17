#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

enum RotationDirection
{
	RD_CLOCKWISE,
	RD_ANTICLOCKWISE,
	RD_NOTROTATING
};

enum PlayerMoveDirection
{
	PLAYER_MOVETOLEFT,
	PLAYER_MOVETORIGHT,
	PLAYER_NOTMOVING
};

class ControllerLayer :public cocos2d::Layer
{
public:
	RotationDirection		m_rotationDirection;
	float					m_rotateAngle;//用于翻转box2d场景
	PlayerMoveDirection		m_playerMoveDirection;
	bool					m_returnToPreviousLevelState;
	class BasicLevelLayer*		m_layer;
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ControllerLayer);

	virtual void update(float delta);
protected:
private:
	

	void moveToRightBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveToLeftBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void clockwiseBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void antiClockwiseBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void confirmBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void pauseBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};
#endif 
