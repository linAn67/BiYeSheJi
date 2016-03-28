#include "GameUI/LoseLayer.h"
#include "GameScene/GameScene.h"
#include "GameData/GameManager.h"
#include "ChoseLevelLayer.h"
USING_NS_CC;
using namespace ui;

bool LoseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("loselayer/LoseLayer.csb");
	addChild(rootNode);
	
	Button* replayBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Replay");
	replayBtn->addTouchEventListener(CC_CALLBACK_2(LoseLayer::replayBtnCallBack, this));

	Button* exitBtn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, "Exit");
	exitBtn->addTouchEventListener(CC_CALLBACK_2(LoseLayer::exitBtnCallBack, this));
}

cocos2d::Scene* LoseLayer::createScene(cocos2d::RenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	LoseLayer* mylayer = LoseLayer::create();
	scene->addChild(mylayer, 10);
	
	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	//����Sprite��ӵ�GamePause��������
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//����λ�á�
	spr->setFlipY(true);			     //��ת����ΪUI�����OpenGL���겻ͬ
	spr->setColor(Color3B::GRAY);		 //ͼƬ��ɫ���ɫ
	scene->addChild(spr);

	return scene;
}

void LoseLayer::replayBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto curLevel = GameManager::getInstance()->curLevel;
	auto scene = GameScene::createScene(curLevel);
	director->replaceScene(scene);
}

void LoseLayer::exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
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

