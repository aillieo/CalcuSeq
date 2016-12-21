#include "EquationBuilder.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool EquationBuilder::init()
{
     
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
	setTexture("ResourcesCalculator/builder.png");
	//setTextureRect(Rect(0,0,400,100));

	_posInLayer = Point(0,0);

    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//对触摸事件的监听
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(EquationBuilder::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(EquationBuilder::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(EquationBuilder::onTouchEnded,this);
	touchListener->onTouchCancelled=CC_CALLBACK_2(EquationBuilder::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
	touchListener->setSwallowTouches(true);


	_left = Sprite::create("ResourcesCalculator/builder_left.png");
	//_left->setTextureRect(Rect(0,0,100,100));
	addChild(_left);
	//_left->setColor(Color3B(255,0,0));
	_left->setPosition((Vec2)getContentSize()/2 - Vec2(132.5,0));
	_left->setVisible(false);

	_right = Sprite::create("ResourcesCalculator/builder_right.png");
	//_right->setTextureRect(Rect(0,0,100,100));
	addChild(_right);
	//_right->setColor(Color3B(0,0,255));
	_right->setPosition((Vec2)getContentSize()/2 + Vec2(132.5,0));
	_right->setVisible(false);


    return true;
}

bool EquationBuilder::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (!isVisible())
	{
		return false;
	}
	

	Point p = getParent()->convertToNodeSpace(touch->getLocation());

	if (getBoundingBox().containsPoint(p))
	{
        setOpacity(20);
		_left->setVisible(true);
		_right->setVisible(true);
		return true;
	}
	else
	{
		return false;
	}
	
	
	
}

void EquationBuilder::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void EquationBuilder::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	Point p = getParent()->convertToNodeSpace(touch->getLocation());
	int operands = 0;
	_left->setVisible(false);
	_right->setVisible(false);
    setOpacity(255);

/*
	if (_left->getBoundingBox().containsPoint(p))
	{
		operands = 1;
	}
	else if (_right->getBoundingBox().containsPoint(p))
	{
		operands = 2;
	}
	else
	{
		return;
	}

    
*/
    float halfHeight = getContentSize().height/2;
    if ((p.y<getPositionY() - halfHeight )||(p.y> getPositionY() + halfHeight ))
    {
        return;
    }
    
    if (p.x < getPositionX())
    {
        operands = 1;
    }
    else
    {
        operands = 2;
    }


	_eventDispatcher->dispatchCustomEvent("ADD_EQUATION", &operands);
	


}

void EquationBuilder::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void EquationBuilder::setPosInLayer( cocos2d::Point posInLayer )
{
	_posInLayer = posInLayer;
}

void EquationBuilder::updatePosition()
{
	stopAllActions();
	MoveTo* mt = MoveTo::create(0.2f,_posInLayer);
	runAction(mt);
}








