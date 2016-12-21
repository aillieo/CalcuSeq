#include "Text.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool Text::init()
{
     
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_equationID = 0;
	_text = " ";

	_labelText = Label::create(_text,"font/Simplifica.ttf",50) ;
	addChild(_labelText);
	_labelText->setPosition(0,0);
	_labelText->setHorizontalAlignment(TextHAlignment::CENTER);
	_labelText->setColor(Color3B(0,0,0));


	//对输入的监听
	_listenerInput = EventListenerCustom ::create("INPUT",CC_CALLBACK_1(Text::onEventInput,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerInput,this);
	_listenerInput->setEnabled(false);

    
    return true;
}


void Text::enableInput( bool input )
{
	_listenerInput->setEnabled(input);

/*
	if(input)
	{
		auto fi = FadeIn::create(0.2);
		auto fo = FadeOut::create(0.2);
		auto seq = Sequence::create(fi,fo,NULL);
		auto rpt = RepeatForever::create(seq);
		_labelText->runAction(rpt);
	}
	else
	{
		_labelText->stopAllActions();
		_labelText->setOpacity(255);
	}

	*/
}


void Text::onEventInput( cocos2d::EventCustom* event )
{
	PanelButtonType *pbt = (PanelButtonType *)(event->getUserData());
	processInput(*pbt);

}

void Text::processInput( PanelButtonType panelButtonType )
{

}


void Text::setTextColor(cocos2d::Color3B c3b)
{
    _labelText->setColor(c3b);

}


/*
cocos2d::EventListenerCustom* Text::getInputListener()
{
	return _listenerInput;
}
*/



void Text::endInputting()
{
}




void Text::setEquationID( unsigned equationID )
{
	_equationID = equationID;
}

std::string Text::getTextString()
{
	return _text;
}


