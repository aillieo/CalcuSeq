#include "LayerScroll.h"



USING_NS_CC;

const float elastic_factor = 40.0f;



// on "init" you need to initialize your instance
bool LayerScroll::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



	_limitBottom = 0;
	_limitUpper = 0;

	_scrollUpdating = false;


	auto _touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(LayerScroll::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(LayerScroll::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(LayerScroll::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(LayerScroll::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setSwallowTouches(true);

	_velocityY = 0;
	_resistanceY = 0.9f;
	_elasticY = 1.0;


    return true;
}



bool LayerScroll::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused_event )
{
	if (_scrollUpdating)
	{
		unschedule(schedule_selector(LayerScroll::_update));
		_scrollUpdating = false;
	}
	

	_velocityY = 0;
	_elasticY = 1.0f;
	return true;
}

void LayerScroll::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused_event )
{

	_velocityY =   touch->getLocation().y - touch->getPreviousLocation().y;



	performElasticOnMoving();
	
	setPositionY(getPositionY() + _velocityY);
	//log("move v = %f",_velocityY);

}

void LayerScroll::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused_event )
{

	if (_velocityY > 100)
	{
		_velocityY = 100;
	}
	else if (_velocityY < -100)
	{
		_velocityY = -100;
	}
	
	

	performElasticOnReleased();

	
	if (!_scrollUpdating)
	{

		schedule(schedule_selector(LayerScroll::_update));
		_scrollUpdating = true;
	}


}

void LayerScroll::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused_event )
{
	
}

void LayerScroll::updateLimitUpper()
{
	
	
}

void LayerScroll::_update(float delta)
{
	

	performFriction();
	
	performElasticOnMoving();


	if (fabs(_velocityY)< _resistanceY * 1.1)
	{
		if ((getPositionY()<= _limitBottom - 1)||((getPositionY()>= _limitUpper + 1)))
		{
			performElasticOnReleased();
		}
		else
		{
			unschedule(schedule_selector(LayerScroll::_update));
			_scrollUpdating = false;
		}
		
	}


	setPositionY(getPositionY() + _velocityY );
	//log("update v = %f",_velocityY);
}


void LayerScroll::performFriction()
{

	if(_velocityY>0)
	{
		_velocityY -= _resistanceY;
	}
	else
	{
		_velocityY += _resistanceY;
	}
	
	if(fabs(_velocityY)< _resistanceY * 1.1)
	{
		_velocityY = 0;
	}
}


void LayerScroll::performElasticOnMoving()
{

	if ((getPositionY()<= _limitBottom)&&_velocityY<0)
	{
		_elasticY = elastic_factor / (_limitBottom - getPositionY() + elastic_factor);
		_velocityY = _velocityY*_elasticY;

	}
	else if ((getPositionY()>= _limitUpper)&&_velocityY>0)
	{
		_elasticY =  elastic_factor  / (getPositionY() - _limitUpper + elastic_factor ) ;
		_velocityY = _velocityY*_elasticY;
	}
	else
	{
		_elasticY = 1;
	}


}

void LayerScroll::performElasticOnReleased()
{
	if (getPositionY()<= _limitBottom)
	{
		scrollTo( _limitBottom );

	}
	else if (getPositionY()>= _limitUpper)
	{	
		scrollTo( _limitUpper );

	}
}

void LayerScroll::scrollTo( float posY )
{

	if (!_scrollUpdating)
	{
		schedule(schedule_selector(LayerScroll::_update));
		_scrollUpdating = true;
	}

	float dis = posY - getPositionY();
	float v_mag = sqrt(fabs(dis) * 2.0 * _resistanceY);
	if (dis>0)
	{
		_velocityY = v_mag;
	}
	else if (dis<0)
	{
		_velocityY =  (-1 )*v_mag;
	}
	
	_elasticY = 1.0f;
}
