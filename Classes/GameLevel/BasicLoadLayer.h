#ifndef __BasicLoadLayer_H__
#define __BasicLoadLayer_H__
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Box2DDebugDraw.h"

class b2dJson;

struct ImageInfo {
	cocos2d::Sprite* sprite;		   // ͼƬ����
	std::string name;				   // ͼƬ��
	class b2Body* body;				   // ͼƬ���ӵĸ���
	float scale;					   // ������ԪΪ��λ�����Ŵ�С
	float aspectScale;				  
	float angle;                    // ��������ĽǶ�
	cocos2d::Point center;        // ����ڸ����ͼƬ����λ��
	float opacity;                  // 0 - 1
	bool flip;                      // ˮƽ��ת
	int colorTint[4];               // 0 - 255 RGBAֵ
};


class BasicLoadLayer : public cocos2d::Layer
{
protected:
    b2World* m_world;                       // the physics world
	std::set<ImageInfo*> m_imageInfos;		//������ص�ͼƬ����Ϣ�����ڸ��ݸ����λ�úͽǶȵı䶯���ı�ͼƬ��λ�úͽǶ�
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


