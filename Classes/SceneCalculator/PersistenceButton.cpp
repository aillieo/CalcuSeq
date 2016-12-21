#include "PersistenceButton.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool PersistenceButton::init()
{

    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
	setTexture("ResourcesCalculator/persistenceButton.png");
	setColor(Color3B(197,197,197));
	//setTextureRect(Rect(0,0,400,100));

	_persistenceID = 0;

    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//对触摸事件的监听
	_touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(PersistenceButton::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(PersistenceButton::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(PersistenceButton::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(PersistenceButton::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setSwallowTouches(false);


	_ext = Sprite::create("ResourcesCalculator/persistenceButton_ext.png");
	addChild(_ext);
	_ext->setPosition((Vec2)getContentSize()/2 + Vec2(0,100));
	_ext->setOpacity(40);
	_ext->setColor(Color3B(197,197,197));


	_save = Sprite::create("ResourcesCalculator/persistenceButton_save.png");
	//_save->setTextureRect(Rect(0,0,100,100));
	addChild(_save);
	//_save->setColor(Color3B(255,0,0));
	_save->setPosition((Vec2)getContentSize()/2 + Vec2(-55,95));
	_save->setVisible(false);

	_load = Sprite::create("ResourcesCalculator/persistenceButton_load.png");
	//_load->setTextureRect(Rect(0,0,100,100));
	addChild(_load);
	//_load->setColor(Color3B(0,0,255));
	_load->setPosition((Vec2)getContentSize()/2 + Vec2(55,95));
	_load->setVisible(false);





    return true;
}

bool PersistenceButton::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{



	Point p = getParent()->convertToNodeSpace(touch->getLocation());


	if (getBoundingBox().containsPoint(p))
	{
		_save->setVisible(true);
		_load->setVisible(true);
		_ext->setOpacity(255);
		return true;
	}
	else
	{
		return false;
	}
	
	
	
}

void PersistenceButton::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	if (!_touchListener->isSwallowTouches())
	{
			_touchListener->setSwallowTouches(true);
	}

	
}

void PersistenceButton::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{


	Point p = convertToNodeSpace(touch->getLocation());
	_save->setVisible(false);
	_load->setVisible(false);
	_ext->setOpacity(40);

	if (_save->getBoundingBox().containsPoint(p))
	{
		_eventDispatcher->dispatchCustomEvent("SAVE_SCENE",&_persistenceID);

	}
	else if (_load->getBoundingBox().containsPoint(p))
	{
		_eventDispatcher->dispatchCustomEvent("LOAD_SCENE",&_persistenceID);

	}


	if (_touchListener->isSwallowTouches())
	{
		_touchListener->setSwallowTouches(false);
	}


}

void PersistenceButton::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}


void PersistenceButton::setPersistenceID(int pID)
{

	_persistenceID = pID;
	std::string s_id = String::createWithFormat("Seq.%d",_persistenceID + 1)->getCString();
	Label* label = Label::createWithSystemFont(s_id,"Arial",40);
	addChild(label);
	label->setPosition((Vec2)getContentSize()/2 + Vec2(0,0));
	label->enableShadow(Color4B(0,0,0,90),Size(2,-2),0);


	Color3B c3b = Color3B(255, 255, 255);
	switch(pID)
	{
	case 0:
		c3b = Color3B(255, 0, 0);
		break;
	case 1:
		c3b = Color3B(255, 165, 0);
		break;
	case 2:
		c3b = Color3B(255, 255, 0);
		break;
	case 3:
		c3b = Color3B(0, 255, 0);
		break;
	case 4:
		c3b = Color3B(0, 127, 255);
		break;
	case 5:
		c3b = Color3B(0, 0, 255);
		break;
	case 6:
		c3b = Color3B(139, 0, 255);
		break;
	default:
		break;

	}


	_save->setColor(c3b);
	_load->setColor(c3b);
	label->setColor(c3b);


}
