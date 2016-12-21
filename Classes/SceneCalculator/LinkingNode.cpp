#include "LinkingNode.h"
#include "TextOperand.h"
#include "LinkingManager.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool LinkingNode::init()
{
     
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }


	_linkingIdentifier = LinkingIdentifier::create();
	addChild(_linkingIdentifier);


	_value = 0;

	_nodeID = 0;


	auto listenerTransfer = EventListenerCustom ::create("TRANSFER_FROM_TEXT_TO_NODE",CC_CALLBACK_1(LinkingNode::onRecevieValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTransfer,this);


	_sourceNode = nullptr;


	



    return true;
}





void LinkingNode::willBeSourceNode(bool willBe)
{
	
	if(willBe)
	{
		_linkingIdentifier->showAsSource();
	}
	else
	{
		_linkingIdentifier->hideIdentifier();
	}

}


void LinkingNode::willBeTargetNode(bool willBe)
{

	if(willBe)
	{
		_linkingIdentifier->showAsTarget();
	}
	else
	{
		_linkingIdentifier->hideIdentifier();
	}
}




void LinkingNode::addTarget( LinkingNode* lnode )
{
	_targetNodes.pushBack(lnode);
	sendValueToTargets();
}

void LinkingNode::setSource( LinkingNode* lnode )
{
	if(_sourceNode != nullptr)
	{
		removeSource();
	}

	
	_sourceNode = lnode;
	
}


void LinkingNode::removeTarget( LinkingNode* lnode )
{
	if (_targetNodes.contains(lnode))
	{
		//_eventDispatcher->dispatchCustomEvent("REMOVE_LINKAGE_BY_TARGET",lnode);
		_targetNodes.eraseObject(lnode);
	}
}

void LinkingNode::removeSource()
{

	_eventDispatcher->dispatchCustomEvent("REMOVE_LINKAGE_BY_TARGET",this);
	_sourceNode->removeTarget(this);
	_sourceNode = nullptr;
}

void LinkingNode::sendValueToTargets()
{

	if (_targetNodes.empty())
	{
		return;
	}
	else
	{
		for (LinkingNode* ln : _targetNodes)
		{
			ln->setValue(_value);
			_eventDispatcher->dispatchCustomEvent("TRANSFER_FROM_NODE_TO_TEXT",ln);
			ln->sendValueToTargets();
		}
		
	}


	
}

double LinkingNode::getValue()
{
	return _value;
}

void LinkingNode::setValue( double value )
{
	_value = value;
}

void LinkingNode::onRecevieValue( cocos2d::EventCustom* event )
{

	TextOperand* to = (TextOperand*)(event->getUserData());
	if (to->getParent() != this->getParent())
	{
		return;
	}

	_value =  to->getValue();
	
	if(_sourceNode != nullptr)
	{
		removeSource();
	}

	sendValueToTargets();

}


void LinkingNode::onEnter()
{

    Node::onEnter();
	if (!LinkingManager::getInstance()->allLinkingNodes.contains(this))
	{
		LinkingManager::getInstance()->allLinkingNodes.pushBack(this);
	}
}



void LinkingNode::setParent(Node * parent)
{

	Node::setParent(parent);
	if (!LinkingManager::getInstance()->allLinkingNodes.contains(this))
	{
		LinkingManager::getInstance()->allLinkingNodes.pushBack(this);
	}
}


void LinkingNode::onExit()
//void LinkingNode::removeFromParent()
{
	auto linkingManager = LinkingManager::getInstance();

	if (_sourceNode!= nullptr)
	{
		removeSource();
	}
	

	if (!_targetNodes.empty())
	{
		Vector<LinkingNode*> lns = Vector<LinkingNode*>();
		for (LinkingNode* ln :_targetNodes)
		{
			lns.pushBack(ln);
		}
		//_targetNodes.clear();
		for (LinkingNode* ln :lns)
		{
			ln->removeSource();
		}

	}

	if (linkingManager->allLinkingNodes.contains(this))
	{
		linkingManager->allLinkingNodes.eraseObject(this);
	}


	

    //Node::removeFromParent();
	Node::onExit();
}

bool LinkingNode::isLinkableAsTarget()
{
	return true;
}


void LinkingNode::setNodeID( unsigned nodeID )
{
	_nodeID = nodeID;
}

unsigned LinkingNode::getNodeID()
{
	return _nodeID;
}

LinkingNode* LinkingNode::getSource()
{
	return _sourceNode;
}




LinkingNode* LinkingNode::getRoot()
{
	if (_sourceNode == nullptr)
	{
		return this;
	}
	else
	{
		LinkingNode* ln = this;
		while (ln->getSource()!=nullptr)
		{
			ln = ln->getSource();
		}
		return ln;
	}
	
}

/*

int LinkingNode::getIndex()
{
	LinkingManager* linkingManager = LinkingManager::getInstance();
	if(!linkingManager->allLinkingNodes.contains(this))
	{
		return -1; 
	}
	else
	{
		return linkingManager->allLinkingNodes.getIndex(this);
	}
}

*/








/*
void LinkingNode::startLinking( cocos2d::EventCustom* event )
{

	enableTouch(true);


}

void LinkingNode::setHolderOperand( HolderOperand* holderOperand )
{
	_holderOperand = holderOperand;
	addChild(_holderOperand);
}

void LinkingNode::endLinking( cocos2d::EventCustom* event )
{

	enableTouch(false);
	_eventDispatcher->dispatchCustomEvent("TRANSFER_VALUE",_holderOperand);

}

bool LinkingNode::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	Point p = getParent()->convertToNodeSpace(touch->getLocation());

	if (getPosition().distance(p)<50)
	{
		_selected = true;
	}

	return true;
}

void LinkingNode::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void LinkingNode::onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *unused )
{
	Point p = getParent()->convertToNodeSpace(touch->getLocation());
	if (_selected&&(getPosition().distance(p)<50))
	{

		_eventDispatcher->dispatchCustomEvent("LINK",this);
		//_linkabe = false;
		
	}
	_selected = false;
}

void LinkingNode::onTouchCancelled( cocos2d::Touch *touch, cocos2d::Event *unused )
{

}

void LinkingNode::enableTouch( bool touch )
{
	_touchListener->setEnabled(touch);
	_holderOperand->enableTouch(!touch);

}

void LinkingNode::transferValue( cocos2d::EventCustom* event )
{
	if(((HolderOperand*)(event->getUserData()))!=_holderOperand)
	{
		return;
	}
	if (_targetNodes.size()==0)
	{
		return;
	}
	for (LinkingNode* ln :_targetNodes)
	{
		sendValue(ln);
	}



}

void LinkingNode::sendValue( LinkingNode* linkingNode )
{
	double v = _holderOperand->getValue();
	linkingNode->getHolderOperand()->setValue(v);

}

HolderOperand* LinkingNode::getHolderOperand()
{
	return _holderOperand;
}



void LinkingNode::enableLinkAsTarget( bool b )
{
	_linkabeAsTarget = b;
}

bool LinkingNode::isLinkableAsTarget()
{
	return _linkabeAsTarget;
}



*/
