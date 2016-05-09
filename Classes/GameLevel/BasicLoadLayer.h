#ifndef __BasicLoadLayer_H__
#define __BasicLoadLayer_H__
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Box2DDebugDraw.h"

class b2dJson;

struct ImageInfo {
	cocos2d::Sprite* sprite;		   // 图片精灵
	std::string name;				   // 图片名
	class b2Body* body;				   // 图片链接的刚体
	float scale;					   // 以物理单元为单位的缩放大小
	float aspectScale;				  
	float angle;                    // 相对与刚体的角度
	cocos2d::Point center;        // 相对于刚体的图片中心位置
	float opacity;                  // 0 - 1
	bool flip;                      // 水平翻转
	int colorTint[4];               // 0 - 255 RGBA值
};


class BasicLoadLayer : public cocos2d::Layer
{
protected:
    b2World* m_world;                       // the physics world
	std::set<ImageInfo*> m_imageInfos;		//储存加载的图片的信息，用于根据刚体的位置和角度的变动，改变图片的位置和角度
public:
    BasicLoadLayer();
    virtual ~BasicLoadLayer();
    
    static cocos2d::Scene* scene();                          
    virtual bool init();                                      
    CREATE_FUNC(BasicLoadLayer);
	
	virtual std::string getFilename();                        
    virtual cocos2d::Point initialWorldOffset();            
    virtual float initialWorldScale();                         
    
    virtual void loadWorld();                                 
    virtual void afterLoadProcessing(b2dJson* json);           
    virtual void clear();                                     

	void loadImages(b2dJson* json);
	void setImagePositionsFromPhysicsBodies();
	void removeBodyFromWorld(b2Body* body);               
	void removeImageFromWorld(ImageInfo* imgInfo);     
	cocos2d::Sprite* getAnySpriteOnBody(b2Body* body);           
	cocos2d::Sprite* getSpriteWithImageName(std::string name);    
	
	virtual void update(float dt);   
};

#endif


