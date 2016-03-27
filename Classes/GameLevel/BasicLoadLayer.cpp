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
    
    //���������ó�ʼλ�ú�����
    setPosition( initialWorldOffset() );
    setScale( initialWorldScale() );
    
    // ��json�ļ�������box2d�������磬�ں�����β�������afterLoadProcessing
    loadWorld();
    
    scheduleUpdate();
    
    return true;
}

// ����������д������������޸������json�ļ���
string BasicLoadLayer::getFilename()
{
    return "jointTypes.json";
}


// Override this in subclasses to set the inital view position
Point BasicLoadLayer::initialWorldOffset()
{
    // This function should return the location in pixels to place
    // the (0,0) point of the physics world. The screen position
    // will be relative to the bottom left corner of the screen.
    
    //place (0,0) of physics world at center of bottom edge of screen
    Size s = Director::getInstance()->getWinSize();
    return Vec2( s.width/2, 0 );
}


// Override this in subclasses to set the inital view scale
float BasicLoadLayer::initialWorldScale()
{
    // This method should return the number of pixels for one physics unit.
    // When creating the scene in RUBE I can see that the jointTypes scene
    // is about 8 units high, so I want the height of the view to be about
    // 10 units, which for iPhone in landscape (480x320) we would return 32.
    // But for an iPad in landscape (1024x768) we would return 76.8, so to
    // handle the general case, we can make the return value depend on the
    // current screen height.
    
    Size s = Director::getInstance()->getWinSize();
    return s.height / 10; //screen will be 10 physics units high
}

// Attempts to load the world from the .json file given by getFilename.
// If successful, the method afterLoadProcessing will also be called,
// to allow subclasses to do something extra while the b2dJson information
// is still available.
void BasicLoadLayer::loadWorld()
{
    // The clear method should undo anything that is done in this method,
    // and also whatever is done in the afterLoadProcessing method.
    clear();
    
    // ��ȡ�����ص�json�ļ����ļ���
    string filename = getFilename();
    
    // �ҵ��ļ��ľ���·��
    string fullpath = CCFileUtils::getInstance()->fullPathForFilename(filename.c_str());
    
    // ����ļ���ʵ��λ��
    // ֱ�ӽ��������������λ�ã�Ȼ�������±��뼴�����볡��
    CCLOG("Full path is: %s", fullpath.c_str());
    
	//��json�ļ��д���world���������world������NULL��������Ϣ������ʾ������ʲô��
    b2dJson json;
    std::string errMsg;
    std::string jsonContent = CCFileUtils::getInstance()->getStringFromFile(fullpath.c_str());
    m_world = json.readFromString(jsonContent, errMsg);
    
	//������紴���ɹ��������ͼƬ�������Լ���������Ҫ��ʼ���Ķ���
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
	//��ȡjson�ļ��а�����ͼƬ��Ϣ�ŵ�vector��
	json->getAllImages(b2dImages);
	//ͨ��������ЩͼƬ��ϢΪ֮���쾫�飬���ҳ�ʼ����������
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


// Override this in subclasses to do some extra processing (eg. acquire references
// to named bodies, joints etc) after the world has been loaded, and while the b2dJson
// information is still available.
void BasicLoadLayer::afterLoadProcessing(b2dJson* json)
{
    
}

// This method should undo anything that was done by the loadWorld and afterLoadProcessing
// methods, and return to a state where loadWorld can safely be called again.
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

// Standard Cocos2d method, just step the physics world with fixed time step length
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
			//need to rotate image local center by body angle
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

//������Ӹ��ڵ����Ƴ���ͬʱҲ�Ƴ�ͼƬ��Ϣ
void BasicLoadLayer::removeImageFromWorld(ImageInfo* imgInfo)
{
	removeChild(imgInfo->sprite, true);
	m_imageInfos.erase(imgInfo);
}

//���������ȡ��Ӧ�ľ���
cocos2d::Sprite* BasicLoadLayer::getAnySpriteOnBody(b2Body* body)
{
	for each (auto imgInfo in m_imageInfos)
	{
		if (imgInfo->body == body)
			return imgInfo->sprite;
	}
	return nullptr;
}

//����ͼƬ���ֻ�ȡ��Ӧ�ľ���
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