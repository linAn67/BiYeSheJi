#ifndef __BasicLoadLayer_H__
#define __BasicLoadLayer_H__
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Box2DDebugDraw.h"

class b2dJson;

struct ImageInfo {

	cocos2d::Sprite* sprite;      // the image
	std::string name;               // the file the image was loaded from
	class b2Body* body;             // the body this image is attached to (can be NULL)
	float scale;                    // a scale of 1 means the image is 1 physics unit high
	float aspectScale;              // modify the natural aspect of the image
	float angle;                    // 'local angle' - relative to the angle of the body
	cocos2d::Point center;        // 'local center' - relative to the position of the body
	float opacity;                  // 0 - 1
	bool flip;                      // horizontal flip
	int colorTint[4];               // 0 - 255 RGBA values
};


class BasicLoadLayer : public cocos2d::Layer
{
protected:
    b2World* m_world;                       // the physics world
	std::set<ImageInfo*> m_imageInfos;		//储存加载的图片的信息，用于根据刚体的位置和角度的变动，改变图片的位置和角度
public:
    BasicLoadLayer();
    virtual ~BasicLoadLayer();
    
    static cocos2d::Scene* scene();                           // returns a Scene that contains the HelloWorld as the only child
    virtual bool init();                                        // virtual functions cannot be used in the constructor, but we want to allow some customization from subclasses
    CREATE_FUNC(BasicLoadLayer);
	
	virtual std::string getFilename();                          // override this in subclasses to specify which .json file to load
    virtual cocos2d::Point initialWorldOffset();              // override this in subclasses to set the inital view position
    virtual float initialWorldScale();                          // override this in subclasses to set the initial view scale
    
    virtual void loadWorld();                                   // attempts to load the world from the .json file given by getFilename
    virtual void afterLoadProcessing(b2dJson* json);            // override this in a subclass to do something else after loading the world (before discarding the JSON info)
    virtual void clear();                                       // undoes everything done by loadWorld and afterLoadProcessing, so that they can be safely called again

/*
    virtual b2Vec2 screenToWorld(cocos2d::Point screenPos);   // converts a position in screen pixels to a location in the physics world
    virtual cocos2d::Point worldToScreen(b2Vec2 worldPos);    // converts a location in the physics world to a position in screen pixels*/

	void loadImages(b2dJson* json);
	void setImagePositionsFromPhysicsBodies();
	void removeBodyFromWorld(b2Body* body);                 // removes a body and its images from the layer
	void removeImageFromWorld(ImageInfo* imgInfo);      // removes an image from the layer
	cocos2d::Sprite* getAnySpriteOnBody(b2Body* body);            // returns the first sprite found attached to the given body, or nil if there are none
	cocos2d::Sprite* getSpriteWithImageName(std::string name);    // returns the first sprite found with the give name (as named in the RUBE scene) or nil if there is none
	
	virtual void update(float dt);   
};

#endif


