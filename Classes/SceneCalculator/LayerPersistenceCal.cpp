#include "LayerPersistenceCal.h"
#include "PersistenceButton.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerPersistenceCal::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_bg  = Sprite::create("BLANK.png");
	addChild(_bg);
	_bg->setPosition(visibleSize.width*(-0.5),visibleSize.height/2);
	_bg->setTextureRect(Rect(0,0,visibleSize.width,visibleSize.height));
	_bg->setColor(Color3B(0,0,0));
	_bg->setOpacity(180);





	for(int i = 0; i< 7 ; i++)
	{
		PersistenceButton* persistenceButton = PersistenceButton::create();
		_bg->addChild(persistenceButton);
		//persistenceButton ->setPositionX(190 + (i%2) * 340 );
		//persistenceButton->setPositionY(1000 - (i/2) * 400 );
		persistenceButton -> setPosition((Vec2)(_bg->getContentSize()/2) + Vec2( -160 + (i%2) * 320 , 200 - (i/2) * 240));
		persistenceButton -> setPersistenceID(i);
	}


	_label = Label::createWithSystemFont(" ","Arial",50);
	_bg->addChild(_label);
	_label->setPosition(visibleSize.width/2,visibleSize.height/2 + 400);
	_label->setOpacity(0);



	_shown = false;
	_updating = false;



	auto _touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(LayerPersistenceCal::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(LayerPersistenceCal::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(LayerPersistenceCal::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(LayerPersistenceCal::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setSwallowTouches(true);


	auto saveResponseListener = EventListenerCustom ::create("SAVE_SUCCESS",CC_CALLBACK_1(LayerPersistenceCal::onSaveSucceed,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(saveResponseListener,this);
	auto loadResponseListener = EventListenerCustom ::create("LOAD_SUCCESS",CC_CALLBACK_1(LayerPersistenceCal::onLoadSucceed,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(loadResponseListener,this);



    return true;
}

bool LayerPersistenceCal::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	bool bRet = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point p = _bg->getParent()->convertToNodeSpace(touch->getLocation());

	if ((_shown)&&(_bg->getBoundingBox().containsPoint(p)))
	{
		bRet = true;
	}
	else if((!_shown)&&(fabs(_bg->getPositionX() + visibleSize.width/2 -p.x)<=50)&&(fabs(visibleSize.height/2 -p.y)<=200))
	{
		bRet = true;
	}


	if (_updating&&bRet)
	{
		unscheduleUpdate();
	}


	return bRet;

}

void LayerPersistenceCal::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{


	Size visibleSize = Director::getInstance()->getVisibleSize();

	_bg->setPositionX(_bg->getPositionX() + touch->getLocation().x - touch->getPreviousLocation().x);
	if (_bg->getPositionX()>visibleSize.width/2)
	{
		_bg->setPositionX(visibleSize.width/2);
	}
	else if (_bg->getPositionX()< -1 *(visibleSize.width/2))
	{
		_bg->setPositionX( -1 *(visibleSize.width/2));
	}

}

void LayerPersistenceCal::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	_shown = _bg->getPositionX()>0;
	_updating = true;
	scheduleUpdate();

}

void LayerPersistenceCal::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void LayerPersistenceCal::update( float delta )
{
		Size visibleSize = Director::getInstance()->getVisibleSize();
	if (_shown)
	{
		_bg->setPositionX(_bg->getPositionX() + 800*delta);
		if (_bg->getPositionX()>visibleSize.width/2)
		{
			_bg->setPositionX(visibleSize.width/2);
			unscheduleUpdate();
			_updating = false;
		}
	}
	else
	{
		_bg->setPositionX(_bg->getPositionX()- 800*delta);
		if (_bg->getPositionX()< -1 *(visibleSize.width/2))
		{
			_bg->setPositionX( -1 *(visibleSize.width/2));
			unscheduleUpdate();
			_updating = false;
		}
	}


}



void LayerPersistenceCal::onSaveSucceed(cocos2d::EventCustom* event)
{
	_label->setString("Successfully saved");
	_label->setOpacity(255);
	_label->stopAllActions();
	FadeOut* fo = FadeOut::create(1.2f);
	_label->runAction(fo);

}

void LayerPersistenceCal::onLoadSucceed( cocos2d::EventCustom* event )
{

	_label->setString("Successfully loaded");
	_label->setOpacity(255);
	_label->stopAllActions();
	FadeOut* fo = FadeOut::create(1.2f);
	_label->runAction(fo);
}



