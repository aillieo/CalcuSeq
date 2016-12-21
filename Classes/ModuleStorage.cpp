#include "ModuleStorage.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool ModuleStorage::init()
{
	 
	// 1. super init first
	if ( !Node::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_panelButtonStore = nullptr;
	_panelButtonStore = nullptr;
	_textOperand = nullptr;

	_storageIndex = 0;


	

	return true;
}


void ModuleStorage::initComponents(PanelButtonStore* panelButtonStore , PanelButtonRestore* panelButtonRestore )
{


	_panelButtonStore = panelButtonStore;
	_panelButtonRestore = panelButtonRestore;
	_textOperand = TextOperand::create();

	addChild(_panelButtonStore);

	_panelButtonRestore->setPosition(45,0);
	addChild(_panelButtonRestore);

	_panelButtonStore->setPosition(180,0);
	addChild(_textOperand);

	_textOperand->setPosition(_panelButtonRestore->getPosition() + Vec2(0,-5));
	_textOperand-> setTextColor(Color3B(255,255,255));


}




void ModuleStorage::setStorageIndex(int index )
{
	_storageIndex = index;
	_panelButtonStore->setStorageIndex(_storageIndex );
	_panelButtonRestore->setStorageIndex(_storageIndex );

	std::string eveName = "UPDATE_STORE_VALUE_";
	eveName = eveName + String::createWithFormat("%d",_storageIndex)->_string;
	auto updateStoreValueListener = EventListenerCustom ::create(eveName,CC_CALLBACK_1(ModuleStorage::updateStoreValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(updateStoreValueListener,this);

	_updateStoreValue();


}


void ModuleStorage::updateStoreValue(cocos2d::EventCustom* event)
{
	_updateStoreValue();

}


void ModuleStorage::_updateStoreValue()
{

	std::string key = "store_value_";
	key = key + String::createWithFormat("%d",_storageIndex)->_string;
	double d = UserDefault::getInstance()->getDoubleForKey(key.c_str(),0);
	_textOperand->setValue(d,true);
	//// 数值  颜色  x传递


}