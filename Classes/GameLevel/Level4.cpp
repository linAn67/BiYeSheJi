#include "GameLevel/Level4.h"
USING_NS_CC;


Scene* Level4::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level4* layer = new Level4();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

void Level4::win()
{
	if (!m_isLocked)
	{
		auto director = Director::getInstance();
		auto scene = GameScene::createScene(3);
		scene = TransitionFade::create(1.0f, scene, Color3B::WHITE);
		director->replaceScene(scene);
		m_isLocked = true;
	}
}

void Level4::clear()
{
	BasicLevelLayer::clear();
}

std::string Level4::getFilename()
{
	return "level4.json";
}

void Level4::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
}