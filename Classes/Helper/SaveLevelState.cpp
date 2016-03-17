#include "Helper/SaveLevelState.h"

SaveLevelState::SaveLevelState()
{
}


SaveLevelState::~SaveLevelState()
{
	for each (auto lsDatas in m_levelStateDatas)
	{
		for each (auto data in lsDatas->allBodyDatas)
		{
			if (nullptr!=data)
			{
				delete data;
				data = nullptr;
			}
		}
		lsDatas->allBodyDatas.clear();
		delete lsDatas;
		lsDatas = nullptr;
	}
	m_levelStateDatas.clear();
}


void SaveLevelState::saveLevelStateDatas(b2Body* bodyList, float32 rotateAngle)
{
	LevelStateData* lsData = new LevelStateData;
	for (b2Body* body = bodyList; body; body = body->GetNext())
	{
		BodyData* bDate = new BodyData;
		bDate->body = body;
		bDate->position = body->GetPosition();
		bDate->angle = body->GetAngle();
		bDate->angularVelocity = body->GetAngularVelocity();
		bDate->linearVelocity = body->GetLinearVelocity();
		bDate->active = body->IsActive();

		//也许该弄个容器专门存key，然后进行处理
		lsData->allBodyDatas.push_back(bDate);
	}
	lsData->levelRotateAngle = rotateAngle;
	//////////////////////////////////////////////////////////////////////////
	//check if the data equal to the previous one then delete the data
	//////////////////////////////////////////////////////////////////////////

	if (m_levelStateDatas.size() == 0)
	{
		//no data in list,save data
		m_levelStateDatas.push_back(lsData);
	}
	else
	{
		if (!isTwoLevelStateDataEqual(lsData,m_levelStateDatas.back()))
		{
			//not equal,save data
			m_levelStateDatas.push_back(lsData);
		}
		else
		{
			//equal. need to delete the data
			for each (auto data in lsData->allBodyDatas)
			{
				if (nullptr != data)
				{
					delete data;
					data = nullptr;
				}
			}
			lsData->allBodyDatas.clear();
			delete lsData;
			lsData = nullptr;
		}
	}
}

void SaveLevelState::loadLevelStateDatasAndSet(float32 rotateAngle)
{
	if (m_levelStateDatas.size() == 0)
	{
		LevelStateData* lsData = m_levelStateDatas.back();
		for each (auto bodyData in lsData->allBodyDatas)
		{
			if (nullptr != bodyData)
			{
				b2Body* b = bodyData->body;
				b->SetTransform(bodyData->position, bodyData->angle);
				b->SetLinearVelocity(bodyData->linearVelocity);
				b->SetAngularVelocity(bodyData->angularVelocity);
				b->SetActive(bodyData->active);
				//after set,delete body's data
				delete bodyData;
				bodyData = nullptr;
			}
		}
		rotateAngle = lsData->levelRotateAngle;
		lsData->allBodyDatas.clear();
		delete lsData;
		lsData = nullptr;
		m_levelStateDatas.pop_back();
	}
}

bool SaveLevelState::isTwoLevelStateDataEqual(LevelStateData* a, LevelStateData* b)
{
	//compare angle and vector size
	if ((a->levelRotateAngle != b->levelRotateAngle) ||
		(a->allBodyDatas.size() != b->allBodyDatas.size()))
	{
		return false;
	}

	unsigned int size = a->allBodyDatas.size();
	std::vector<BodyData*> aBDs = a->allBodyDatas;
	std::vector<BodyData*> bBDs = b->allBodyDatas;
	for (unsigned int i = 0; i < size; ++i)
	{
		BodyData* ai = aBDs[i];
		BodyData* bi = bBDs[i];
		//compare body,position,angle,active except velocity
		//because liner velocity and angular velocity changed in every frame
		//though the body is static all the time
		if (ai->body != bi->body ||
			!(ai->position == bi->position) ||
			ai->angle != bi->angle ||
			ai->active != bi->active)
		{
			return false;
		}
	}
	return true;
}
