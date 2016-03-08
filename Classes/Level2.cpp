#include "Level2.h"
USING_NS_CC;
std::string Level2::getFilename()
{
	return "level1.json";
}

void Level2::afterLoadProcessing(b2dJson* json)
{
	BasicLevelLayer::afterLoadProcessing(json);
	m_groundBodys.push_back(json->getBodyByName("obstacle"));
}

