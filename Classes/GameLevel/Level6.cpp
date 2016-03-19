#include "GameLevel/Level6.h"

USING_NS_CC;
#define TIMEINTERVAL 4.0f

Scene* Level6::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level6* layer = new Level6();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

std::string Level6::getFilename()
{
	return "level6.json";
}

void Level6::afterLoadProcessing(b2dJson* json)
{
	Level5::afterLoadProcessing(json);
	m_whirlpool->m_sprite->setScale(1.5);
	time = 0;
}

void Level6::update(float dt)
{
	Level5::update(dt);
	time += dt;
	if (time>TIMEINTERVAL)
	{
		time -= TIMEINTERVAL;
		m_whirlpool->m_isOn = !m_whirlpool->m_isOn;
	}
}
