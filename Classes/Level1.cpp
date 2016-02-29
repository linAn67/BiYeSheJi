#include "Level1.h"
#include "rubestuff/b2dJson.h"

using namespace std;
using namespace cocos2d;


Scene* Level1::scene()
{
	Scene *scene = Scene::create();

	// add layer as a child to scene
	Color4B c4b = Color4B(104, 171, 213, 255);
	LayerColor* layer2 = LayerColor::create(c4b);
	scene->addChild(layer2);
	Level1* layer = new Level1();
	layer->init();// do things that require virtual functions (can't do in constructor)
	scene->addChild(layer);
	layer->release();


	return scene;
}

Level1::Level1()
{

}

std::string Level1::getFilename()
{
	return "level1.json";
}

cocos2d::Point Level1::initialWorldOffset()
{
	//place (0,0) of physics world at center of bottom edge of screen
	Size s = Director::getInstance()->getWinSize();
	return Vec2(s.width / 2, s.height / 2);
}

float Level1::initialWorldScale()
{
	Size s = Director::getInstance()->getWinSize();
	return s.height / 8; //screen will be 8 physics units high
}

void Level1::afterLoadProcessing(b2dJson* json)
{
	RUBELayer::afterLoadProcessing(json);

	m_backgroundBody = json->getBodyByName("gruand");
	m_obstacleControl = json->getBodyByName("obstacleControl");
	
	rotateAngle = 0;
}

void Level1::clear()
{
	RUBELayer::clear();
}

void Level1::update(float dt)
{
	RUBELayer::update(dt);

// 	m_backgroundBody->rotateAroundExternalPoint(0, 0, CC_DEGREES_TO_RADIANS(0.01));
// 	m_obstacleControl->rotateAroundExternalPoint(0, 0, CC_DEGREES_TO_RADIANS(0.01));
	rotateAngle += 1;
	m_backgroundBody->SetTransform(m_backgroundBody->GetPosition(), CC_DEGREES_TO_RADIANS(rotateAngle));
	m_obstacleControl->SetTransform(m_obstacleControl->GetPosition(), CC_DEGREES_TO_RADIANS(rotateAngle));
	setImagePositionsFromPhysicsBodies();
}
