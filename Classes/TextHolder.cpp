#include "TextHolder.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool TextHolder::init()
{
     
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("textHolder.png");
	//setTextureRect(Rect(0,0,60,60));
	setColor(Color3B(110,160,120));

	setOpacity(100);

	_text = nullptr;



	_touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(TextHolder::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(TextHolder::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(TextHolder::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(TextHolder::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setSwallowTouches(false);


	auto _listener = EventListenerCustom ::create("RESET_HOLDER",CC_CALLBACK_1(TextHolder::resetInputState,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,this);

    
    return true;
}



bool TextHolder::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
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

void TextHolder::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{
    if(!_touchManager.hasMoved)
    {
        _touchManager.hasMoved = true;
    }
}

void TextHolder::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	Point p = getParent()->convertToNodeSpace(touch->getLocation());
	if (!_touchManager.hasMoved&&_touchManager.containsTouchingPoint)
	{

		checkPanelTypeToShow(true);
		
	}
    if (_touchListener->isSwallowTouches())
    {
            _touchListener->setSwallowTouches(false);
    }


}

void TextHolder::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	
}


void TextHolder::enableInput( bool input )
{
	_inputting = input;
	_text->enableInput(_inputting );
	if (input)
	{
		setColor(Color3B(255,255,255));
		setOpacity(255);
	}



}



void TextHolder::checkPanelTypeToShow(bool show)
{
	if (holderType == HolderType::NOT_INPUT)
	{
		return;
	}

	if (holderType == HolderType::OPERAND)
	{
		_eventDispatcher->dispatchCustomEvent("SHOW_PANEL_INPUT_OPERAND",&show);
		enableInput(true);
		return;
	}
	
	int tmp = 0;
	if (show)
	{
		tmp = ((holderType == HolderType::OPERATOR_BINARY)?2:1);
	}
	_eventDispatcher->dispatchCustomEvent("SHOW_PANEL_INPUT_OPERATOR",&tmp);
	enableInput(true);
	
}

void TextHolder::initText(Text *text)
{
	if (_text!=nullptr)
	{
		return;
	}
	_text = text;
	addChild(_text);
	_text->setPosition((Vec2)getContentSize()/2 + Vec2(0,-5));
}

Text* TextHolder::getText()
{
	return _text;
}

void TextHolder::resetInputState( cocos2d::EventCustom* event )
{
	_inputting = false;
	setColor(Color3B(110,160,120));
	setOpacity(100);

}




