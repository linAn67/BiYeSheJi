#ifndef __SaveLevelState_H__
#define __SaveLevelState_H__
#include "GameLevel/LevelStateData.h"
#include <list>
#include "GameLevel/BasicLevelLayer.h"
class SaveLevelState
{
private:
	//a container to save all body's data and angle in every frame
	std::list<LevelStateData*> m_levelStateDatas;
public:
	SaveLevelState();
	~SaveLevelState();
	void saveLevelStateDatas(b2Body* bodyList, float32 rotateAngle);
	//load data and set all body's position and angle
	void loadLevelStateDatasAndSet(float32 rotateAngle);
private:
	bool isTwoLevelStateDataEqual(LevelStateData* a, LevelStateData* b);
};

#endif
