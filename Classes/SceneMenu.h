#pragma  once

#include "cocos2d.h"

class SceneMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  


    // implement the "static create()" method manually
    CREATE_FUNC(SceneMenu);

private:

	cocos2d::Vector<cocos2d::MenuItem*> _items;

	void itemReplaceSceneCallback(cocos2d::Ref* pSender , int itemId);

};


