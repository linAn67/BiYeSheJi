#include "GameLevel/Level7.h"

USING_NS_CC;

Scene* Level7::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level7* layer = new Level7();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

std::string Level7::getFilename()
{
	return "level7.json";
}

void Level7::afterLoadProcessing(b2dJson* json)
{
	Level5::afterLoadProcessing(json);
	m_whirlpool->m_sprite->setScale(1.1);

}

void Level7::update(float dt)
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
