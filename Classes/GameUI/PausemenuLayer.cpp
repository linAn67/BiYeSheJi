#include "GameUI/PausemenuLayer.h"
#include "GameLevel/BasicLevelLayer.h"
#include "GameScene/GameScene.h"
#include "GameData/GameManager.h"
#include "GameUI/ChoseLevelLayer.h"
#include "GameUI/SettingLayer.h"
USING_NS_CC;
using namespace ui;

bool PausemenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("pausemenu/PauseLayer.csb");
	addChild(rootNode);
	
	Button* replayBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Replay");
	replayBtn->addTouchEventListener(CC_CALLBACK_2(PausemenuLayer::replayBtnCallBack, this));

	Button* continueBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Continue");
	continueBtn->addTouchEventListener(CC_CALLBACK_2(PausemenuLayer::continueBtnCallBack, this));

	Button* settingBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Setting");
	settingBtn->addTouchEventListener(CC_CALLBACK_2(PausemenuLayer::settingBtnCallBack, this));

	Button* exitBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Exit");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(PausemenuLayer::exitBtnCallBack, this));

}

cocos2d::Scene* PausemenuLayer::createScene(cocos2d::RenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	PausemenuLayer* mylayer = PausemenuLayer::create();
	scene->addChild(mylayer, 10);
	
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//中心位置。
	spr->setFlipY(true);			     //翻转，因为UI坐标和OpenGL坐标不同
	spr->setColor(Color3B::GRAY);		 //图片颜色变灰色
	scene->addChild(spr, 0, 998);
	return scene;
}

void PausemenuLayer::replayBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto curLevel = GameManager::getInstance()->curLevel;
	Scene* scene;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		scene = GameScene::createScene(curLevel);
		director->replaceScene(scene);
		break;
	default:
		break;
	}
}

void PausemenuLayer::continueBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	director->popScene();
}

void PausemenuLayer::settingBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	bool isBtnPress;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		isBtnPress = true;
		break;
	default:
		isBtnPress = false;
		break;
	}
	if (isBtnPress)
	{
		auto director = Director::getInstance();
		Sprite* sp = dynamic_cast<Sprite*>(this->getParent()->getChildByTag(998));
		sp = Sprite::createWithTexture(sp->getTexture());
		sp->setPosition(ccp(568, 320));	//中心位置。
		sp->setFlipY(true);			     //翻转，因为UI坐标和OpenGL坐标不同
		sp->setColor(Color3B::GRAY);		 //图片颜色变灰色
		director->pushScene(SettingLayer::createScene(sp));
	}
}

void PausemenuLayer::exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto curLevel = GameManager::getInstance()->curLevel;
	Scene* scene;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		
		scene = ChoseLevelLayer::createScene();
		director->replaceScene(scene);
		break;
	default:
		break;
	}
}

