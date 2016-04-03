#include "GameUI/PausemenuLayer.h"
#include "GameLevel/BasicLevelLayer.h"
#include "GameScene/GameScene.h"
#include "GameData/GameManager.h"
#include "GameUI/SettingLayer.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace ui;
using namespace cocos2d::experimental;

bool SettingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("setting/SettingLayer.csb");
	addChild(rootNode);
	
	Slider* sliderBgm = dynamic_cast<Slider*>(Helper::seekWidgetByName((Widget*)rootNode, "sliderBgm"));
	sliderBgm->addEventListener(CC_CALLBACK_2(SettingLayer::sliderEvent, this));
	float bgmVolume = AudioEngine::getVolume(0);
	sliderBgm->setPercent(bgmVolume*sliderBgm->getMaxPercent());
	Button* exitBtn = dynamic_cast<Button*>(Helper::seekWidgetByName((Widget*)rootNode, "btnExit"));
	exitBtn->addTouchEventListener(CC_CALLBACK_2(SettingLayer::exitBtnCallBack, this));

}

cocos2d::Scene* SettingLayer::createScene(cocos2d::Sprite* scrshot)
{
	CCScene *scene = CCScene::create();
	SettingLayer* mylayer = SettingLayer::create();
	scene->addChild(mylayer, 10);
	
	//将截图添加到层中
	mylayer->addChild(scrshot,-2);

	return scene;
}

void SettingLayer::sliderEvent(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		int maxPercent = slider->getMaxPercent();
		AudioEngine::setVolume(0, (float)percent / (float)maxPercent);
	}
}

void SettingLayer::exitBtnCallBack(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto director = Director::getInstance();

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		
		director->popScene();
		break;
	default:
		break;
	}
}

