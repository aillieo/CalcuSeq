#pragma  once

#include "cocos2d.h"


class LayerUI : public cocos2d::Layer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(LayerUI);



protected:


	//主菜单相关
	virtual void menuQuitCallback(cocos2d::Ref* pSender);


};


