#include "TextOperandWithLinking.h"
#include "LinkingNode.h"

USING_NS_CC;





// on "init" you need to initialize your instance
bool TextOperandWithLinking::init()
{

    // 1. super init first
    if ( !TextOperand::init() )
    {
        return false;
    }



	auto listenerTransfer = EventListenerCustom ::create("TRANSFER_FROM_NODE_TO_TEXT",CC_CALLBACK_1(TextOperandWithLinking::onRecevieValue,this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTransfer,this);

    
    return true;
}


void TextOperandWithLinking::setValue(double value, bool bUpdateText)
{

	setValue( value, bUpdateText,true,true);

/*
	setValueByLinkage(value,bUpdateText);
	//// ?数值 颜色  -传递

	_eventDispatcher->dispatchCustomEvent("TRANSFER_FROM_TEXT_TO_NODE",this);*/
}

void TextOperandWithLinking::setValue( double value, bool bUpdateText, bool bSetOutOfDate, bool bTransfer )
{

	if (bSetOutOfDate)
	{
		_eventDispatcher->dispatchCustomEvent("SET_EQUATION_OUT_OF_DATE",getParent()->getParent());
	}
	
	TextOperand::setValue( value, bUpdateText);


	if (bTransfer)
	{
		_eventDispatcher->dispatchCustomEvent("TRANSFER_FROM_TEXT_TO_NODE",this);
	}
	


}



/*
void TextOperandWithLinking::setValueByLinkage( double value , bool bUpdateText)
{


	std::string eveName = "SET_EQUATION_OUT_OF_DATE_";
	eveName = eveName + String::createWithFormat("%d",_equationID)->_string;
	_eventDispatcher->dispatchCustomEvent(eveName);

	TextOperand::setValue(value,bUpdateText);
	//// ?数值 -颜色  -传递
	
}
*/

void TextOperandWithLinking::onRecevieValue( cocos2d::EventCustom* event )
{


	LinkingNode* ln = (LinkingNode*)(event->getUserData());
	if (ln->getParent() != this->getParent())
	{
		return;
	}

	if (ln->getValue() != _value)
	{
		setValue(ln->getValue(),true,true,false);
		//// 数值 颜色  -传递
		_isAppending = false;
	}
	

}




