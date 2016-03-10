#include "Level1.h"
#include "Level2.h"
USING_NS_CC;
std::string Level1::getFilename()
{
	return "level1.json";
}

void Level1::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
	
}

cocos2d::Scene* Level1::createScene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	//À¶É«±³¾°
	Color4B c4b = Color4B(104, 171, 213, 255);
	LayerColor* layer2 = LayerColor::create(c4b);
	scene->addChild(layer2, -2);

	Level1* layer = new Level1();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();

	return scene;
}

void Level1::win()
{

	auto director = Director::getInstance();
	auto scene = Level2::createScene();
	scene = TransitionFade::create(1.0f, scene, Color3B::WHITE);
	director->replaceScene(scene);
}