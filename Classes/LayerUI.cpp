#include "LayerUI.h"
#include "SceneMenu.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerUI::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

/*
	MenuItemImage* itemQuit = MenuItemImage::create("BUTTON_.png","BUTTON_.png",CC_CALLBACK_1(LayerUI::menuQuitCallback,this));
	Menu* menu = Menu::create(itemQuit,NULL);
	addChild(menu);
	menu->setLocalZOrder(10086);
	menu->setPosition(0,0);
	itemQuit->setPosition(itemQuit->getContentSize().width/2, visibleSize.height - itemQuit->getContentSize().height/2);


	itemQuit->setVisible(false);

*/
    return true;
}

void LayerUI::menuQuitCallback( cocos2d::Ref* pSender )
{
	//Director::getInstance()->replaceScene(SceneMenu::createScene());
}
