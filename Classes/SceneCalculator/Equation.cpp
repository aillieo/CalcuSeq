#include "Equation.h"
#include "TextHolderWithLinking.h"
#include "LinkingNodeResult.h"
#include "ButtonCompute.h"


//const float init_builder_posY = 1000;

const int move_action_tag = 181;

USING_NS_CC;



// on "init" you need to initialize your instance
bool Equation::init()
{
     
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
	_equationID = 0;

	_posInLayer = Point(0,0);

	_computed =false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	setTexture("BLANK.png");
	setTextureRect(Rect(0,0,700,60));
	
	_bg1 = Sprite::create("ResourcesCalculator/equation_fore.png");
	//_bg1->setTextureRect(Rect(0,0,700,100));
	addChild(_bg1,-1);
	_bg1->setPosition(getContentSize()/2);
	//_bg1->setGlobalZOrder(-1);

	_bg2 = Sprite::create("ResourcesCalculator/equation_bg.png");
	addChild(_bg2,-2);
	_bg2->setPosition(getContentSize()/2);
	//_bg2->setColor(getRandomColor());
	//_bg2->setGlobalZOrder(-2);


	Sprite* cover = Sprite::create("ResourcesCalculator/equation_cover.png");
	addChild(cover);
	cover->setPosition(getContentSize()/2);

    
	_textHolderResult = TextHolderWithLinking::create();
	addChild(_textHolderResult);
	_textHolderResult->setPosition((Vec2)getContentSize()/2 + Vec2(270,0));
	_textResult = TextOperandWithLinking::create();
	_textHolderResult->initText(_textResult);
	_textHolderResult->holderType = TextHolderWithLinking::HolderType::NOT_INPUT;
	LinkingNodeResult* linkingNodeResult = LinkingNodeResult::create();
	_textHolderResult->initLinkingNode(linkingNodeResult);



/*
	MenuItemImage* itemCompute = MenuItemImage::create("ResourcesCalculator/itemCompute.png","ResourcesCalculator/itemCompute.png",CC_CALLBACK_1(Equation::compute,this));
	Menu* menu = Menu::create(itemCompute,NULL);
	addChild(menu);
	menu->setPosition(0,0);
	itemCompute->setPosition((Vec2)getContentSize()/2 + Vec2(135,0));
	itemCompute->setColor(Color3B(150,225,150));
*/

	_buttonCompute = ButtonCompute::create();
	addChild(_buttonCompute);
	_buttonCompute->setPosition((Vec2)getContentSize()/2 + Vec2(135,0));
	_buttonCompute->setColor(Color3B(150,225,150));


	_panelEdit = PanelEdit::create();
	addChild(_panelEdit);
	_panelEdit->setPosition((Vec2)getContentSize()/2 + Vec2(0,68));


	auto outOfDateListener = EventListenerCustom ::create("SET_EQUATION_OUT_OF_DATE",CC_CALLBACK_1(Equation::setEquationOutOfDate,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(outOfDateListener,this);


	auto computeListener = EventListenerCustom ::create("COMPUTE",CC_CALLBACK_1(Equation::compute,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(computeListener,this);

    _touchListener=EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan=CC_CALLBACK_2(Equation::onTouchBegan,this);
    _touchListener->onTouchMoved=CC_CALLBACK_2(Equation::onTouchMoved,this);
    _touchListener->onTouchEnded=CC_CALLBACK_2(Equation::onTouchEnded,this);
    _touchListener->onTouchCancelled=CC_CALLBACK_2(Equation::onTouchCancelled,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	//_touchListener->setSwallowTouches(true);


	setOpacity(0);

	Equation::_setEquationOutOfDate();


	//_posInSeq = EquationPosInSeq::BOTTOM;

    _willLeadToDynamicSort = false;
    
    _moveWithPanelEdit = false;
    
    _inDynamicSorting   = false;

    return true;
}

unsigned Equation::getEquationID()
{
	return _equationID;

}

void Equation::setEquationID( unsigned equationID )
{
	_equationID = equationID;
	//_textHolderResult->passEquationID(equationID);

	//std::string eveName = "SET_EQUATION_OUT_OF_DATE_";
	//eveName = eveName + String::createWithFormat("%d",_equationID)->_string;
	//auto updateStoreValueListener = EventListenerCustom ::create(eveName,CC_CALLBACK_1(Equation::setEquationOutOfDate,this));



}


void Equation::compute(cocos2d::EventCustom* event)
//void Equation::compute( cocos2d::Ref* pSender )
{

	if (this!= event->getUserData())
	{
		return;
	}
	
	_compute();

}

void Equation::_compute()
{
	_computed = true;
	Color3B c3b1 = Color3B(150,225,150);
	setColor(c3b1);
	_bg1->setColor(c3b1);
	//Color3B c3b2 = Color3B(180,255,190);
	//_textHolderResult->setColor(c3b2);
}



void Equation::onLongPressed()
{

	//_panelEdit->showItems();
    if(_willLeadToDynamicSort )
    {
        _inDynamicSorting = true;
        _touchListener -> setSwallowTouches(true);
        _eventDispatcher->dispatchCustomEvent("DYNAMIC_SORT",this);
    }
    
}


bool Equation::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

    
	//Point p = getParent()->convertToNodeSpace(touch->getLocation());
 
	//if (getBoundingBox().containsPoint(p))
	{

        _touchManager.reset();
        
        if(_moveWithPanelEdit)
        {
            _moveWithPanelEdit = false;
            return false;
        }

        
		_touchManager.containsTouchingPoint = true;
		scheduleUpdate();
		return true;
	}
	
	return false;
}
 
void Equation::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{


    
    
	if(!_touchManager.hasMoved)
    {
        _touchManager.hasMoved = true;
    }
    
    if (_touchManager.hasMoved)
    {
        if ((touch->getLocation().x - touch->getStartLocation().x < -100)&&(!_moveWithPanelEdit)&&(!_touchManager.isLongPressing)&&(_bg2->getBoundingBox().containsPoint(convertToNodeSpace(touch->getLocation()))))
        {
            _moveWithPanelEdit = true;
            bool autoUpdate = true;
            _eventDispatcher->dispatchCustomEvent("AUTO_UPDATE_LINKAGE_POSITION",&autoUpdate);
            _eventDispatcher->dispatchCustomEvent("SCROLL_LOCK");

        }
    }

	if (_touchManager.timer >= 0)
	{
		unscheduleUpdate(); 
		_touchManager.timer = -1;
	}

    if (_inDynamicSorting)
    {
        setPositionY(getPositionY() + touch->getLocation().y - touch->getPreviousLocation().y);
    }
    
    if (_moveWithPanelEdit)
    {
        setPositionX(getPositionX() + touch->getLocation().x - touch->getPreviousLocation().x);
        
        if(getPositionX()>_posInLayer.x)
        {
            setPositionX(_posInLayer.x);
        }
        //else if (getPositionX() < _posInLayer.x - 600)
        //{
        //    setPositionX(_posInLayer.x - 600);
            
        //}
        

    }
    
}

void Equation::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	unscheduleUpdate();
    

    _willLeadToDynamicSort = false;
    
    if (_moveWithPanelEdit)
    {
        
        if (getPositionX() < _posInLayer.x - 450)
        {
            _eventDispatcher->dispatchCustomEvent("REMOVE_EQUATION",this);

        }
        else
        {
            updatePosition();
            _moveWithPanelEdit = false;
        }
        


        
    }
    

	if ((!_touchManager.isLongPressing)&&(!_touchManager.hasMoved))
	{
		_panelEdit->hideItems();
	}
	
    
    if (_inDynamicSorting)
    {
        _inDynamicSorting = false;
        _touchListener -> setSwallowTouches(false);
        _eventDispatcher->dispatchCustomEvent("DYNAMIC_SORT",this);
    }
    else
    {
        bool autoUpdate = false;
        _eventDispatcher->dispatchCustomEvent("AUTO_UPDATE_LINKAGE_POSITION",&autoUpdate);

    }
	

/*
	if (_touchManager.isLongPressing)
	{
		return;
	}
	
	Point p = getParent()->convertToNodeSpace(touch->getLocation());
	if (getBoundingBox().containsPoint(p)&&_touchManager.containsTouchingPoint)
	{
		return;
	}
	
*/

}
 
void Equation::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	
}
 

void Equation::update(float delta)
{
    _touchManager.timer += delta;
	if (_touchManager.timer >= 0.55)
	{
		unscheduleUpdate();
		_touchManager.isLongPressing = true;
		onLongPressed();
	}
	
}

void Equation::onRemove()
{
	//删除无用的linkage



}

void Equation::setEquationOutOfDate( cocos2d::EventCustom* event )
{
	if (this!= event->getUserData())
	{
		return;
	}
	_setEquationOutOfDate();
}

void Equation::_setEquationOutOfDate()
{
	_computed = false;
	Color3B c3b1 = Color3B(100,100,100);
	setColor(c3b1);
	_bg1->setColor(c3b1);
	//Color3B c3b2 = Color3B(120,120,120);
	//_textHolderResult->setColor(c3b2);
}

void Equation::setPosInLayer(cocos2d::Point pos)
{
	_posInLayer = pos;
}





Equation* Equation::createWithString( const std::string& eq_string)
{
	return Equation::create();
}

void Equation::updateHolderColor()
{

}

void Equation::onExit()
{
	Sprite::onExit();
}



void Equation::setEquationColor(cocos2d::Color3B c3b)
{
    _bg2->setColor(c3b);

}


/*void Equation::setPosInSeq(bool isTop, bool isBottom)
{

	_panelEdit->setAsTop(isTop);
	_panelEdit->setAsBottom(isBottom);
}
*/




void Equation::updatePosition()
{
	//stopAllActions();
    if(getActionByTag(move_action_tag)!= nullptr)
    {
        stopActionByTag(move_action_tag);
    }
	MoveTo* mt = MoveTo::create(0.2f,_posInLayer);
	runAction(mt);
    mt->setTag(move_action_tag);
}

std::string Equation::toString()
{
	return "";
}





