#include "PanelButtonStore.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelButtonStore::init()
{
	 
	// 1. super init first
	if ( !PanelButton::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//setTexture("BLANK.png");
	setColor(Color3B(255,0,0));
	//setTextureRect(Rect(0,0,88,88));
	_icon->setTexture("buttons/button_store.png");
	_icon->setVisible(true);
	
	_storageIndex = 0;

	_label->setVisible(false);
	

	return true;
}






void PanelButtonStore::onPressed()
{
	//通知正在输入的text把value存入userdefault
	//通知module的text改变为userdefault的值

	_eventDispatcher->dispatchCustomEvent("STORE_VALUE",&_storageIndex);

	std::string eveName = "UPDATE_STORE_VALUE_";
	eveName = eveName + String::createWithFormat("%d",_storageIndex)->_string;
	_eventDispatcher->dispatchCustomEvent(eveName);


	
}


void PanelButtonStore::setStorageIndex(int index)
{
	_storageIndex = index;
}