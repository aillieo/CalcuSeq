#include "PanelInput.h"
#include "PanelButton.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PanelInput::init()
{
     
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    

	setTexture("BLANK.png");
	setColor(Color3B(200,150,200));
	setTextureRect(Rect(0,0,720,90));



	auto _touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(PanelInput::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(PanelInput::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(PanelInput::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(PanelInput::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setSwallowTouches(true);




    return true;
}

void PanelInput::initButtons()
{

}

bool PanelInput::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	if (!isVisible())
	{
		return false;
	}

	Point p = getParent()->convertToNodeSpace(touch->getLocation());

	if (!getBoundingBox().containsPoint(p))
	{
		PanelButtonType pbt = PanelButtonType::BUTTON_G_CLOSE;
		_eventDispatcher->dispatchCustomEvent("INPUT",&pbt);
		//return true;
        return false;
	}


	bool found = false;

	for (PanelButton* pb : _buttons)
	{
		pb->getTouchManager().reset();
		p = pb->getParent()->convertToNodeSpace(touch->getLocation());
		if (!found)
		{
			if (pb->getBoundingBox().containsPoint(p)&&pb->isVisible()&&pb->getParent()->isVisible())
			{
				pb->getTouchManager().containsTouchingPoint = true;
				found = true;
			}
		}

	}
	


	return true;
}


void PanelInput::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}



void PanelInput::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{


	Point p;

	for (PanelButton* pb : _buttons)
	{
		p = pb->getParent()->convertToNodeSpace(touch->getLocation());
		if (pb->getTouchManager().containsTouchingPoint && pb->getBoundingBox().containsPoint(p))
		{
			pb->onPressed();
			return;
		}

	}
}



void PanelInput::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

