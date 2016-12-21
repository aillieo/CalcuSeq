#include "TextHolderWithLinking.h"
#include "LinkingNodePair.h"
#include "TextOperandWithLinking.h"

#include <iomanip>
#include "PersistenceManager.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool TextHolderWithLinking::init()
{

    // 1. super init first
    if ( !TextHolder::init() )
    {
        return false;
    }
    
	setTexture("textHolderWide.png");
	//setOpacity(20);
	//setColor(Color3B(190,190,190));

	_linkingNode = nullptr;

	_searchingForTarget = false;
	_potentialTarget = nullptr;

	_linkingManager = LinkingManager::getInstance();


    return true;
}




void TextHolderWithLinking::onLongPressed()
{
    
	_touchListener->setSwallowTouches(true);
	_linkingNode->willBeSourceNode(true);
	_searchingForTarget = true;

	bool  show = true;
	_eventDispatcher->dispatchCustomEvent("SHOW_LINKAGES", &show);

}

LinkingNode* TextHolderWithLinking::getLinkingNode()
{
	return _linkingNode;
}


void TextHolderWithLinking::initLinkingNode(LinkingNode* linkingNode)
{

	if(_linkingNode != nullptr)
	{
		return;
	}
	_linkingNode = linkingNode;
	addChild(_linkingNode,-1);
	_linkingNode->setPosition(getContentSize()/2);
	//_linkingManager->allLinkingNodes.pushBack(_linkingNode);

}


bool TextHolderWithLinking::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	_touchManager.reset();

	Point p = getParent()->convertToNodeSpace(touch->getLocation());

	if (getBoundingBox().containsPoint(p))
	{
		_potentialTarget = nullptr;
		_touchManager.containsTouchingPoint = true;
		scheduleUpdate();
		return true;
	}
	
	return false;
}

void TextHolderWithLinking::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{
    
    TextHolder::onTouchMoved(touch, unused);
    
	if (_touchManager.timer >= 0)
	{
		unscheduleUpdate(); 
		_touchManager.timer = -1;
	}

	if (_searchingForTarget)
	{
		Point p;

		if (_potentialTarget != nullptr)
		{
			p = _potentialTarget->getParent()->convertToNodeSpace(touch->getLocation());

			if (_potentialTarget->getPosition().getDistance(p)>60)
			{
				_potentialTarget->willBeTargetNode(false);
				_potentialTarget = nullptr;
			}
		}
		else
		{
			for (LinkingNode* ln : _linkingManager->allLinkingNodes)
			{
				p = ln->getParent()->convertToNodeSpace(touch->getLocation());
				if ((_potentialTarget == nullptr)&&(ln!=_linkingNode)&&(ln->getPosition().getDistance(p)<60))
				{
					ln->willBeTargetNode(true);
					_potentialTarget = ln;
				}
			}
		}
	}

}

void TextHolderWithLinking::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{

	unscheduleUpdate(); 
	if (_searchingForTarget)
	{
		if (_potentialTarget != nullptr)
		{
			buildLinkage(_linkingNode,_potentialTarget);
			_potentialTarget->willBeTargetNode(false);
			_potentialTarget = nullptr;
		}
		_searchingForTarget = false;
		_linkingNode->willBeSourceNode(false);
	}

	if (_touchManager.isLongPressing)
	{
		return;
	}

	TextHolder::onTouchEnded(touch, unused);


	
}

void TextHolderWithLinking::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	
}


void TextHolderWithLinking::update(float delta)
{
	_touchManager.timer += delta;

	if (_touchManager.timer >= 0.5)
	{
        
		unscheduleUpdate();

		_touchManager.isLongPressing = true;
		onLongPressed();
	}

}





void TextHolderWithLinking::buildLinkage( LinkingNode* source , LinkingNode* target )
{

	LinkingNodePair* lnp = lnp->create();
	lnp->linkingNodeSource = source;
	lnp->linkingNodeTarget = target;
	_eventDispatcher->dispatchCustomEvent("BUILD_LINKAGE",lnp);

}

std::string TextHolderWithLinking::toString()
{

	std::string str = "";
	std::stringstream ss;  

	//ss <<std::setprecision(16);
	ss<<std::setprecision(15);
	ss << getLinkingNode()->getValue()<<":";
	ss << getLinkingNode()->getNodeID();

/*
	int sourceId = -1;
	if (nullptr != getLinkingNode()->getSource())
	{
		sourceId = getLinkingNode()->getSource()->getNodeID();
	}
	ss << sourceId;*/

	ss >> str; 
	ss.clear();
	return str;

}

bool TextHolderWithLinking::initWithString( const std::string& str )
{

	std::vector<std::string> strs = PersistenceManager::splitString(str,":");

	if (strs.size() != 2)
	{
		return false;
	}

	std::stringstream ss(strs[0]);
	double val = 0;
	ss >> val;
	getLinkingNode()->setValue(val);
	((TextOperandWithLinking*)getText())->setValue(val,true);
	ss.clear();

    std::stringstream ss2(strs[1]);
    int nID = 0;
    //ss2<<strs[1];
    ss2>>nID;
	getLinkingNode()->setNodeID(nID);
	ss2.clear();



	return true;
}






/*
void TextHolderWithLinking::passEquationID( unsigned equationID )
{
	_linkingNode->setEquationID(equationID);

	if (holderType != HolderType::NOT_INPUT)
	{
		_text->setEquationID(equationID);
	}
	

	
}
*/


