#include "LayerLinkage.h"
#include "Linkage.h"
#include "PersistenceManager.h"
#include <iomanip>



USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerLinkage::init()
{
     
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto addLinkageListener = EventListenerCustom ::create("BUILD_LINKAGE",CC_CALLBACK_1(LayerLinkage::createLinkage,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(addLinkageListener,this);

	auto showLinkagesListener = EventListenerCustom ::create("SHOW_LINKAGES",CC_CALLBACK_1(LayerLinkage::setLinkagesVisible,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(showLinkagesListener,this);

	auto removeLinkageListener = EventListenerCustom ::create("REMOVE_LINKAGE_BY_TARGET",CC_CALLBACK_1(LayerLinkage::removeLinkageByTarget,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(removeLinkageListener,this);


	auto updateLkgPosListener = EventListenerCustom ::create("UPDATE_LINKAGE_POSITION",CC_CALLBACK_1(LayerLinkage::updateLinkagePosition,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(updateLkgPosListener,this);
    
    auto autoUpdateLkgPosListener = EventListenerCustom ::create("AUTO_UPDATE_LINKAGE_POSITION",CC_CALLBACK_1(LayerLinkage::autoUpdateLinkagePosition,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(autoUpdateLkgPosListener,this);


	_linkingManager = LinkingManager::getInstance();

	_updating = 0.0f;
	
	_linkagesShown = true;

	_autoUpdateLkgPos = false;

	setCascadeOpacityEnabled(true);

    return true;
}

void LayerLinkage::createLinkage( cocos2d::EventCustom* event )
{

	LinkingNodePair* lnp = (LinkingNodePair*)(event->getUserData());
	_createLinkage(lnp);

}


bool LayerLinkage::validateLinkage(LinkingNodePair* linkingNodePair)
{

    //return true;
    
	LinkingNode* source = linkingNodePair->linkingNodeSource;
	LinkingNode* target = linkingNodePair->linkingNodeTarget;



	if (!target->isLinkableAsTarget())
	{
		return false;
	}
	
	if (target->getParent()->getParent()==source->getParent()->getParent())
	{
		return false;
	}
	
	if (target->getRoot()==source->getRoot())
	{
		return false;
	}
	
	

	return true;

}





void LayerLinkage::removeLinkageByTarget(cocos2d::EventCustom* event)
{
	
	LinkingNode* ln = (LinkingNode*)(event->getUserData());
	Linkage* linkageToDelete = nullptr;

	for(Linkage* lkg : _linkingManager->allLinkages)
	{
		if (lkg->hasTarget(ln))
		{
			linkageToDelete = lkg;
			break;
		}
		
	}
	if (linkageToDelete!= nullptr)
	{
		_linkingManager->allLinkages.eraseObject(linkageToDelete);
		linkageToDelete->removeFromParent();
	}
	

	
	
}

void LayerLinkage::update( float delta )
{
	if ((_updating<= 0)&&(!_autoUpdateLkgPos))
	{
		unscheduleUpdate();
		return;
	}
	

	for (Linkage* lkg : _linkingManager->allLinkages)
	{
		lkg->updatePosition();
	}

	if (_updating>0 ){_updating -= delta;}
    

	
}

void LayerLinkage::updateLinkagePosition( cocos2d::EventCustom* event )
{


		if ((_updating<=0)&&(!_autoUpdateLkgPos))
		{
			scheduleUpdate();
		}
		_updating = 0.5;


}

void LayerLinkage::autoUpdateLinkagePosition( cocos2d::EventCustom* event )
{
    
    bool* b = (bool*)(event->getUserData());
    
    if (_autoUpdateLkgPos == *b)
    {
        return;
    }
    else
    {
        _autoUpdateLkgPos = *b;
    }
    
    if(_autoUpdateLkgPos)
    {
        
        if(_updating<=0)
        {
            scheduleUpdate();
        }
        
    }
    else
    {
        _updating = 0.5;
        
    }
    
    
    
    
}

void LayerLinkage::setLinkagesVisible( cocos2d::EventCustom* event )
{

	bool* show = (bool*)(event->getUserData());

	if (*show)
	{
		showLinkages(true);
		return;
	}
	

	if(_linkagesShown)
	{
		showLinkages(false);
	}
	else
	{
		showLinkages(true);
	}
}

void LayerLinkage::showLinkages( bool show )
{

	_linkagesShown = show;

	if (show)
	{

		//setOpacity(255);
		stopAllActions();
		FadeIn* fi = FadeIn::create(0.16f);
		runAction(fi);
	}
	else
	{
		//setOpacity(80);
		stopAllActions();
		FadeOut* fo = FadeOut::create(0.4f);
		runAction(fo);
	}
	
}

void LayerLinkage::_createLinkage( LinkingNodePair* linkingNodePair )
{
	if(!validateLinkage(linkingNodePair))
	{
		return;
	}

	LinkingNode* source = linkingNodePair->linkingNodeSource;
	LinkingNode* target = linkingNodePair->linkingNodeTarget;

	Linkage* linkage = Linkage::create();
	addChild(linkage);
	linkage->setNodes(source , target);
	_linkingManager->allLinkages.pushBack(linkage);


}



bool LayerLinkage::initLinkagesWithString( const std::string& str )
{

	std::vector<std::string> strLkg = PersistenceManager::splitString(str,";");

	int nodeID[2] = {0,0};
	if (str.size()>1)
	{
		for (std::string s : strLkg)
		{
			if (s.find(",") != std::string::npos)
			{
				std::vector<std::string> strNodes = PersistenceManager::splitString(s,",");
                std::stringstream ss(strNodes[0]);
				ss>>nodeID[0];
                ss.clear();
                std::stringstream ss2(strNodes[1]);
				ss2>>nodeID[1];
				ss2.clear();
				LinkingNodePair* lnp = LinkingNodePair::create();
				lnp->linkingNodeSource = _linkingManager->allLinkingNodes.at(nodeID[0]);
				lnp->linkingNodeTarget = _linkingManager->allLinkingNodes.at(nodeID[1]);
				_createLinkage(lnp);
			}


		}


	}



	setOpacity(0);
	showLinkages(true);
	


	return true;
}
