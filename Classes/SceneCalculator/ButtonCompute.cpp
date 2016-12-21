#include "ButtonCompute.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool ButtonCompute::init()
{
	 
	// 1. super init first
	if ( !Sprite::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("ResourcesCalculator/itemCompute.png");
	setColor(Color3B(127,127,127));
	
	Label* label = Label::create("=","font/Simplifica.ttf",80);
	addChild(label);
	label->setPosition((Vec2)getContentSize()/2 + Vec2(2,-5));
	label->setColor(Color3B::BLACK);



	_touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(ButtonCompute::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(ButtonCompute::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(ButtonCompute::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(ButtonCompute::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);



	return true;
}

void ButtonCompute::onPressed()
{

	_eventDispatcher->dispatchCustomEvent("COMPUTE",getParent());



}




bool ButtonCompute::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	_touchManager.reset();

	Point p = getParent()->convertToNodeSpace(touch->getLocation());

	if (getBoundingBox().containsPoint(p))
	{
        //_touchListener->setSwallowTouches(true);
		_touchManager.containsTouchingPoint = true;
		//scheduleUpdate();
		return true;
	}

	return false;
}
 
void ButtonCompute::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{
    if(!_touchManager.hasMoved)
    {
        _touchManager.hasMoved = true;
    }
}

void ButtonCompute::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{



	
	Point p = getParent()->convertToNodeSpace(touch->getLocation());
	if (!_touchManager.hasMoved&&_touchManager.containsTouchingPoint)
	{

		onPressed();
		
	}

    if (_touchListener->isSwallowTouches())
    {
            _touchListener->setSwallowTouches(false);
    }

}
 
void ButtonCompute::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	
}

