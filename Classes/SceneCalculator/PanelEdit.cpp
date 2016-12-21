#include "PanelEdit.h"



USING_NS_CC;


// on "init" you need to initialize your instance
bool PanelEdit::init()
{

    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    



	_isTop = false;
	_isBottom = false;


	_itemRemove = MenuItemImage::create("ResourcesCalculator/itemRemove.png","ResourcesCalculator/itemRemove.png",CC_CALLBACK_1(PanelEdit::itemRemoveCallback,this));
	//_itemMoveUp = MenuItemImage::create("ResourcesCalculator/itemMoveUp.png","ResourcesCalculator/itemMoveUp.png",CC_CALLBACK_1(PanelEdit::itemMoveUpCallback,this));
	//_itemMoveDown = MenuItemImage::create("ResourcesCalculator/itemMoveDown.png","ResourcesCalculator/itemMoveDown.png",CC_CALLBACK_1(PanelEdit::itemMoveDownCallback,this));



	//Menu* menu = Menu::create(_itemRemove,_itemMoveUp,_itemMoveDown,NULL);
    Menu* menu = Menu::create(_itemRemove,NULL);
	addChild(menu);
	menu->setPosition(0,0);
	_itemRemove->setPosition(310,0);
	//_itemMoveUp->setPosition(175,0);
	//_itemMoveDown->setPosition(95,0);

	_itemRemove->setVisible(false);
	//_itemMoveUp->setVisible(false);
	//_itemMoveDown->setVisible(false);

/*
	_itemRemove->setGlobalZOrder(2);
	_itemMoveUp->setGlobalZOrder(2);
	_itemMoveDown->setGlobalZOrder(2);
	menu->setGlobalZOrder(2);*/

    return true;
}


/*
void PanelEdit::setAsTop(bool top)
{
	if (_isTop == top)
	{
		return;
	}
	
	_isTop = top;
	if(_itemRemove->isVisible())
	{
		showItems();
	}
}


void PanelEdit::setAsBottom(bool bottom)
{
	if (_isBottom == bottom)
	{
		return;
	}


	_isBottom = bottom;
	if(_itemRemove->isVisible())
	{
		showItems();
	}
	
}
*/

void PanelEdit::showItems()
{

	_itemRemove->setVisible(true);
	//_itemMoveUp->setVisible(!_isTop);
	//_itemMoveDown->setVisible(!_isBottom);
	
}

void PanelEdit::hideItems()
{

	_itemRemove->setVisible(false);
	//_itemMoveUp->setVisible(false);
	//_itemMoveDown->setVisible(false);

}


void PanelEdit::reverseItems()
{
	if(_itemRemove->isVisible())
	{
		hideItems();
	}
	else
	{
		showItems();
	}



}

/*
void PanelEdit::itemMoveUpCallback( cocos2d::Ref* pSender )
{

	_eventDispatcher->dispatchCustomEvent("MOVE_UP",this->getParent());

	
	
}

void PanelEdit::itemMoveDownCallback( cocos2d::Ref* pSender )
{
	_eventDispatcher->dispatchCustomEvent("MOVE_DOWN",this->getParent());

	
}
 */

void PanelEdit::itemRemoveCallback( cocos2d::Ref* pSender )
{
	_eventDispatcher->dispatchCustomEvent("REMOVE_EQUATION",this->getParent());
}
