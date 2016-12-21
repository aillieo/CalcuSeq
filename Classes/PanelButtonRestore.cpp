#include "PanelButtonRestore.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelButtonRestore::init()
{
	 
	// 1. super init first
	if ( !PanelButtonStore::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("BUTTON180.png");
	setColor(Color3B(80,125,80));

	_icon->setTexture("buttons/button_restore.png");
    //_icon->setColor(Color3B(200,0,180));
	_icon->setPosition(getContentSize()/2);
	_icon->setOpacity(60);
	



	return true;
}



void PanelButtonRestore::onPressed()
{
	//通知正在输入的text从userdefault中读取值

	_eventDispatcher->dispatchCustomEvent("RESTORE_VALUE",&_storageIndex);

}
