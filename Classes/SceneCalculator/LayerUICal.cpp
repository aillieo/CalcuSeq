#include "LayerUICal.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool LayerUICal::init()
{
     
    // 1. super init first
    if ( !LayerUI::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



	_itemShowLinkages = MenuItemImage::create("ResourcesCalculator/button_top.png","ResourcesCalculator/button_top.png",CC_CALLBACK_1(LayerUICal::menuShowLinkagesCallback,this));
	Menu* menu = Menu::create(_itemShowLinkages,NULL);
	addChild(menu);
	menu->setPosition(0,0);
	_itemShowLinkages->setPosition(visibleSize.width/2,visibleSize.height -_itemShowLinkages->getContentSize().height/2 );
	_itemShowLinkages->setOpacity(0);


	_panelInputOperand = PanelInputOperand::create();
	addChild(_panelInputOperand);
	_panelInputOperand->setPosition(_panelInputOperand->getContentSize()/2);
	_panelInputOperand->setVisible(false);

	_panelInputOperator = PanelInputOperator::create();
	addChild(_panelInputOperator);
	_panelInputOperator->setPosition(_panelInputOperator->getContentSize()/2);
	_panelInputOperator->setVisible(false);



	auto showPanelInputListener = EventListenerCustom ::create("SHOW_PANEL_INPUT_OPERAND",CC_CALLBACK_1(LayerUICal::showPanelInputOperand,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(showPanelInputListener,this);
	auto showPanelInput2Listener = EventListenerCustom ::create("SHOW_PANEL_INPUT_OPERATOR",CC_CALLBACK_1(LayerUICal::showPanelInputOperator,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(showPanelInput2Listener,this);


	


    return true;
}




void LayerUICal::showPanelInputOperand( cocos2d::EventCustom* event )
{

	bool *show = (bool*)(event->getUserData());
	_panelInputOperand->setVisible(*show);
}

void LayerUICal::showPanelInputOperator( cocos2d::EventCustom* event )
{
	int *show = (int*)(event->getUserData());
	if (*show == 0)
	{
		_panelInputOperator->setVisible(false);
	}
	else
	{
		_panelInputOperator->setVisible(true);
		_panelInputOperator->setSymbolType(*show);
	}

}


void LayerUICal::menuShowLinkagesCallback(cocos2d::Ref* pSender)
{

	bool  show = false;
	_eventDispatcher->dispatchCustomEvent("SHOW_LINKAGES", &show);

}

