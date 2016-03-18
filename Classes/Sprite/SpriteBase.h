#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

class HelloWorld : public cocos2d::Layer
{
private:
	b2World* m_world;
	GLESDebugDraw* m_debugDraw;
	cocos2d::DrawNode* m_drawNode;
public:
    static cocos2d::Scene* createScene();

	void onEnter();
	virtual bool init() override;
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	
	void initPhysics();
	void createCircle();
	void createRect();

	void update(float delta);
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
