#include "LayerEquation.h"
#include "EquationUnary.h"
#include "EquationBinary.h"
#include "VersionConfigCal.h"
#include "PersistenceManager.h"


const float distance_between_equations = 180;
const float init_builder_posY = 1000;

#if (CAL_VERSION_PRO == 1)

	const int max_equations_allowed = 99;

#else

	const int max_equations_allowed = 10;

#endif


USING_NS_CC;




// on "init" you need to initialize your instance
bool LayerEquation::init()
{
     
    // 1. super init first
    if ( !LayerScroll::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_equationBuilder = EquationBuilder::create();
	addChild(_equationBuilder);
	_equationBuilder->setPosition(visibleSize.width/2,init_builder_posY);
	_equationBuilder->setPosInLayer(Point(visibleSize.width/2,init_builder_posY));



	_layerLinkage = LayerLinkage::create();
	addChild(_layerLinkage,5);




	auto addEquationListener = EventListenerCustom ::create("ADD_EQUATION",CC_CALLBACK_1(LayerEquation::addEquation,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(addEquationListener,this);
	auto removeEquationListener = EventListenerCustom ::create("REMOVE_EQUATION",CC_CALLBACK_1(LayerEquation::removeEquation,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(removeEquationListener,this);
	//auto equationMoveUpListener = EventListenerCustom ::create("MOVE_UP",CC_CALLBACK_1(LayerEquation::equationMoveUp,this));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(equationMoveUpListener,this);
	//auto equationMoveDownListener = EventListenerCustom ::create("MOVE_DOWN",CC_CALLBACK_1(LayerEquation::equationMoveDown,this));
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(equationMoveDownListener,this);


    auto dynamicSortListener = EventListenerCustom ::create("DYNAMIC_SORT",CC_CALLBACK_1(LayerEquation::dynamicSort,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(dynamicSortListener,this);
    
    auto scrollLockListener = EventListenerCustom ::create("SCROLL_LOCK",CC_CALLBACK_1(LayerEquation::scrollLock,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority( scrollLockListener,this);


	//随机 用于建立等式时产生不同的颜色
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);
	srand(rand_seed);
    _lastColor = CCRANDOM_0_1()*5;


    _eqInDynamicSorting = nullptr;
	_eqInDynamicSorting_Y = 0;
    
	_locked = false;
    

    return true;
}

void LayerEquation::addEquation( cocos2d::EventCustom* event )
{
	Equation* eq = nullptr;
	int* operands = (int*)(event->getUserData());
	switch (*operands)
	{
	case 1:
		eq = EquationUnary::create();
		break;
	case 2:
		eq = EquationBinary::create();
		break;
	default:
		break;
	}
    
	_addEquation(eq);


}


void LayerEquation::_addEquation( Equation* eq )
{
	addChild(eq);

	eq->setPosition(_equationBuilder->getPositionX(), init_builder_posY - _equations.size() *distance_between_equations );
    eq->setEquationColor(getRandomColor());
	eq->setPosInLayer(eq->getPosition());

	_equations.pushBack(eq);




	unsigned equationID = _equationIDs.size() + 1;
	while (find(_equationIDs.begin(),_equationIDs.end(),equationID) != _equationIDs.end())
	{
		equationID++;
	}
	eq->setEquationID(equationID);
	_equationIDs.push_back(equationID);

	ScaleTo* st = ScaleTo::create(0.2f,1);
	eq->setScaleY(0.01f);
	eq->runAction(st);

	updateLimitUpper();

	if(_equations.size()>=max_equations_allowed)
	{
		_equationBuilder->setVisible(false);
	}
	else
	{	
		_equationBuilder->setPosInLayer(Point(_equationBuilder->getPositionX(),eq->getPositionY() - distance_between_equations));
		_equationBuilder->updatePosition();
	}

	if (_equations.size()==1)
	{
		bool display = false;
		_eventDispatcher->dispatchCustomEvent("DISPLAY_HELP_INFO",&display);

		//eq->setPosInSeq(true,true);
	}
/*	else if(_equations.size()==2)
	{
		_equations.front()->setPosInSeq(true,false);
		eq->setPosInSeq(false,true);
	}
	else
	{
		_equations.at(_equations.size()-2)->setPosInSeq(false,false);
		eq->setPosInSeq(false,true);
	}
*/
    
    
    
    float dt = convertToWorldSpace(_equationBuilder->getPosition()).y -  490;
    if(dt < 0)
    {
        scrollTo(getPositionY() - dt);
    }
    
    
    
}



void LayerEquation::removeEquation( cocos2d::EventCustom* event )
{
	Equation* eqRmv = (Equation*)(event->getUserData());
	float posY = eqRmv->getPositionY();

	eqRmv->onRemove();


	std::vector<unsigned>::iterator iter=std::find(_equationIDs.begin(),_equationIDs.end(),eqRmv->getEquationID());
	_equationIDs.erase(iter);

	eqRmv->removeFromParent();
	_equations.eraseObject(eqRmv);




	for (Equation* eq : _equations)
	{
		if (eq->getPositionY()< posY)
		{
			eq->setPosInLayer(Point(eq->getPositionX() , eq->getPositionY()+distance_between_equations));
			eq->updatePosition();
		}
	}

	updateLimitUpper();
	resortEquations();

	_eventDispatcher->dispatchCustomEvent("UPDATE_LINKAGE_POSITION");

	if(_equations.size() == max_equations_allowed - 1)
	{
		_equationBuilder->setVisible(true);
	}
	else
	{
		_equationBuilder->setPosInLayer(Point(_equationBuilder->getPositionX(),init_builder_posY - _equations.size() *distance_between_equations));
		_equationBuilder->updatePosition();
	}

	if (_equations.empty())
	{
		bool display = true;
		_eventDispatcher->dispatchCustomEvent("DISPLAY_HELP_INFO",&display);
	}
/*	else if (_equations.size()==1)
	{
		_equations.front()->setPosInSeq(true,true);
	}
	else if(_equations.size()>=2)
	{
		_equations.front()->setPosInSeq(true,false);
		_equations.back()->setPosInSeq(false,true);
	}
*/


}



cocos2d::Color3B LayerEquation::getRandomColor()
{
    //int maxColor = 7;
    int maxColor = 4;
    int rdm = (int)(CCRANDOM_0_1() * maxColor);
    /*
     int r = (rdm)*255/maxColor;
     int b = (maxColor-rdm)*255/maxColor;
     maxColor = maxColor/2;
     int g = (maxColor-abs((int)(rdm-1-maxColor)))*255/maxColor;
     return Color3B(r,g,b);
     */
    
    if(rdm == _lastColor)
    {
        rdm = 3 -_lastColor;
    }
    _lastColor = rdm;
    
    
    Color3B c3b = Color3B(255, 255, 255);
    
    /*
     switch(rdm)
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
     */
    
    switch(rdm)
    {
        case 0:
            c3b = Color3B(237, 50, 33);
            break;
        case 1:
            c3b = Color3B(255, 221, 0);
            break;
        case 2:
            c3b = Color3B(93, 204, 35);
            break;
        case 3:
            c3b = Color3B(162, 48, 219);
            break;
            
        default:
            break;
            
    }
    
    
    return c3b;
    
    
}

void LayerEquation::updateLimitUpper()
{
	

	_limitUpper = ( _equations.size() - 3) * distance_between_equations  ;
	if (_limitUpper < 0)
	{
		_limitUpper = 0;
	}
	


	if (getPositionY()>= _limitUpper)
	{
		scrollTo(_limitUpper);
	}
}

/*
void LayerEquation::equationMoveUp( cocos2d::EventCustom* event )
{

	Equation* eq2 = (Equation*)(event->getUserData());

	if((!_equations.contains(eq2))||(eq2 == _equations.front()))
	{
		return;
	}

	unsigned u2 = _equations.getIndex(eq2);

	Equation* eq1 = _equations.at(u2-1);

	swapPos(eq1,eq2);
	eq1->updatePosition();
	eq2->updatePosition();
	_eventDispatcher->dispatchCustomEvent("UPDATE_LINKAGE_POSITION");


}



void LayerEquation::equationMoveDown( cocos2d::EventCustom* event )
{

	Equation* eq2 = (Equation*)(event->getUserData());

	if((!_equations.contains(eq2))||(eq2 == _equations.back()))
	{
		return;
	}

	unsigned u2 = _equations.getIndex(eq2);

	Equation* eq1 = _equations.at(u2+1);

	swapPos(eq1,eq2);
	eq1->updatePosition();
	eq2->updatePosition();
	bool autoUpdate = false;
	_eventDispatcher->dispatchCustomEvent("UPDATE_LINKAGE_POSITION",&autoUpdate);


}
*/

void LayerEquation::swapPos(Equation* eq1 , Equation* eq2)
{

	unsigned u1 = _equations.getIndex(eq1);
	unsigned u2 = _equations.getIndex(eq2);

	//float posY1 = eq1->getPositionY();
	//float posY2 = eq2->getPositionY();

	eq2->setPosInLayer(Point(eq2->getPositionX(),init_builder_posY - u1 *distance_between_equations));
	//eq2->updatePosition();
	eq1->setPosInLayer(Point(eq1->getPositionX(),init_builder_posY - u2 *distance_between_equations));
	//eq1->updatePosition();

	_equations.swap(u1,u2);

	//bool autoUpdate = false;
	//_eventDispatcher->dispatchCustomEvent("UPDATE_LINKAGE_POSITION",&autoUpdate);
	//resortEquations();

/*
	if (u1 == 0)
	{
		eq2->setPosInSeq(true,false);
	}
	else if (u1 == _equations.size() - 1)
	{
		eq2->setPosInSeq(false,true);
	}
	else
	{
		eq2->setPosInSeq(false,false);
	}
	

	if (u2 == 0)
	{
		eq1->setPosInSeq(true,false);
	}
	else if (u2 == _equations.size() - 1)
	{
		eq1->setPosInSeq(false,true);
	}
	else
	{
		eq1->setPosInSeq(false,false);
	}

*/
	



}





bool LayerEquation::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused)
{
	if(!_equations.empty())
	{
		LayerScroll::onTouchBegan(touch, unused);
		return true;
	}
	else
	{
		return false;
	}

}


void LayerEquation::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused)
{

	if(!_locked)
	{
		LayerScroll::onTouchMoved(touch, unused);
		sendOpacityOfHiddenLabel();
	}
	
	

}


void LayerEquation::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused)
{

	LayerScroll::onTouchEnded(touch, unused);

	if(_locked)
	{
		
		_locked = false;
	}
	
	

}



void LayerEquation::resortEquations()
{

// 	std::sort(_equations.begin(),_equations.end(),[](Equation* eq1 ,Equation* eq2 ){return eq1->getPositionY()>eq2->getPositionY();});
// 	for (int i = 0; i < _equations.size(); i++)
// 	{
// 		log("eqid = %u",_equations.at(i)->getEquationID());
// 	}

}



std::string LayerEquation::toString()
{

	std::stringstream ss;  
	ss <<"e";


	for (Equation* eq : _equations)
	{
		ss << ";";
		ss << eq->toString();
	}

	ss << "~";
	ss << "l";


	LinkingManager* lm = LinkingManager::getInstance();
	for (Linkage* lkg : lm->allLinkages)
	{
		ss << ";";
		ss <<lkg->getLinkingNodePair()->linkingNodeSource->getNodeID()<< ",";
		ss <<lkg->getLinkingNodePair()->linkingNodeTarget->getNodeID();
	}


	std::string str = "";
	ss>>str;
	ss.clear();
	
	return str;
}


LayerEquation* LayerEquation::createWithString(const std::string& str)
{

	LayerEquation* le = LayerEquation::create();
	
	if (str.empty())
	{
		return le;
	}
	

	std::vector<std::string> str2 = PersistenceManager::splitString(str,"~");
	


	std::vector<std::string> strEq = PersistenceManager::splitString(str2[0],";");

	
	if (strEq.size() > 1)
	{
		for (std::string s : strEq)
		{
			if (s.find("b") != std::string::npos)
			{
				EquationBinary* eq = EquationBinary::createWithString(s);
				le->_addEquation(eq);
			}
			else if (s.find("u") != std::string::npos)
			{
				EquationUnary* eq = EquationUnary::createWithString(s);
				le->_addEquation(eq);
			}


		}

	}
	

	LinkingManager::getInstance()->resortNodes();
	le->_layerLinkage->initLinkagesWithString(str2[1]);

	if (le->_equations.empty())
	{
		bool display = true;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("DISPLAY_HELP_INFO",&display);
	}
	
	return le;
	
}

void LayerEquation::_update( float delta )
{
	LayerScroll::_update(delta);
	
	sendOpacityOfHiddenLabel();

}

void LayerEquation::sendOpacityOfHiddenLabel()
{
	float op = _limitBottom - getPositionY() - 50 ;
	if (op > 0)
	{
		op = 1.2 * op;
		op = (op>255?255:op);
		_eventDispatcher->dispatchCustomEvent("ADJUST_HIDDEN_LABEL",&op);
	}
	else
	{
		op = 0;
		_eventDispatcher->dispatchCustomEvent("ADJUST_HIDDEN_LABEL",&op);
	}
}



void LayerEquation::dynamicSort(cocos2d::EventCustom* event)
{

    
    if (_eqInDynamicSorting == nullptr)
    {
        _eqInDynamicSorting = (Equation*)(event->getUserData());
        _eqInDynamicSorting -> setScale(1.02f);
        _eqInDynamicSorting -> setLocalZOrder(2);
        _eqInDynamicSorting_Y = _eqInDynamicSorting->getPositionY();
        scheduleUpdate();
    }
    else
    {
        unscheduleUpdate();
        
         _eqInDynamicSorting -> setScale(1.0f);
         _eqInDynamicSorting -> setLocalZOrder(0);
        _eqInDynamicSorting -> updatePosition();
        
        
        _eqInDynamicSorting = nullptr;
    }

	bool autoUpdate = (_eqInDynamicSorting != nullptr);
	_eventDispatcher->dispatchCustomEvent("AUTO_UPDATE_LINKAGE_POSITION",&autoUpdate);

    
}

void LayerEquation::update(float delta)
{
    
    if(convertToWorldSpace(_eqInDynamicSorting->getPosition()).y > 1280 - distance_between_equations )
    {
        if ((getPositionY()> _limitBottom))
        {
            setPositionY(getPositionY()-10);
            _eqInDynamicSorting->setPositionY(_eqInDynamicSorting->getPositionY() + 10);
            if ((getPositionY()< _limitBottom))
            {
                setPositionY(_limitBottom);
            }
        }
        
        
    }
    else if(convertToWorldSpace(_eqInDynamicSorting->getPosition()).y <  distance_between_equations )
    {
        if ((getPositionY()< _limitUpper))
        {
            setPositionY(getPositionY()+10);
            _eqInDynamicSorting->setPositionY(_eqInDynamicSorting->getPositionY() - 10);
            if ((getPositionY()> _limitUpper))
            {
                setPositionY(_limitUpper);
            }
        }
    }

    //return;
    

	if(fabs(_eqInDynamicSorting->getPositionY() - _eqInDynamicSorting_Y) > distance_between_equations)
	{
		unsigned uu = _equations.getIndex(_eqInDynamicSorting);
		unsigned uu2 = uu;
		if(_eqInDynamicSorting->getPositionY() > _eqInDynamicSorting_Y )
		{
            if(uu2 != 0)
            {
                uu2 --;
            }

		}
		else
		{
			if(uu2 <_equations.size()-1)
            {
                uu2 ++;
            }
		}

		if(uu2 != uu)
		{
            _eqInDynamicSorting_Y = _equations.at(uu2)->getPositionY();
            swapPos(_equations.at(uu2) , _eqInDynamicSorting);
			_equations.at(uu)->updatePosition();

		}


	}




}




void LayerEquation::scrollLock(cocos2d::EventCustom* event)
{
	_locked = true;
}