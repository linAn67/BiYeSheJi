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
	
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	CCSprite *spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setPosition(ccp(568, 320));	//中心位置。
	spr->setFlipY(true);			     //翻转，因为UI坐标和OpenGL坐标不同
	spr->setColor(Color3B::GRAY);		 //图片颜色变灰色
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

