#ifndef __BAISICLEVEL_H__
#define __BAISICLEVEL_H__

#include "cocos2d.h"
#include "RUBELayer.h"
#include "GameUI/ControllerLayer.h"
#include "rubestuff/b2dJson.h"
#include "Helper/SaveLevelState.h"
#include "GameLevel/ContactListener.h"
#include "GameData/GameManager.h"
#include "GameScene/GameScene.h"
#include "Sprite/Player.h"
//检查内存泄漏用
/*#include <vld.h>*/

class b2dJson;

enum BodyType
{
	BodyType_KEY,
	BodyType_FATALBALL,
	BodyType_Door,
	BodyType_Whirlpool,
	BodyType_Ground,
	BodyType_Edge,
	BodyType_Player=99
};

struct BasicLevelBodyUserData
{
	BodyType bodyType;
	b2Body* body;
};

class BasicLevelLayer:public RUBELayer
{
protected:
public: 
	Player* m_player;
	//b2Body* m_playerBody;						//存储主角的刚体用于移动
	//b2Fixture* m_playerFootSensorFixture;		//碰撞检测当前踩的地方是什么
	b2Body* m_door;								//通关的门
	bool m_isPlayerCollideWithDoor;
	int m_numFootContacts;
												//由于cocos2dx封装的Vector仅支持继承自CCNode的类，所以这里用STL的Vector
	std::vector<b2Body*> m_objectBodys;			//存储非场景刚体用于旋转操作
	//存储当前场景的旋转角度
	CC_SYNTHESIZE(float, rotateAngle, RotateAngle);

	//防止玩家多次重复点击通关按钮导致出错
	bool m_isLocked;

	//存放所有钥匙的bud
	std::set<BasicLevelBodyUserData*> m_allKeys;
	//存放待删除的钥匙的bud
	std::set<BasicLevelBodyUserData*> m_keyToProgress;


	ControllerLayer* m_controllerLayer;
	ContactListener* m_contactListener;

	virtual std::string getFilename();
	virtual cocos2d::Point initialWorldOffset();
	virtual float initialWorldScale();
	virtual void afterLoadProcessing(b2dJson* json);

	virtual void clear();
	virtual void update(float dt);

	void movePlayer();

	void rotateBodyPosition(b2Body* body);
	b2Vec2 rotateBodyVelocity(b2Vec2 velocity);

	static cocos2d::Scene* createScene();

	//当玩家通过关卡时，进行切换场景
	virtual void win();
	//当玩家失败时，弹出失败界面，玩家可选择重玩或离开当前关卡
	virtual void lose();

	void doPause();
	void rotateBodyAndChangeAngle(b2Body* body);

	//box2d的碰撞检测
	virtual void addContactListener();

private:
	//读取地面，设置其userdata，并其存入m_objectBodys
	void loadGround(b2dJson* json);
	void loadPlayer(b2dJson* json);
	//读取钥匙的刚体,设置其userdata，并将userdata存入m_allKeys
	void loadKeys(b2dJson* json);
	//读取球的刚体，设置其userdata，并其存入m_objectBodys
	void loadBalls(b2dJson* json);
	//连接刚体的链子
	void loadChains(b2dJson* json);
	//读取边界
	void loadEdge(b2dJson* json);
	//操作按钮层
	void addControllerLayer();

	void rotateAllObjectBodys();
	//旋转场景刚体,静态刚体,刚体位置在0,0
	void rotateAllGroundBodys();
	//旋转非场景的刚体,动态刚体
};

#endif