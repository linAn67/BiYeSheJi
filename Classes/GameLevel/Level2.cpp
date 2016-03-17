#include "GameLevel/Level2.h"

USING_NS_CC;
std::string Level2::getFilename()
{
	return "level2.json";
}

void Level2::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
	
}

cocos2d::Scene* Level2::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	//À¶É«±³¾°
	Color4B c4b = Color4B(104, 171, 213, 255);
	LayerColor* layer2 = LayerColor::create(c4b);
	scene->addChild(layer2, -2);

	Level2* layer = new Level2();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}