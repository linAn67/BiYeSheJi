#include "WidgeCallBackHandle.h" 
#include "ui/UIText.h" 
USING_NS_CC; 
using namespace std; 
using namespace cocos2d::ui; 
WidgeCallBackHandle::WidgeCallBackHandle() 
{} 
Widget::ccWidgetTouchCallback WidgeCallBackHandle::onLocateTouchCallback(const string &callBackName) 
{ 
    if (callBackName == "onTouch")//判断事件名，返回对应的函数。下同 
    { 
        return CC_CALLBACK_2(WidgeCallBackHandle::onTouch, this); 
    } 
    return nullptr; 
} 
Widget::ccWidgetClickCallback WidgeCallBackHandle::onLocateClickCallback(const string &callBackName) 
{ 
    if (callBackName == "onClick") 
    { 
        return CC_CALLBACK_1(WidgeCallBackHandle::onClick, this); 
    } 
    return nullptr; 
} 
Widget::ccWidgetEventCallback WidgeCallBackHandle::onLocateEventCallback(const string &callBackName) 
{ 
    if (callBackName == "onEvent") 
    { 
        return CC_CALLBACK_2(WidgeCallBackHandle::onEvent, this); 
    } 
    return nullptr; 
} 
void WidgeCallBackHandle::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type) 
{ 
    CCLOG("onTouch"); 
} 
void WidgeCallBackHandle::onClick(cocos2d::Ref* sender) 
{ 
    CCLOG("onClick"); 
} 
void WidgeCallBackHandle::onEvent(cocos2d::Ref* sender, int eventType) 
{ 
    CCLOG("onEvent"); 
} 
