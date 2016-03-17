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

	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	//����Sprite��ӵ�GamePause��������
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//����λ�á�
	spr->setFlipY(true);			     //��ת����ΪUI�����OpenGL���겻ͬ
	spr->setColor(Color3B::GRAY);		 //ͼƬ��ɫ���ɫ
	scene->addChild(spr);


	return scene;
}*/

cocos2d::Scene* PausemenuLayer::createScene(cocos2d::RenderTexture* sqr, BasicLevelLayer* gameLevelLayer)
{
	CCScene *scene = CCScene::create();
	PausemenuLayer* mylayer = PausemenuLayer::create();
	scene->addChild(mylayer, 10);
	mylayer->m_gameLevelLayer = gameLevelLayer;
	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	//����Sprite��ӵ�GamePause��������
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//����λ�á�
	spr->setFlipY(true);			     //��ת����ΪUI�����OpenGL���겻ͬ
	spr->setColor(Color3B::GRAY);		 //ͼƬ��ɫ���ɫ
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

