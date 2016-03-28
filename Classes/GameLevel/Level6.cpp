#include "GameLevel/Level6.h"

USING_NS_CC;
//开启状态持续时间
#define TIME1 5.0f
//关闭状态持续时间
#define TIME2 1.0f

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
	m_whirlpool->getSprite()->setScale(1.5);
	time = 0;
}

void Level6::update(float dt)
{
	Level5::update(dt);
	time += dt;
	if (m_whirlpool->m_isOn)
	{
		if (time>TIME1)
		{
			time -= TIME1;
			m_whirlpool->m_isOn = false;
		}
	}
	else
	{
		if (time > TIME2)
		{
			time -= TIME2;
			m_whirlpool->m_isOn = true;
		}
	}
}
