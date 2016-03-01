#include "HelloWorldScene.h"
#include "ControllerLayer.h"

USING_NS_CC;



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch *t, Event *){
		//do something
		Vec2 p = t->getLocation();
		log("%f|%f",p.x,p.y);
		
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
//     if ( !Layer::init() )
//     {
//         return false;
//     }
//     
//     Size visibleSize = Director::getInstance()->getVisibleSize();
//     Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_drawNode = DrawNode::create();
	addChild(m_drawNode);
	this->scheduleUpdate();
	this->initPhysics();
	this->createCircle();
	this->createRect();

	if (m_world)
	{
		m_debugDraw = new GLESDebugDraw(30);
		
		m_debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
		m_world->SetDebugDraw(m_debugDraw);
	}

	ControllerLayer*con = ControllerLayer::create();
	addChild(con);

	return true;
}



void HelloWorld::initPhysics()
{
	b2Vec2 gravity;
	gravity.Set(0, 0);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);

}

void HelloWorld::createCircle()
{
	b2BodyDef bd;
	bd.type = b2BodyType::b2_dynamicBody;
	bd.position.Set(100 / 30, 100 / 30);

	b2CircleShape circle;
	circle.m_radius = 60 / 30;
	b2FixtureDef fd;
	fd.shape = &circle;

	b2Body* body = m_world->CreateBody(&bd);
	body->CreateFixture(&fd);

}

void HelloWorld::createRect()
{
	b2BodyDef bd;
	bd.type = b2BodyType::b2_dynamicBody;
	bd.position.Set(200 / 30, 100 / 30);
	bd.angle = CC_DEGREES_TO_RADIANS(360);

	b2PolygonShape rect;
	rect.SetAsBox(50 / 30, 50 / 30);
	b2FixtureDef fd;
	fd.shape = &rect;

	b2Body* body = m_world->CreateBody(&bd);
	body->CreateFixture(&fd);
}



void HelloWorld::update(float delta)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	m_world->Step(delta, velocityIterations, positionIterations);
}

void HelloWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	CCLayer::draw(renderer, transform, flags);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	kmGLPushMatrix();

	m_world->DrawDebugData();

	kmGLPopMatrix();
}

