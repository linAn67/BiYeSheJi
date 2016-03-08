#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class BasicLevelLayer;

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
	float					m_rotateAngle;//���ڷ�תbox2d����
	PlayerMoveDirection		m_playerMoveDirection;
	BasicLevelLayer*					m_layer;

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ControllerLayer);

	virtual void update(float delta);

	void moveToRight(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void moveToLeft(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void clockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void antiClockwiseRotate(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void confirmBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
protected:
private:
};
#endif 
