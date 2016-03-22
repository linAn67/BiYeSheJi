#include "GameLevel/Level8.h"

USING_NS_CC;

Scene* Level8::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level8* layer = new Level8();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

std::string Level8::getFilename()
{
	return "level8.json";
}

void Level8::afterLoadProcessing(b2dJson* json)
{
	Level5::afterLoadProcessing(json);
	m_whirlpool->m_sprite->setScale(1.5);

}

void Level8::update(float dt)
{
	Level5::update(dt);
	m_whirlpool->m_isOn = !m_button->m_isOn;
	if (m_whirlpool->m_isOn == false)
	{
		for each (auto bud in m_objsInWhirlpool)
		{
			bud->body->SetLinearDamping(0);
		}
		m_objsInWhirlpool.clear();
	}
}

float Level8::initialWorldScale()
{
	Size s = Director::getInstance()->getWinSize();
	return s.height / 10; //screen will be 8 physics units high
}
