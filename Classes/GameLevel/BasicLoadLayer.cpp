#include "GameLevel/BasicLoadLayer.h"
#include "rubestuff/b2dJson.h"
#include "rubestuff/b2dJsonImage.h"

using namespace std;
using namespace cocos2d;

BasicLoadLayer::BasicLoadLayer()
{
    m_world = NULL;
}

BasicLoadLayer::~BasicLoadLayer()
{
    unscheduleUpdate();
    clear();
}

Scene* BasicLoadLayer::scene()
{
    auto scene = Scene::create();
    BasicLoadLayer* layer = BasicLoadLayer::create();
    scene->addChild(layer);
    return scene;
}

bool BasicLoadLayer::init()
{
    Layer::init();
    
    setAnchorPoint( Vec2(0,0) );
    
    //从子类设置初始位置和缩放
    setPosition( initialWorldOffset() );
    setScale( initialWorldScale() );
    
    // 从json文件中载入box2d物理世界，在函数结尾处会调用afterLoadProcessing
    loadWorld();
    
    scheduleUpdate();
    
    return true;
}

// 在子类中重写这个函数即可修改载入的json文件名
string BasicLoadLayer::getFilename()
{
    return "jointTypes.json";
}


// Override this in subclasses to set the inital view position
Point BasicLoadLayer::initialWorldOffset()
{
    Size s = Director::getInstance()->getWinSize();
    return Vec2( s.width/2, 0 );
}


// Override this in subclasses to set the inital view scale
float BasicLoadLayer::initialWorldScale()
{
    Size s = Director::getInstance()->getWinSize();
    return s.height / 10; //screen will be 10 physics units high
}

void BasicLoadLayer::loadWorld()
{
    clear();
    
    // 获取待加载的json文件的文件名
    string filename = getFilename();
    
    // 找到文件的绝对路径
    string fullpath = CCFileUtils::getInstance()->fullPathForFilename(filename.c_str());
    
    // 输出文件的实际位置
    // 直接将场景发布到这个位置，然后不用重新编译即可载入场景
    CCLOG("Full path is: %s", fullpath.c_str());
    
	//从json文件中创造world，如果出错，world将保持NULL，错误信息将会提示发生了什么事
    b2dJson json;
    std::string errMsg;
    std::string jsonContent = CCFileUtils::getInstance()->getStringFromFile(fullpath.c_str());
    m_world = json.readFromString(jsonContent, errMsg);
    
	//如果世界创建成功，则进行图片的载入以及其他的需要初始化的东西
    if ( m_world ) {
        CCLOG("Loaded JSON ok");
		loadImages(&json);
		afterLoadProcessing(&json);
    }
    else
        CCLOG("%s",errMsg.c_str());
}

void BasicLoadLayer::loadImages(b2dJson* json)
{
	vector<b2dJsonImage*> b2dImages;
	//获取json文件中包含的图片信息放到vector中
	json->getAllImages(b2dImages);
	//通过遍历这些图片信息为之创造精灵，并且初始化各项属性
	for each (auto img in b2dImages)
	{
		Sprite* sprite = Sprite::create(img->file.c_str());
		if (!sprite)
		{
			continue;
		}

		addChild(sprite);
		reorderChild(sprite, img->renderOrder);

		sprite->setFlippedX(img->flip);
		sprite->setColor(Color3B(img->colorTint[0], img->colorTint[1], img->colorTint[2]));
		sprite->setOpacity(img->colorTint[3]);
		sprite->setScale(img->scale / sprite->getContentSize().height);

		ImageInfo*imgInfo = new ImageInfo;
		imgInfo->sprite = sprite;
		imgInfo->name = img->name;
		imgInfo->body = img->body;
		imgInfo->scale = img->scale;
		imgInfo->aspectScale = img->aspectScale;
		imgInfo->angle = img->angle;
		imgInfo->center = Vec2(img->center.x, img->center.y);
		imgInfo->opacity = img->opacity;
		imgInfo->flip = img->flip;
		for (int n = 0; n < 4; ++n)
		{
			imgInfo->colorTint[n] = img->colorTint[n];
		}
		m_imageInfos.insert(imgInfo);
	}
	setImagePositionsFromPhysicsBodies();
}

void BasicLoadLayer::afterLoadProcessing(b2dJson* json)
{
    
}

void BasicLoadLayer::clear()
{
	for each (auto imgInfo in m_imageInfos)
	{
		removeChild(imgInfo->sprite, true);
	}
	m_imageInfos.clear();

    if ( m_world ) {
        CCLOG("Deleting Box2D world");
        delete m_world;
    }
}

void BasicLoadLayer::update(float dt)
{
	if (m_world)
	{
		m_world->Step(1 / 60.0, 8, 1);
	}
	setImagePositionsFromPhysicsBodies();
}

void BasicLoadLayer::setImagePositionsFromPhysicsBodies()
{
	for each (auto imgInfo in m_imageInfos)
	{
		Vec2 pos = imgInfo->center;
		float angle = -imgInfo->angle;
		if (imgInfo->body) {
			//根据刚体角度旋转图片的本地中心角度
			b2Vec2 localPos(pos.x, pos.y);
			b2Rot rot(imgInfo->body->GetAngle());
			localPos = b2Mul(rot, localPos) + imgInfo->body->GetPosition();
			pos.x = localPos.x;
			pos.y = localPos.y;
			angle += -imgInfo->body->GetAngle();
		}
		imgInfo->sprite->setRotation(CC_RADIANS_TO_DEGREES(angle));
		imgInfo->sprite->setPosition(pos);
	}
}


void BasicLoadLayer::removeBodyFromWorld(b2Body* body)
{
	m_world->DestroyBody(body);

	vector<ImageInfo*> imagesToRemove;
	for each (auto imgInfo in m_imageInfos)
	{
		if (imgInfo->body == body)
		{
			removeChild(imgInfo->sprite, true);
			imagesToRemove.push_back(imgInfo);
		}
	}

	for each (auto imgInfo in imagesToRemove)
	{
		m_imageInfos.erase(imgInfo);
	}
}

//将精灵从父节点中移除，同时也移除图片信息
void BasicLoadLayer::removeImageFromWorld(ImageInfo* imgInfo)
{
	removeChild(imgInfo->sprite, true);
	m_imageInfos.erase(imgInfo);
}

//遍历刚体获取对应的精灵
cocos2d::Sprite* BasicLoadLayer::getAnySpriteOnBody(b2Body* body)
{
	for each (auto imgInfo in m_imageInfos)
	{
		if (imgInfo->body == body)
			return imgInfo->sprite;
	}
	return nullptr;
}

//遍历图片名字获取对应的精灵
cocos2d::Sprite* BasicLoadLayer::getSpriteWithImageName(std::string name)
{
	for each(auto imgInfo in m_imageInfos)
	{
		if (imgInfo->name == name)
		{
			return imgInfo->sprite;
		}
		return nullptr;
	}
}