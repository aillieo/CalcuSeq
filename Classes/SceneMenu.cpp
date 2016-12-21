#include "SceneMenu.h"
#include "SceneCalculator/SceneCalculator.h"
#include "SceneToolkit/SceneToolkit.h"

USING_NS_CC;

Scene* SceneMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SceneMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneMenu::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0 ; i < 6 ; i++)
	{
		MenuItem* mii = MenuItemImage::create("button_menu.png","button_menu.png",
			
			//CC_CALLBACK_1(itemReplaceSceneCallback,this,i));
			std::bind(&SceneMenu::itemReplaceSceneCallback,this,std::placeholders::_1,i));
		
		mii ->setPositionX(190 + (i%2) * 340 );
		mii->setPositionY(1000 - (i/2) * 400 );
		_items.pushBack(mii);

	}
	Menu* menu = Menu::createWithArray(_items);
	addChild(menu);
	menu->setPosition(0,0);
    

    return true;
}



void SceneMenu::itemReplaceSceneCallback( cocos2d::Ref* pSender , int itemId )
{

	switch (itemId)
	{
	case 0:
		log("Glossary");
		break;
	case 1:
		log("Physics");
		break;
	case 2:
		log("Calculator");
		Director::getInstance()->replaceScene(SceneCalculator::createScene());
		break;
	case 3:
		log("Conversion");
		break;
	case 4:
		log("Toolkit");
		Director::getInstance()->replaceScene(SceneToolkit::createScene());
		break;
	case 5:
		log("About");
		break;
	default:
		break;
	}
}






