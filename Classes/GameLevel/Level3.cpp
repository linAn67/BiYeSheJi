#include "GameLevel/Level3.h"
USING_NS_CC;


Scene* Level3::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Level3* layer = new Level3();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

void Level3::clear()
{
	BasicLevelLayer::clear();
}

std::string Level3::getFilename()
{
	return "level3.json";
}

void Level3::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
}

