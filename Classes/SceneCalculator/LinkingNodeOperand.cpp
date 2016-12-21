#include "LinkingNodeOperand.h"

USING_NS_CC;



// on "init" you need to initialize your instance
bool LinkingNodeOperand::init()
{
 
    // 1. super init first
    if ( !LinkingNode::init() )
    {
        return false;
    }


	/*
	_holderOperand = nullptr;


	_linkabeAsTarget = true;

	auto startLinkingListener = EventListenerCustom ::create("START_LINKING",CC_CALLBACK_1(LinkingNode::startLinking,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(startLinkingListener,this);
    
	auto endLinkingListener = EventListenerCustom ::create("CANCEL_LINKING",CC_CALLBACK_1(LinkingNode::endLinking,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(endLinkingListener,this);


	auto transferValueListener = EventListenerCustom ::create("TRANSFER_VALUE",CC_CALLBACK_1(LinkingNode::transferValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(transferValueListener,this);



	_touchListener=EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan=CC_CALLBACK_2(LinkingNode::onTouchBegan,this);
	_touchListener->onTouchMoved=CC_CALLBACK_2(LinkingNode::onTouchMoved,this);
	_touchListener->onTouchEnded=CC_CALLBACK_2(LinkingNode::onTouchEnded,this);
	_touchListener->onTouchCancelled=CC_CALLBACK_2(LinkingNode::onTouchCancelled,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener,this);
	_touchListener->setEnabled(false);

	*/
    return true;
}

