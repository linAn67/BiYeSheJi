#include "GameUI/ChoseLevelLayer.h"
#include "GameData/GameManager.h"
#include "GameScene/GameScene.h"

USING_NS_CC;
using namespace ui;

bool ChoseLevelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_locked = false;
	auto rootNode = CSLoader::createNode("choselevel/ChoseScene.csb");
	addChild(rootNode);

	for (int i = 0; i < 8; ++i)
	{
		Button* btn = (Button*)Helper::seekWidgetByName((Widget*)rootNode, std::to_string(i+1));
		btn->addTouchEventListener(CC_CALLBACK_2(ChoseLevelLayer::touchEvent, this));
		m_btns.pushBack(btn);
	}

	return true;
}

cocos2d::Scene* ChoseLevelLayer::createScene()
{
	CCScene *scene = CCScene::create();
	ChoseLevelLayer* mylayer = ChoseLevelLayer::create();
	scene->addChild(mylayer, 10);

	return scene;
}

void ChoseLevelLayer::touchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	ssize_t index = m_btns.getIndex((Button*)sender);
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (!m_locked)
		{
			GameManager::getInstance()->curLevel = index + 1;
			GameScene::replaceScene(index + 1);
			m_locked = true;
		}
		break;
	default:
		break;
	}
}

