#include "PausemenuLayer.h"
#include "BasicLevelLayer.h"

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

/*
cocos2d::Scene* PausemenuLayer::createScene(CCRenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	PausemenuLayer* mylayer = PausemenuLayer::create();
	scene->addChild(mylayer,10);

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//中心位置。
	spr->setFlipY(true);			     //翻转，因为UI坐标和OpenGL坐标不同
	spr->setColor(Color3B::GRAY);		 //图片颜色变灰色
	scene->addChild(spr);


	return scene;
}*/

cocos2d::Scene* PausemenuLayer::createScene(cocos2d::RenderTexture* sqr, BasicLevelLayer* gameLevelLayer)
{
	CCScene *scene = CCScene::create();
	PausemenuLayer* mylayer = PausemenuLayer::create();
	scene->addChild(mylayer, 10);
	mylayer->m_gameLevelLayer = gameLevelLayer;
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//中心位置。
	spr->setFlipY(true);			     //翻转，因为UI坐标和OpenGL坐标不同
	spr->setColor(Color3B::GRAY);		 //图片颜色变灰色
	scene->addChild(spr);


	return scene;
}

void PausemenuLayer::replayBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	m_gameLevelLayer->replay();
}

void PausemenuLayer::continueBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	director->popScene();
}

void PausemenuLayer::settingBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{

}

void PausemenuLayer::exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{

}

